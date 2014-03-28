# Stig Non-Relational Database

This is the repository for the Stig non-relational database. It's meant to be fast and to scale for billions of users.  Stig provides a single path to data and will eliminate our need for memcache due to its speed and high concurrency.

## Stig features:

* **Points of View**: This is our version of optimistic locking or isolation. [Learn more](https://github.com/StigDB/stigdb/blob/master/docs/pov.md). 
* **Time Travel**: We use something called the _Flux Capacitor_ to keep a history of changes made to the database and to resolve conflicts as they come into shared points of view and the global point of view. This permits us to perform consistent read for any point in time. Stig defines its "time line" by causality rather than clock time. Instead of manipulating timestamps, Stig records an ordering of events (e.g., update A affects update B, so A "happens before" B).)
* **Query Language**: Stig has its own high-level, compiled, type-safe, functional language called _Stigscript_. Stigscript is not just a query language: You can write general-purpose programs in it complete with compile-time unit tests. Stig comes with a compiler that transforms Stigscript into shared libraries (.so files on Linux), which Stig servers load as packages.
* **Scalability and Availability**: While we eventually plan to develop a sharded Stig machine (and actively design so that we can build such a machine), our current single-node server with fail-over/replication can handle hundreds of thousands of transactions per second. 

## Supported Platforms

Currently Stig only runs on Linux.

## System Requirements

TBD (HDD? SSD? RAM? Processor speed? FS type?)

## Building Stig

See [the build/install docs](https://github.com/StigDB/stigdb/blob/master/docs/build_and_install.md) for precise instructions

## Contributing to Stig

Contributing to Stig is easy! Just have a look at our [documentation](https://github.com/StigDB/stigdb/blob/master/docs/contributing.md) about how to contribute.

-----

README.md Copyright 2010-2014 Stig LLC

README.md is licensed under a Creative Commons Attribution-ShareAlike 4.0 International License.

You should have received a copy of the license along with this work. If not, see <http://creativecommons.org/licenses/by-sa/4.0/>.
