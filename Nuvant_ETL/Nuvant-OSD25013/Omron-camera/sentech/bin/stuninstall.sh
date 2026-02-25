#!/bin/bash
removedirfile()
{
    if [[ $EUID -ne 0 ]]; then
        sudo bash -c "rm -rf $1"
        R=$?
        if [[ $R = 127 ]]; then
            echo "sudo command not found. Please either install sudo or login as superuser before executing this script."
            exit 1
        elif [ "?" = "1" ]; then
            echo "Either sudo configuration is invalid or permission denied (user is not in the sudoers file)."
            echo "Please login as superuser and re-execute this script."
            exit 1
        fi
    else
        rm -rf $1
        R=$?
    fi
    if [ $R -ne 0 ]; then
        echo "Error removing $1. Uninstallation terminated. [Error code: $R]"
        echo "Please manually remove $1."
        exit 1
    fi
}

echo ""
echo "======================================================================="
echo "Uninstallation script: SentechSDK 1.1.2-Update5"
echo "Installed location: /opt/sentech"
echo "(C)2021 OMRON SENTECH CO., LTD"
echo "Contact/Support: techsupport-ose@omron.com"
echo "http://www.sentech.co.jp/"
echo "======================================================================="
echo ""
echo "Uninstallation will remove the following: "
echo "  /opt/sentech and all files/directories inside /opt/sentech/*"
echo "  /etc/udev/rules.d/30-stcam.rules"
echo ""
echo -n "Continue uninstallation process? [y/N] : [default: N] "
read yesno
if [ "$yesno" = "y" ] || [ "$yesno" = "Y" ]; then
    removedirfile /opt/sentech
    removedirfile /etc/udev/rules.d/30-stcam.rules
    echo "Uninstallation is completed."
    echo "If you appended /opt/sentech/.stprofile to your login script or copied it to /etc/profile.d/stprofile.sh, please remove it manually."
    echo "If you appended /opt/sentech/stldlib.conf to /etc/ld.so.conf.d/, please remove it manually and run ldconfig."
    if [ -d "/root/.sentech" ]; then
        echo "Directory /root/.sentech exists. If no longer used, please remove manually."
    fi
else
    echo "Uninstallation is cancelled."
    exit 
fi
echo ""
