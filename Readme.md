# Battery limit control

Setups a battery limit automatically when booting or rebooting a laptop.

## What is this?
Is a program that uses linux filesystem to control battery charge limit, after boot or reboot a laptop. It replaces default battery charge limit to your own custom battery limit.

### How it works?
This works changing the value inside battery_charge_threshold file inside /sys/ folder.

### How to use it?
To use this program you MUST run it as sudo! sudo is required due linux filesystem security permissions.

***Note:***
"bat" is the default name used to call this program.
If you want, you can change this name to anything else. **Do not forget the name you gave it** if you create your own name or add to your .bashrc file as an alias.

Type --help to display info:
`sudo bat --help`

## Installation
### Step 1:
First copy the compile program from builds folder to /usr folder.

`sudo cp builds/battery_limit_manager /usr/local/bin/`

### Step 2:
Copy the service file from src folder to systemd folder.

`sudo cp  src/service_files/battery_limit_manager.service  /etc/systemd/system/`

### Step 3:
After copy the file, enable it with systemctl.

`systemctl enable --now battery_limit_manager.service`

### Step 4:
Create a link to the program.

`ln -s /usr/local/bin/battery_limit_manager /usr/local/bin/bat`

### Step 5:
Run a test.

`sudo bat --help`

## Unninstall
### Step 1:
Disable its deamon.

`systemctl disable battery_limit_manager.service`

### Step 2:
Remove files.

`sudo rm -r /usr/local/bin/battery_limit_manager /usr/local/bin/bat /etc/systemd/system/battery_limit_manager.service`
