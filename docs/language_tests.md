# Running Language Tests

As with most documents in this repository, this one is a work in progress. As items arise, we'll add them to this document. Should you think of or discover anything which should be included, please send a [pull request](./pull_request.md).

## What are language tests?

Stig uses a query language named _Stigscript_. Stigscript is used to write packages which not only interact with the database but also enhance the functionality of the system.

Part of the secret sauce which makes Stig so fast is that all packages are pre-compiled before you even get started. Without the overhead of an interpreted language, Stig is able to achieve blinding speeds.

The language tests exist to confirm that the [Stigscript compiler](./stigc.md) is doing the right thing when it compiles Stigscript files into packages.

## How to run language tests

Language tests may be run either in their entirety or one at a time.

### All tests

To run all of the language tests, `cd` to the top of the source directory (usually `~/stig/src`) and run `make test_lang`.

Should you experience any problems during this process, please see the [Troubleshooting](./build_and_install.md#troubleshooting) section of the [Building and Installing Stig](./build_and_install.md) documentation.

### Individual tests

To run an individual test, you must use the `run_tests.py` script. This script is located under `stig/lang_tests` in the source directory (usually `~/stig/src/stig/lang_tests`).

To run a test, simply declare the test name (with relative path) as the final argument to `run_tests.py`. You may declare multiple files here to run individual tests in series.

For example:

```
$ cd ~/stig/src/stig/lang_tests
$ ./run_tests.py general/lists.stig
Change:
Pass: general/lists.stig
Fail:
Overall: 0 changed, 1 passed, 0 failed
```

## run_tests.py Options

* `-c`: Print only the changes between the expected and actual states. If there are no changes, there will be no output.
* `-v`: Output the result of each and every test within a test file, rather than presenting results in aggregate.

## Interpreting the test output

Some functionality has not yet been completed in the [Stigscript compiler](./stigc.md). Therefore it is **expected** that some tests will fail.

To determine whether a test has, in fact, failed, you must check the value of the "Change:" field in the output. If there is no value here, the actual value matched the expected value. Therefore the test **did not** fail. The compiler may have some un-/under-implemented functionality, but it should not directly impact the performance of the software.

An example of some tests which report failure but are, in fact, OK:

```
$ ./run_tests.py general/random.stig
====================================================================
Changes: general/random.stig
Differs: Synth + Symbols
Change:
Pass:
Fail: general/random.stig
Overall: 0 changed, 0 passed, 1 failed

$ ./run_tests.py general/mutablefilter.stig
====================================================================
Changes: general/mutablefilter.stig
Differs: Synth + Symbols
Change:
Pass:
Fail: general/mutablefilter.stig
Overall: 0 changed, 0 passed, 1 failed
```
-----

language_tests.md Copyright 2010-2014 Stig LLC

language_tests.md is licensed under a Creative Commons Attribution-ShareAlike 4.0 International License.

You should have received a copy of the license along with this work. If not, see <http://creativecommons.org/licenses/by-sa/4.0/>.
