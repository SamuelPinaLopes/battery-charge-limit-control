import sys

flag = sys.argv[1]

# open the file
with open("/etc/BatterYLimiT/setup.conf", 'r') as config:
    # get the default threshold limit
    if flag == "--threshold":
        for line in config:
            if "default_limit" in line:
                print(line[len(line)-2:])


    # get the device's battery directory path 
    elif flag == "--Dir_power":
        print("want to know the default power_supply directory for battery info...")


    # knows if this device is already setup or not
    elif flag == "--setup":
        print("want to know if the device is already fully setup...")
    
