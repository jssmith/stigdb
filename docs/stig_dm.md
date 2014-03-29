# stig_dm: The Stig Disk Manager

## Synopsis

``` 
stig_dm --options-go-here device
```

## Description

foo

## Examples

### Creating a new Stig block-level device

```
sudo stig_dm --la --le --create-volume --device-speed=slow --instance-name=my_db --num-devices=1 --stripe-size=512 sda5
```

-----

stig_dm.md Copyright 2010-2014 Stig LLC

stig_dm.md is licensed under a Creative Commons Attribution-ShareAlike 4.0 International License.

You should have received a copy of the license along with this work. If not, see <http://creativecommons.org/licenses/by-sa/4.0/>.
