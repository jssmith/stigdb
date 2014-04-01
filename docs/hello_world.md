# Hello World in Stig

This document will walk you through two different _Hello World_ scenarios:

1. A simpler method, using [Stig Mynde](./mynde.md)
1. A slightly more advanced method, using _Stigscript_ packages and the Stig command line client

## Stig Mynde



## Stigscript Packages

Once the Stig programs are compiled and installed, it's time to write and run our first package!

A _package_ is a piece of code which Stig runs in order to perform operations. Think of it like a library package or module (a'la Ruby gems, Python packages, or Perl modules).

Packages give Stig a remarkable amount of flexibility and power. They're written in _Stigscript_.

### Create a packages directory

Stig needs a directory where it knows it can locate its packages. Because we're just testing for now, we're just going to create this as a subdirectory of the `~/stig` directory which was created during the build and installation phase:

```
mkdir ~/stig/packages
```

### Write a "Hello World" package

In the venerable tradition of Hello World, our first package isn't going to do very much. Save the following into a file named `~/stig/packages/hello_world.stig`:

```
/* Hello World! */

package #1;

hello_world = ("Hello, world! My name is " + name + ".") where {
  name = given::(str);
};
```

### Compile your new package

Part of the secret sauce which makes Stig so fast is that all packages are pre-compiled before you even get started. Without the overhead of an interpreted language, Stig is able to achieve blinding speeds.

To compile your new package, run the following command:

```
stigc ~/packages/hello_world.stig
```
Assuming everything went to plan, your packages directory should now contain these files:

```
hello_world.1.so
hello_world.cc
hello_world.h
hello_world.link.cc
hello_world.stig
hello_world.stig.sig
```
'hello_world.1.so` is the file which Stig will run as a package.

Now that you have a package, it's time to fire up the server.

### Start the Stig server

Before you can run any Stig operations, you must start the Stig server. The command below will start the `stigi` server program as a daemon, use the `demo` instance, and enable logging:

```
sudo stigi --create=true --la --le --d --iname=helloworld --starting_state=SOLO --mem_sim
```

This command starts the server in _memory simulation_ mode. In this mode, the server will simulate a disk volume in memory. Because the data is not actually written to disk, when you stop the server, all data will be lost.

### Run the Stig client

The Stig command line client allows you to interact with your Stig database from the comfort of your own keyboard.

To start the client:

```
$ stig_client --la --le
```

You should now be greeted by the client prompt:

```
stig>
```

To exist the client, type `ctrl-D`.

### Install the package

Before you can use the package, you must install it so Stig knows it exists. At the client prompt, type:

```
stig> install hello_world.1;
```
After a brief wait, you will be returned to the client prompt. Your package is now ready to use.

### Create a session and a private point of view

All Stig operations must occur within a point of view and a session. You can create these at the command line.

If the call to `create_session` is successful, it will return the ID of the session. Use this ID in the `create_private_pov` call. This will associate the point of view with the correct session.

If the call to `create_private_pov` is successful, it will return the ID of the point of view.

```
stig> create_session ttl=10000
SESSION_ID
stig> create_private_pov ttl=10000 session=SESSIONID
POV_ID
```

### Give the package a spin

Now to call your package:

```
stig> hello_world(name="Inigo Montoya");
{ "result": "Hello, world! My name is Inigo Montoya."}
```

### Success!

Congratulations! You've now written and used your first Stig package!

-----

hello_world.md Copyright 2010-2014 Stig LLC

hello_world.md is licensed under a Creative Commons Attribution-ShareAlike 4.0 International License.

You should have received a copy of the license along with this work. If not, see <http://creativecommons.org/licenses/by-sa/4.0/>.

This document owes a large debt to the Developing with Stig document in the [Tagged](http://tagged.com) wiki, originally authored by [dr4b](https://github.com/dr4b).
