# Points of View

Points of View are Stig's version of Isolation – the ACID property that defines how/when the changes made by one operation become visible to other concurrent operations.  Most databases have some form of locking to make sure changes happen consistently, when many things are trying to read and write to it at the same time.  Pessimistic databases lock down the entire database any time someone wants to read or write, to make sure nothing gets overwritten, but this is sometimes overkill and makes it very slow to access anything.  Optimistic databases lock very little, let changes and reads happen quickly, and have to cross their fingers and pray not to end up with overwrites or bad reads.

Stig doesn't lock at all.  And yet, we also guarantee data consistency.

With Stig, instead of the database locking everything every time someone makes a change, we have people make changes in their own little private points of view, like their own sandbox.  Then, changes propagate outward from private points of view to shared points of view, and then to global, which is the whole database.  Nothing needs to lock as changes come in; whether or not they can be resolved will be determined at a later point.  We call this "eventual consistency" – this means that instantaneous changes will only be seen by a subset of the database at first, but that the changes will get resolved with the entire database eventually and consistently.

These subsets of the database are, in the Stig world, “points of view”. We make it possible for you to work in your own part of the database with your own view of reality, which will later be resolved with the rest of the world.

There are three levels of points of view: Private, Shared, and Global. Changes propagate from Private to Shared, and from Shared to Global.  They can also go straight from a Private POV to the Global POV; intermediate Shared POVs are created for the sake of making interactions between users faster.  Users always make changes in a Private POV.

![POV Diagram](./images/POVs.gif "Stig Points of View")

In this diagram, users may affect more than one Private POV at a time – for example, maybe Yellow is involved in a heated online social competition with Red and Orange, but is also working on changing her profile, something which can go directly to Global without it really affecting anybody else. 

* **Private** – Things in a private point of view are only changeable by one user — and as such, all things that are modified by users are in private points of view. These points of view may be ephemeral.  A user could possibly affect several private points of view at once.
* **Shared** – Shared points of view are used to bridge between the private and global points of view. Users cannot change them directly; instead, they are an intermediary point for changes. Shared points of view are a deliberate logical grouping of private POVs that make sense to resolve together without involving the rest of the database as well.
* **Global** – Things in the global point of view can be viewed by all users, and have been resolved in such a way to create a consistent world for everyone accessing the database. This is very similar to what would be the result of a commit in a traditional database. Usually, when we write the database to disk, we write from the global POV.

Being able to make quick changes without locking the entire database gives us a lot of flexibility in what we can do, as well as much faster communication for real-time applications. On the other hand, conflicts can arise when resolving the differences between points of view, and in some cases that separate point of view has to be shut down as it is completely incompatible with the rest of the database’s view of the world. We don’t delete the point of view, however, we just declare it as unresolvable. This allows the programmer to handle the situation without losing the data in the commit.

Let’s try to apply this to a real-world example. Imagine that Alice, Bob, and Carol are all interested in reading the Lord of the Rings trilogy, and want to take the books out from the library. They’re not just going to go straight to the city’s database of books to figure out whether they can take out the books, are they? Each of them goes to their individual branch and tries to take out the book. Suppose Alice and Bob go to the same branch and Carol goes to another one nearby, and each branch has one copy of each of the books in the trilogy, and the central library database knows that.

![POV Library Example Diagram](./images/Libraries.gif "A library-based POV example")

Now, all three people want to take out Book 1 of the trilogy. Carol has no problem — there’s one copy of the book at her local library, and she’s the only one who wants it, so she gets it. In Carol’s private POV, and in the Shoreline Library’s system, Carol now has the book and the library does not have a copy on the shelves. The change will propagate to the city’s database in a minute.

At the very same time, Alice and Bob both go to their local library and try to take out Book 1. They both get the book at the same time, and argue all the way up to the front counter, where a librarian flips a coin and randomly awards the book to Alice. In Alice’s POV she has the book, and in the Ballard library’s system, the library does not have a copy on the shelves. These changes will also propagate to the city’s database in a minute.

Bob asks if there’s a nearby library that has a copy of the book. The librarian queries the central library database, which says that the Shoreline library has a copy of the book, because Carol’s checkout hasn’t propagated through yet.

Bob tells the librarian that he’d like to put in a hold for the Shoreline copy and also take out Books 2 and 3. But just before the librarian tries to put in a hold for Book 1 at Shoreline for Bob, the changes propogate through to the central database. It sends her back a message saying that she can’t reserve a copy for Bob, because there is no copy of it at Shoreline anymore.

Bob decides that he’ll just reserve Book 1 after Alice brings it back.

-----

pov.md Copyright 2010-2014 Stig LLC

pov.md is licensed under a Creative Commons Attribution-ShareAlike 4.0 International License.

You should have received a copy of the license along with this work. If not, see <http://creativecommons.org/licenses/by-sa/4.0/>.

Based upon the Points of View document in the [Tagged](http://tagged.com) wiki, originally authored by [dr4b](https://github.com/dr4b).
