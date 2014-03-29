# Hello World in Stig

Once the Stig programs are compiled and installed, it's time to write and run our first package!

A _package_ is a piece of code which Stig runs in order to perform operations. Think of it like a library package or module (a'la Ruby gems, Python packages, or Perl modules).

Packages give Stig a remarkable amount of flexibility and power. They're written in _Stigscript_.

## Create a packages directory

Stig needs a directory where it knows it can locate its packages. Because we're just testing for now, we're just going to create this as a subdirectory of the `~/stig` directory which was created during the build and installation phase:

```
mkdir ~/stig/packages
```

## Write a "Hello World" package

In the venerable tradition of Hello World, our first package isn't going to do very much. Save the following into a file named `~/stig/packages/hello_world.stig`:

```
/* Hello World! */

package #1;

hello_world = ("Hello, world! My name is " + name + ".") where {
  name = given::(str);
};
```

## Compile your new package

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

## Start the Stig server

> Assuming you used the [Quick Start](https://github.com/StigDB/stigdb/blob/master/docs/build_and_install.md#quick-start) in the [Building and Installing Stig](https://github.com/StigDB/stigdb/blob/master/docs/build_and_install.md) doc, you should have a Stig instance (database) named _demo_. If you named it something else, please update the commands below accordingly.

Before you can run any Stig operations, you must start the Stig server. The command below will start the `stigi` server program as a daemon, use the `demo` instance, and enable logging:

```
sudo stigi --create=false --la --le --d --iname=demo --starting_state=SOLO
```

## Run the Stig client

stig_client --la --le
