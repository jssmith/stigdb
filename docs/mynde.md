# Stig Mynde: memcached on Stig

In addition to it's own custom protocol, Stig speaks Memcached. This Memcached interface is named _Mynde_.

Since Memcached is available just about everywhere now, Mynde allows Stig to be more easily accessible from arbitrary languages, hosts, or platforms.

## Overview

Mynde aims to implement all of the memcached protocol and provide the same general guarantees as memcached.

## Quick Start

TBD

## Differences between Mynde and Memcached

### The effect of points of view

Because Mynde uses [Stig points of view](./pov.md) and tetris to resolve conflicting updates to the database rather than using locks, some operations may appear to produce different results. For example, when multiple clients increment the same key they may all get different result values. Nevertheless, all these increments will be counted and all will get one 'possible' value of the key, according to the client's personal [point of view](./pov.md).

### TTL of 0

Since Stig is a durable database rather than a cache, Mynde only allows a _time to live_ (aka _TTL_) of `0`. This means that, unlike in memcached, keys will live forever unless they are deleted. Under no circumstances will Stig Mynde automatically cull keys to reclaim space. Once written to the database, data remains in the database until explicitly deleted.

## Features

### Transactionality
Stig is transactional and can perform both multi-get and multi-set operations. Exact semantics around this are documented below.

### Consistency
All actions within a single connection happen in a consistent [Stig point of view](./pov.md). Specifically, when it recognizes a multi-get, Stig guarantees that every key in the multi-get is consistent. Exact rules for this with regards to different database operations appear below.

### Speed
Some operations are considerably faster when running on Stig than in memcached. This is because the lack of locking allows Stig to have less work to calculate the result. As Stig's dataset grows to exceed memory capacity, some operations will require disk access and will therefore take more time.

TODO: Update this section once we have numbers.

### Update Visibility
Stig requires all updates be placed in a private [Point of View](./pov.md). From there it will promote the updates to a shared or global point of view.

This maps to memcached in that each connection effectively lives in it's own Stig session with its own private point of view. As memcached commands are sent to Stig, the commands are evaluated in its point of view. The result (_deleted_, _not found_, _value_) is sent back to the user. This happens without waiting for the result to propagate to a shared point of view.

This works because most memcached operations don't have any preconditions required for them to pass. They just happen or they don't. That another session could have caused them to happen or not happen is inconsequential.

Stig guarantees that the results of every operation returned to the user is theoretically possible. As one example, if a delete and an insert happen in parallel, then which occurs first is non-deterministic / a race. Stig will effectively arbitrarily choose when it resolves the difference, but for the initial client calls, both will seem to work.

Every update will remain consistent within its session. Over time, if the update is not overwritten by other operations, other connections will see it after it propagates.

Some operations in Memcached (increment, decrement, prepend, append) modify data in place. Mynde always returns a valid result of the operation given one ordering of time, but exactly how the result appears when concurrency is resolved may differ.

## Command Semantics and Guarantees

The text below has not yet been edited for flow or accuracy.

### Compare and Set (CAS)

CAS operations are the only operations which we actually wait for the promotion to the global point of view to happen before
returning. This is because the semantics defined in the protocol spec require this behavior, and deviating from it modifies the
externally visible results.

### Multi-Get, Multi-Set
These are both transactional in Stig. How we recognize / start / end these varies on which protocol variant you're speaking.

TODO: At present there is no way to do a round of gets and sets together which are guaranteed to be consistent. All the gets will be in one consistent point of view. All the sets will apply to a wholly independent consistent state of the daabase.

### Binary protocol
There is no explicit multi-set or multi-get in the Binary protocol, so we recognize a series of quiet gets followed by anything or a series of quiet sets as one transaction / guaranteed consistent blob. If you want to break a stream of sets or gets into multiple different transactions simply inject an instruction into the stream to break the commands into pieces. A noop or touch (effectively noops since we don't do TTLs) command is recommended for this purpose.

Only quiet gets and quiet sets are watched for being multi-sets/multi-gets. Non-quiet get/set are

### Text Protocol
A get with multiple keys is considered multi-get. A series of independent 'get' commands is considered to be independent transactions.

A series of set commands will be soemantically recognized as a multi-set.

CAS sets are considered independent operations. This could be changed in the future, but for now it's simplest.

### Increment, Decrement
The exact value returned is always a theoretically possible value for the key. It is entirely possible no one else will
ever see it because the value is overwritten, the increment/decrement is combined with others (The operations are NOT
serialized, so multiple people can increment and get the same result).

We don't do any sort of recognition of increment/decrement commands as multi-sets at this juncture. In the future we may
consider a stream of quiet increment/decrement commands. TODO: Revisit this with users to see if they want these to be rolled
into a transaction (Which would be necessary to use this for any sort of credits balance)

### Flush All
The behavior here is TBD. Not currently supported

### Touch
Touch is a no-op since we don't do TTLs

### Append / Prepend
TODO / TBD

### Add
TODO / TBD

### Replace
TODO / TBD

-----

mynde.md Copyright 2010-2014 Stig LLC

mynde.md is licensed under a Creative Commons Attribution-ShareAlike 4.0 International License.

You should have received a copy of the license along with this work. If not, see <http://creativecommons.org/licenses/by-sa/4.0/>.
