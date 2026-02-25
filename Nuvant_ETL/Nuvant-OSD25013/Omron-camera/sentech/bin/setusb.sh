 setusb.sh
#!/bin/bash

USBFSVALUE=0
HR="-------------------------------------------------------------------"
echo ""
echo $HR
echo "OMRON SENTECH CO., LTD. (C) 2017"
echo "This script performs the following USB configuration:"
echo "1. Maximize usbfs memory limit"
echo "2. Disable usb autosuspend"
echo ""

# Set USBFS memory limit
echo $HR
echo "- maximize usbfs memory limit"
echo "Current usbfs memory limit is `cat /sys/module/usbcore/parameters/usbfs_memory_mb`"
if [[ $EUID -ne 0 ]]; then
    sudo sh -c "echo $USBFSVALUE > /sys/module/usbcore/parameters/usbfs_memory_mb"
    RES0=$?
    if [[ "$RES0" = "127" ]]; then
        echo "sudo command not found. Please either install sudo or login as superuser before executing this script."
        exit 1
    fi
else
    echo $USBFSVALUE > /sys/module/usbcore/parameters/usbfs_memory_mb
    RES0=$?
fi
VALUE=`cat /sys/module/usbcore/parameters/usbfs_memory_mb`
RES1=$?
if [[ $RES0 = 0 && $RES1 = 0 && $VALUE = 0 ]]; then
    RESULT="Success!"
else
    RESULT="Failed! Current value is $VALUE [Error code: $RES0 $RES1]";
fi
echo "Maximize usbf memory limit (set to $USBFSVALUE until reboot) : $RESULT"
echo "To permanently set the memory limit, edit your boot script by inserting the following kernel parameter:"
echo "usbcore.usbfs_memory_mb=$USBFSVALUE"

# disable autosuspend
echo $HR
echo "2. Disable USB autosuspend:"
echo "Current usb autosuspend value is `cat /sys/module/usbcore/parameters/autosuspend`"
if [[ $EUID -ne 0 ]]; then
    sudo sh -c "echo -1 > /sys/module/usbcore/parameters/autosuspend"
    RES0=$?
    if [[ "$RES0" = "127" ]]; then
        echo "sudo command not found. Please either install sudo or login as superuser before executing this script."
        exit 1
    fi
else
    echo -1 > /sys/module/usbcore/parameters/autosuspend
    RES0=$?
fi
if [[ $RES0 = 0 ]]; then
    RESULT="Success!"
else
    RESULT="Failed! [Error code: $RES0]"
fi
echo "Disabling USB-auto suspend (set to -1 until reboot): $RESULT"
echo "To permanently disable the auto-suspend, edit /boot/extlinux/extlinux.conf and append:"
echo "usbcore.autosuspend=-1"

echo $HR
echo "Please refer to your board documentation to further optimize the performance."
echo $HR
echo ""

