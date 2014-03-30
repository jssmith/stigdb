# Stig Indy Server

`stigi` is the program for the Stig Indy server. This is the server used in both production and development environments. It is a replicated key-value database server.

## stigi Options

* `--create`: Denotes whether to initialize a Stig instance. Possible values: `true`, `false`. This parameter should only be set to `true` if the `stigi` server had not yet been run against the specified database instance.

## Troubleshooting

### "Corrupt data Reading" in `/var/log/syslog`
If the `stigi` server dies with a message of "Corrupt data Reading" in `/var/log/syslog`, the problem is that the server has been started without initializing the database instance using `--create=true`.

An example of this error:

```
stig@stig-VirtualBox:~$ sudo stigi --create=false --la --le --iname=demo --starting_state=SOLO
...
stigi[2344]: TPool [Entry] allocated [32056416] bytes for [143109] blocks of size [224]
stigi[2344]: TBufBlock allocated [351666176] bytes for [5366] blocks of size [65536]
stigi[2344]: Performance degradation: please set rq_affinity [/sys/block/sda/queue/rq_affinity] for device [/dev/sda5] to 2
stigi[2344]: Assigning Device [/dev/sda5] to core [1] because pos [0]
stigi[2344]: Corrupt data Reading @ [65536] in device [/dev/sda5] from [[stig/indy/disk/util/disk_engine.h, 200]]
stig@stig-VirtualBox:~$
```
-----

stigi.md Copyright 2010-2014 Stig LLC

stigi.md is licensed under a Creative Commons Attribution-ShareAlike 4.0 International License.

You should have received a copy of the license along with this work. If not, see <http://creativecommons.org/licenses/by-sa/4.0/>.
