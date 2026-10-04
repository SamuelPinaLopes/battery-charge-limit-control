# Battery limit control

Setups a battery limit automatically when booting or rebooting the laptop.


What this is?
Is a program that uses linux filesystem to control the battery_limit_threshold, after boot
or reboot a laptop, it replaces the default battery charge limit to your own custom battery
charge limit.


How it works?
This works changing the value inside battery_charge_threshold file inside /sys folders.


How to use it?
To use this program you MUST run it as sudo.
Type --help to know what you can do with it.

--> sudo bat --help (prints help screen)


How to install it?
Step 1: First copy the compile program from builds folder to /usr folder.

--> sudo cp builds/battery_limit_manager /usr/local/bin/


Step 2: Copy the service file from src folder to systemd folder.

--> sudo cp  src/service_files/battery_limit_manager.service  /etc/systemd/system/


Step 3: After copy the file, enable it with systemctl.

--> systemctl enable --now battery_limit_manager.service


Step 4: Create a link to the program.

ln -s /usr/local/bin/battery_limit_manager /usr/local/bin/bat

Note: "bat" is the name that you will use to call this program.
If you want you can change this name to anything else. just don't forget it.


Step 5: Run a test.

--> sudo bat --help

Note: If you create a different name in step 4, use the exact same name where is "bat".
