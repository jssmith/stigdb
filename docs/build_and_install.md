# Building and Installing Stig
* [Introduction](#introduction)
* [Quick Start](#quick-start)
    * [Debug (default)](#debug-build)
    * [Release](#release-build)
* [Supported Platforms](#supported-platforms)
    * [A note on VMs](#a-note-on-vms)
* [Pre-Requisites](#pre-requisites)
    * [Compiler](#compiler)
    * [Libraries](#libraries)
    * [Other programs](#other-programs)
    * [Platform-specific package install command lines](#platform-specific-package-install-command-lines)
        * [Ubuntu](#ubuntu)
        * [CentOS](#centos)
* [Retrieving the Stig Source Code](#retrieving-the-stig-source-code)
* [Build Commands](#build-commands)
    * [make](#make)
    * [make test](#make-test)
    * [make test_build](#make-test_build)
    * [make test_lang](#make-test_lang)
    * [make clean](#make-clean)
* [Creating a Stig disk volume](#creating-a-stig-disk-volume)
* [Hello World](#hello-world)
* [Platform-specific](#platform-specific)
    * [Ubuntu (13.10 and above)](#ubuntu-1310-and-above)
    * [CentOS (6.4 and above)](#centos-64-and-above)
* [Troubleshooting](#troubleshooting)
* [gcc compile tips](#gcc-compile-tips)

## Introduction

As the Stig project is still quite young, the build and installation process currently is fairly hands-on. As the project matures we will make this easier and faster. Please bear with us (and this process) as we grow.

If you experience any problems with the build or this documentation, please [open a GitHub issue](https://github.com/StigDB/stigdb/blob/master/docs/contributing.md#open-github-issues) to report it.

## Quick Start

The instructions below are for **UBUNTU 13.10**. Please modify them accordingly for your Linux distribution.

### Debug Build

This is the default build mode for Stig.

```
(create a separate stig partition)
sudo add-apt-repository ppa:ubuntu-toolchain-r/ppa
sudo apt-get update
sudo apt-get install gcc-4.8
sudo apt-get install g++
sudo apt-get install flex bison util-linux git build-essential uuid-dev libaio-dev libgmp-dev libsctp-dev lksctp-tools zlib1g-dev libicu-dev libreadline6-dev libsnappy-dev valgrind
cd ~
mkdir stig
cd stig
git clone git://github.com/stigdb/stigdb.git ./src
cd src
export PATH=${PATH}:${HOME}/stig/src/tools
make
make test           (optional but recommended)
make test_lang      (optional but recommended)
sudo ~/stig/out/debug/stig/indy/disk/util/stig_dm --la --le --create-volume --device-speed=slow --instance-name=demo --num-devices=1 --stripe-size=512 <DEVICE>
```

### Release Build

```
(create a separate stig partition)
sudo add-apt-repository ppa:ubuntu-toolchain-r/ppa
sudo apt-get update
sudo apt-get install gcc-4.8
sudo apt-get install g++
sudo apt-get install flex bison util-linux git build-essential uuid-dev libaio-dev libgmp-dev libsctp-dev lksctp-tools zlib1g-dev libicu-dev libreadline6-dev libsnappy-dev valgrind
cd ~
mkdir stig
cd stig
git clone git://github.com/stigdb/stigdb.git ./src
cd src
export PATH=${PATH}:${HOME}/stig/src/tools
PREFIX=/installation/path ./bootstrap.sh
make release
make test           (optional but recommended)
make test_lang      (optional but recommended)
sudo make install PATH=${PATH}:${HOME}/stig/src/tools
sudo stig_dm --la --le --create-volume --device-speed=slow --instance-name=demo --num-devices=1 --stripe-size=512 <DEVICE>

```

## Supported Platforms

Stig should work on any Linux-based operating system which uses kernel version 2.6.32 or greater.

The versions on which it is known to build and run:

* [Ubuntu 13.10](http://releases.ubuntu.com/13.10/)
* [CentOS 6.4](http://isoredirect.centos.org/centos/6/isos/x86_64/)
* [Arch Linux](https://www.archlinux.org)

### A note on VMs

If you plan to build and install Stig on a virtual machine, please consider the following suggestions when configuring the machine:

* 4GB RAM minimum, 8GB RAM recommended
* 12GB disk space minimum
* Create a separate partition for the Stig block level device. This partition should be at least 1GB in size.

## Create a new partition/volume

Because of the specialized nature of its storage requirements, Stig must maintain its database files in a separate partition/volume.

While this step is not required for building the Stig binaries, it may be something you'd prefer to do prior to installing any other required software.

Please create the new partition according to the directions for your Linux distribution. The minimum recommended partition size is 1GB.

**WARNING!** Stig will overwrite and destroy any data which exists in this partition. Please do not re-use a partition which contains information you'd like to retain.

### Memory simulation mode

For development purposes, it is possible to start up the `stigi` server in _memory simulation_ mode.

Memory simulation mode is the equivalent of having the Stig block device in memory rather than on disk. Running in memory simulation mode removes the requirement to have a separate volume/partition for the Stig databases.

To run in memory simulation mode, start the `stigi` server with the `--mem_sim` flag.

> **NOTA BENE!**
> Data **will not** persist in memory simulation mode. When the server is shut down any data stored in memory will disappear.

## Pre-Requisites

There are several prerequisites which must be installed for a successful build of Stig:

### Compiler

* gcc-4.8.2 or above (4.8.0 has a nasty bug which craters Stig and 4.8.1 has several bugs in its handling of c++11). 4.7 will work for the moment, but we'll be adopting some C++11 features which 4.7 doesn't support in the near future. So it's best you just start out with a more modern version of the compiler.
    * The preferred method of installing gcc-4.8.2 is to use [a pre-compiled binary](https://launchpad.net/~ubuntu-toolchain-r/+archive/ppa). If that does not work or is not available for your Linux distribution, please see the [gcc compile tips](#gcc-compile-tips) below.
* g++ version 4.8.2 or above
    * If you use the [PPA](https://launchpad.net/~ubuntu-toolchain-r/+archive/ppa), you should be able to install this with a simple `sudo apt-get install g++`.

Shortly Stig will be switching from gcc to clang+LLVM 3.4, but at this moment compiling with clang is not yet supported.

### Libraries

* glibc
* libaio
* libgmp
* libgmpxx
* libgomp
* libicuuc
* libreadline
* libsctp
* libsnappy
* libuuid
* libz
* pthread

### Other programs

* git
* valgrind

### Platform-specific package install command lines

#### Ubuntu

```
apt-get install flex bison util-linux git build-essential uuid-dev libaio-dev libgmp-dev libsctp-dev lksctp-tools zlib1g-dev libicu-dev libreadline6-dev libsnappy-dev valgrind
```

#### CentOS

```
yum groupinstall "Development Tools" --exclude=git
yum install flex bison util-linux uuid-devel libaio-devel gmp-devel mpfr-devel libmpc-devel libuuid-devel glibc-devel libicu-devel lksctp-tools lksctp-tools-devel readline-devel zlib-devel snappy-devel valgrind
```

#### ArchLinux
```
pacman -S flex bison util-linux libaio gmp mpfr libmpc glibc icu lksctp-tools readline zlib snappy valgrind
```

## Retrieving the Stig source code

Currently the build system requires that the Stig source code be located in a directory named `src`.

The Stig source code is located in the [stigdb](http://github.com/stigdb/stigdb) repository on Github. To clone the repository:

```
git clone git://github.com/stigdb/stigdb.git ./src
```

Naturally, adjust the destination path above accordingly for your needs. Just be sure the code ends up in a directory named `src`.

## Build Commands

While Stig has a Makefile, it's just a basic wrapper for Stig's `starsha` build tool.

`starsha` creates a directory layout like so:

```
~
|-- stig
     |-- .starsha
     |-- out
     |-- src
```

After compilation completes, all binaries can be found under the `~/stig/out` directory. If you've run a debug build (the default build type), the binaries will be under `~/stig/out/debug`. If it was a release build (`make release`), the binaries will be under `~/stig/out/release`.

### make

Runs `bootstrap.sh`. This builds the `starsha` build tool and then builds the core Stig apps _in debug mode_. 

Behind the scenes, it's actually running these two commands:

```
make tools/starsha
make apps
```

> **NOTA BENE!** 
> The `starsha` build tool is designed to compile Stig as quickly as possible. In order to do this, it grabs as many system resources as it can. This means that running starsha _will peg your machine_. The build will finish relatively quickly, but in the duration you may find that other applications will not be very responsive.

### make test

Builds and then runs the Stig C++ unit test suite.

This is an optional step but is recommended.

These tests are built and run in debug mode. If the debug binaries do not yet exist in `~/stig/out/debug`, running `make test` will build these binaries before running the unit tests.

NOTE: A number of the tests require specialized permissions to run.

### make test_build

Builds the Stig C++ unit test suite but _does not_ run it.

If the debug binaries do not yet exist in `~/stig/out/debug`, running `make test_build` will build these binaries before building the unit tests.

### make test_lang

Builds and then runs the Stig language tests.

This is an optional step but is recommended. 

This script uses the [littleworkers](https://pypi.python.org/pypi/littleworkers) Python library to run tests in parallel. This library must be installed in order to run `make test_lang`.

While these tests do run in parallel for the number of cores available on your system, they still can take quite some time to complete.

If the debug binaries do not yet exist in `~/stig/out/debug`, running `make test_lang` will build these binaries before running the language tests.

NOTE: Your limit for number of open files must be greater than 4096, or some tests will spuriously fail.

### make install

Installs the Stig binaries. By default all binaries are installed under `/usr/local`.

To change the installation directory, define it in a `PREFIX` variable before running `make release`:

```
PREFIX=/installation/path ./bootstrap.sh
make release
make install
```

If the user performing the build does not have permission to write to the path defined in `PREFIX`, the installation must be run as root:

```
PREFIX=/installation/path ./bootstrap.sh
make release
sudo make install
```

> **NOTA BENE!**
> It is **not** advisable to run `make install` on a debug build. Debug binaries are not intended for production usage.

### make clean

Deletes the `../.starsha/.notes` file, the `../out` directory and the `starsha` binary.

This is an optional step. If you hit a build error, run this command before re-running the build.

## Creating a Stig disk volume

Stig databases are stored on their own block level device on the disk. This device is created and maintained using the [stig_dm](./stig_dm.md) utility.

For debug builds, `stig_dm` is located in `~/stig/out/debug/stig/indy/disk/util`.

For release builds, `stig_dm` is located in the directory specified in `PREFIX` at the start of the build. By default, that directory is `/usr/local/bin`.

More detailed information about `stig_dm` is available in [the documentation](./stig_dm.md). For the sake of simplicity, the below command will work for most initial purposes:

```
sudo ./stig_dm —la —le —create-volume —strategy=stripe —device-speed=slow —instance-name=demo —num-devices=1 —stripe-size=512 <DEVICE>
```
In the command above, please replace `<DEVICE>` with the name of the device which you wish to use for the Stig volume. For example, if you have the following devices:

```
stig@stig-VirtualBox:~$ df -h
Filesystem      Size  Used Avail Use% Mounted on
/dev/sda2       9.9G  5.3G  4.2G  56% /
none            4.0K     0  4.0K   0% /sys/fs/cgroup
udev            2.0G  4.0K  2.0G   1% /dev
tmpfs           396M  848K  395M   1% /run
none            5.0M     0  5.0M   0% /run/lock
none            2.0G  156K  2.0G   1% /run/shm
none            100M   40K  100M   1% /run/user
/dev/sda5        64Z   64Z  1.4G 100% /stig
```

The `<DEVICE>` in the command above would be replaced with `sda5`. Do not include the `/dev/`.

## Hello World

Follow the [Hello World directions](./hello_world.md) to create, compile, and run your first Stig operation.

## Platform-specific

### Ubuntu (13.10 and above)

TBD

### CentOS (6.4 and above)

TBD

## Troubleshooting

### make clean

If the build ever fails, please run the following before trying again:

```
make clean
```

### Build appears stuck at `[1] Jobs queued in wave` (or 0 or 2)

This is the [starsha infinite loop bug](https://github.com/StigDB/stigdb/issues/127). A workaround:

* Hit `ctrl-C` to break out of the build
* Type `touch stig/stig.nycr`
* Re-run your make command

### warning: memset used with constant zero length parameter

This error can occur during a `make release`. It is due to using an old version of gcc.

To resolve: Please upgrade to gcc 4.8.2 or newer.

Example of this error:

```
stig/indy/disk/util/stig_dm.o:
../out/release/stig/indy/disk/util/volume_manager.o (symbol from plugin): warning: memset used with constant zero length parameter; this could be due to transposed parameters
make: *** [release] Error 1
```

### warning: call to '__poll_chk_warn' declared with attribute warning

This error can occur during a `make release`. It is due to using an old version of gcc.

To resolve: Please upgrade to gcc 4.8.2 or newer.

Exmple of this error:

```
stig/core_import.o:
/usr/include/x86_64-linux-gnu/bits/poll2.h: In member function 'IoMain':
/usr/include/x86_64-linux-gnu/bits/poll2.h:41:60: warning: call to '__poll_chk_warn' declared with attribute warning: poll called with fds buffer too small file nfds entries [enabled by default]
  return __poll_chk (__fds, __nfds, __timeout, __bos (__fds));
                                                            ^
make: *** [release] Error 1
```

### Core dump during `make test`

Some of the tests require special (higher) limits for rtprio and memlock. To resolve this issue, edit `/etc/security/limits.conf` and set the rtprio and memlock values for the root user and any user which will be running tests or Stig binaries.

* `rtprio` should be set to 100 to allow the tests to boost thread priorities
* `memlock` should be set to the maximum amount of memory you expect your tests and server to allocate.

Example `/etc/security/limits.com` entries:

```
stig        -         rtprio          100
stig        -         memlock         2050504
root        -         rtprio          100
root        -         memlock         2050504
```

Example of this error:

```
stig@stig-VirtualBox:~/src$ make test
starsha stig/stig stig/server/stig stig/spa/spa stig/client stig/stig/indy/disk/util/stig_dm starsha/starsha starsha/dummy stig/core_import
[0] Jobs queued in wavestarsha --all-="*.test" --test
[0] Jobs queued in wavestig/indy/memory_layer.test:
terminate called after throwing an instance of 'std::system_error'
  what(): Cannot allocate memory
Aborted (core dumped)
make: *** [test] Error 1
stig@stig-VirtualBox:~/src$ 
```

### "ImportError: No module named littleworkers" during `make test_lang`

`make test_lang` runs the script `stig/lang_tests/run_tests.py`. This script uses the [littleworkers](https://pypi.python.org/pypi/littleworkers) Python library to run tests in parallel. This library must be installed in order to run `make test_lang`.

On Ubuntu, the command to install the library is:

```
sudo pip install littleworkers
```

### "No state file" during `make test_lang`

The "No state file" message will be interpretted as a test failure by the unit test framework. **This is a spurious error.** It occurs because the user which is running the test suite has maxed out on open files. The upper limit for number of open files must be greater than 4096 to get rid of these spurious errors.

To increase the open files allowed for the user, edit the `/etc/security/limits.conf' file accordingly. For example:

```
stig             soft    nofile          10000
stig             hard    nofile          20000
```

Now (post reboot) it will report:

```
stig@stig-VirtualBox:~/stig/src$ ulimit -Hn
20000
stig@stig-VirtualBox:~/stig/src$ ulimit -Sn
10000
```

You may now re-run `make test_lang`.

### Test failures during `make test_lang`

The language tests verify whether the language compiler functions as intended. Right now, there are a couple of situations where it **does not**. This means that sometimes tests will fail. And that's OK.

Take, for instance, the following output:

```
stig@stig-VirtualBox:~/stig/src$ make test_lang
starsha stig/stigc stig/server/stigi stig/spa/spa stig/client/stig_client stig/indy/disk/util/stig_dm starsha/starsha starsha/dummy stig/core_import
cd stig/lang_tests; ./run_tests.py
====================================================================
Changes: general/random.stig
Differs: Synth + Symbols
====================================================================
Changes: general/mutablefilter.stig
Differs: Synth + Symbols
Change: 
Pass: ... SNIP ...
Fail: general/random.stig,general/mutablefilter.stig
Overall: 0 changed, 116 passed, 2 failed
stig@stig-VirtualBox:~/stig/src$ 
```

This run of `make test_lang` ends with a report of:
```
Overall: 0 changed, 116 passed, 2 failed
```
The important thing to focus on here is **not** the `2 failed`, but rather the `0 changed`. This (plus the output of the `Change:` line for each of the tests) shows you that, even though the test is reported as failed in the `Synth + Symbols` area, the actual output is not different from the expected one. Therefore, even though the tests are reported as failures (at the synth & symbols compiler level), they in fact worked as expected.

TL;DR: If the test fails but there are no changes reported in the test, it is safe to ignore the failure. It's a bug we need to fix in the compiler, but it will not negatively effect your application.

## gcc compile tips

gcc can be a real bear to compile, but if your Linux distribution does not have a package available for a gcc version higher than 4.8.1, you'll need to compile it from source.

The [gcc installation docs](http://gcc.gnu.org/install/index.html) and [wiki](http://gcc.gnu.org/wiki/InstallingGCC) have a lot of good information on how to do this compile and installation from source. However, we've a few additional tips which may make the process go a little more smoothly:

* The easiest way to get all of the gcc dependencies downloaded and placed where the build process can locate them is to use the `./contrib/download_prerequisites` script in the gcc source directory.
* Other dependencies you may need to install (on Ubuntu): libcloog-isl-dev, gcc-multilib
* As well, since many of the libraries required to compile Stig are also necessary for compiling gcc, installing Stig pre-requisites before building gcc can sometimes make the process run more smoothly.
* We've found that the gcc build frequently will fail when building for Java compiling. As Stig has no need for this, we typically run `configure` with the `--enable-languages=c,c++` flag.
* Make sure to use `--prefix=` during configuration and set it to a directory which will be in your `$PATH`, `$LD_LIBRARY_PATH`, and `$LD_RUN_PATH` (or be sure to add it to these paths after the installation is complete).
* Building gcc takes a lot of space. Before starting, make sure that your build directory has at least 5GB of free space available.

For Ubuntu 13.10, it's possible to get a successful gcc build and installation with the following steps:

```
cd ~
sudo apt-get install flex bison util-linux git build-essential uuid-dev libaio-dev libgmp-dev libsctp-dev lksctp-tools zlib1g-dev libicu-dev libreadline6-dev libsnappy-dev valgrind libcloog-isl-dev gcc-multilib
sudo apt-get install g++
wget http://www.netgull.com/gcc/releases/gcc-4.8.2/gcc-4.8.2.tar.gz
tar zxvf gcc-4.8.2.tar.gz
cd gcc-4.8.2
./contrib/download_prerequisites
cd ..
mkdir build
cd build
../gcc-4.8.2/configure --enable-languages=c,c++
make
make test
sudo make install
```

-----

build_and_install.md Copyright 2010-2014 Stig LLC

build_and_install.md is licensed under a Creative Commons Attribution-ShareAlike 4.0 International License.

You should have received a copy of the license along with this work. If not, see <http://creativecommons.org/licenses/by-sa/4.0/>.
