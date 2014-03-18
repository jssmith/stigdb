# INSTALLING and RUNNING STIG

## Quick Start

## Configuration

Stig requires no up-front configuration. When run, it will analyze your system and select sane operating defaults based upon the system's capabilities.

If these defaults prove inadequate for your needs, you may set [configuration options](./config_options.md) by way of a `.ini` file.

## Binaries

By default, all binaries are installed under `/usr/local`. To change the default location, you may set the installation directory by...

TBD

## Creating the disk image

Because of the specialized nature of its storage requirements, Stig must maintain its database files in a separate partition/volume.

To create the disk image, run the Stig disk manager: `stig_dm`.

**WARNING!** `stig_dm` will overwrite and destroy any data which exists in the selected partition.

### Running in memory simulation mode

## Compile a Stig package

## Run the Stig server

## Troubleshooting
