import sys
from pathlib import Path


# checking if the configuration exists
if Path("/etc/BatterYLimiT/setup.conf").exists():

    # checking if the argument as passed
    if len(sys.argv[1:]) > 0:

        # taking the previous argument
        flag = sys.argv[1]

        # open the file
        with open("/etc/BatterYLimiT/setup.conf", 'r') as config:
            
            # get the default threshold limit
            if flag == "--threshold":
                for line in config:
                    if "default_limit" in line:
                        print(line[-3:])

            # knows if this device is already setup or not
            elif flag == "--setup":
                for line in config:
                    if "already_setup=1" in line:
                        print(1)

            # get default charge limit
            elif flag == "--default_limit":
                for line in config:
                    if "default_limit" in line:
                        print(line[-3:].replace("\n",""), end="")


            # get current limit
            elif flag == "--get_current_limit":
                with open("/sys/class/power_supply/BAT0/charge_control_end_threshold") as chargeThreshold:
                    print(chargeThreshold.read())
            

            # for unknown/wrong values
            else:
                print(f"flag error!\nunknown flag: {flag}")
    
    else:
        print("missing arguments error...")

else:
    print(0)