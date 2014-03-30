# stig_dm: The Stig Disk Manager

## Synopsis

```
stig_dm --options-go-here device
```

## Description

Stig databases are stored on their own block level device on the disk. This device is created and maintained using the [stig_dm](./stig_dm.md) utility.

`stig_dm` provides functionality for creating, maintaining, and deleting Stig block-level devices. It supports both spinning disks and SSDs in both striped and chained configurations.

## Options

Please see `stig_dm --help` for a complete list of `stig_dm` options.

## Examples

### Creating a new Stig block-level dexvice

```
sudo stig_dm --la --le --create-volume --device-speed=slow --instance-name=my_db --num-devices=1 --stripe-size=512 sda5
```

## Troubleshooting

### "job threw standard exception"

This is, as you'd expect, an expected exception. It may safely be ignored.

An example of this:

```
stig@stig-VirtualBox:~/stig/packages$ sudo stig_dm --la --le --create-volume --device-speed=slow --instance-name=demo --num-devices=1 --stripe-size=512 sda5
stig_dm[2628]: log started
stig_dm[2628]: Performance degradation: please set rq_affinity [/sys/block/sda/queue/rq_affinity] for device [/dev/sda5] to 2
stig_dm[2628]: Performance degradation: please set rq_affinity [/sys/block/sda/queue/rq_affinity] for device [/dev/sda5] to 2
stig_dm[2628]: Creating volume with [1] devices for volume id [demo, 2]
stig_dm[2628]: worker 0x1fab130; job threw standard exception; Discard() runner shutting down.
stig_dm[2628]: worker 0x1facce0; job threw standard exception; Discard() runner shutting down.
stig_dm[2628]: log stopped
stig@stig-VirtualBox:~/stig/packages$
```

### "Performance degradation"

When it operates, `stig_dm` will suggest configuration changes which could further optimize its operation. Please see `stig_dm --help` for more information about the changes suggested in these recommendations.

Please see the ["job threw standard exception"](#job-threw-standard-exception) section above for an example of this type of recommendation.

### Volume not listed in `stig_dm --list`

If the user as whom the `stig_dm` command is being run does not have permission to read the device on which the volume exists, it will not appear in the `stig_dm --list` output.

To correct this problem, try running `sudo stig_dm --list` instead.

An example of a `stig_dm --list` which does not have permissions on the device:

```
stig@stig-VirtualBox:~/stig/packages$ stig_dm --list
|-------------|--------|----------------|------|------|----------------------|---------------------|--------|
|      Device | StigFS |      Volume Id |  Pos |  Tot | Logical Extent Start |  Logical Exten Size |   Kind |
|-------------|--------|----------------|------|------|----------------------|---------------------|--------|
|    /dev/sda |     NO |                |      |      |                      |                     |        |
|   /dev/sda1 |     NO |                |      |      |                      |                     |        |
|   /dev/sda2 |     NO |                |      |      |                      |                     |        |
|   /dev/sda5 |     NO |                |      |      |                      |                     |        |
|   /dev/sda6 |     NO |                |      |      |                      |                     |        |
|-------------|--------|----------------|------|------|----------------------|---------------------|--------|
```

The same command run as `sudo`:

```
stig@stig-VirtualBox:~$ sudo stig_dm --list
[sudo] password for stig:
|-------------|--------|----------------|------|------|----------------------|---------------------|--------|
|      Device | StigFS |      Volume Id |  Pos |  Tot | Logical Extent Start |  Logical Exten Size |   Kind |
|-------------|--------|----------------|------|------|----------------------|---------------------|--------|
|   /dev/sda5 |    YES |        demo, 1 |    0 |    1 |                    0 |          1498939392 | Stripe |
|-------------|--------|----------------|------|------|----------------------|---------------------|--------|
|    /dev/sda |     NO |                |      |      |                      |                     |        |
|   /dev/sda1 |     NO |                |      |      |                      |                     |        |
|   /dev/sda2 |     NO |                |      |      |                      |                     |        |
|   /dev/sda6 |     NO |                |      |      |                      |                     |        |
|-------------|--------|----------------|------|------|----------------------|---------------------|--------|
```

### Stig volume fails to mount on machine reboot

The file system used by Stig is not recognized by Linux. Therefore it will fail to mount on boot.

To avoid this problem, please remove the Stig-formatted volume from `/etc/fstab`. Stig will still be able to use the partition (as a raw block device) if it is not mounted.

-----

stig_dm.md Copyright 2010-2014 Stig LLC

stig_dm.md is licensed under a Creative Commons Attribution-ShareAlike 4.0 International License.

You should have received a copy of the license along with this work. If not, see <http://creativecommons.org/licenses/by-sa/4.0/>.
