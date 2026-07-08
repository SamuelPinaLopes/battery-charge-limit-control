# Battery limit control

Setups a battery limit automatically when booting or rebooting the laptop.

What this is?
Is a program that uses linux filesystem to control the battery_limit_threshold, after boot
or reboot my laptop, replaces the default battery charge limit to my own custom battery charge
limit.

How it works?
This works changing the value inside battery_charge_threshold file inside /sys folders.

To define a charge threshold limit use the command called in terminal bset. Type bset --help
to see all of its options such as:
- make an update;
- change default settings;
- show current services or extra actions;