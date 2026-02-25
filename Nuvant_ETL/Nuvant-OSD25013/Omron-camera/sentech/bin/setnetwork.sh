# setnetwork.sh
#!/bin/bash

MTUVAL=9000 
#MEMMAX=33554432
#MEMMAX=16777216
MEMMAX=8388608

SUERROR="sudo command not found. Please either install sudo or login as superuser before executing this script."
HR="-------------------------------------------------------------------"
echo 
echo $HR
echo "OMRON SENTECH CO., LTD. (C) 2018"
echo "This script performs the following network configuration:"
echo "1. Reverse path filtering setting (default: no changes)"
echo "2. Jumbo frame setting (default MTU=$MTUVAL)"
echo "3. Packet memory buffer setting (max=$MEMMAX)"
echo ""
if [ -z $1 ];
then
    echo "Usage parameter: <iface>"
    echo "  where <iface> is the network interface of which MTU to configure."
    echo 
    ip -4 address show
    echo
    echo "Example: ./setnetwork.sh eth0"
    echo $HR
    echo ""
    exit;
fi

# Set the reverse path filter to loose:
echo $HR
echo "1. Reverse path filtering setting:"
rplist=(all default $1)
for i in ${rplist[@]}; do
    echo "Current reverse path filtering setting for $i is `cat /proc/sys/net/ipv4/conf/$i/rp_filter`"
done
echo ""
echo "In case that a GigE Camera is in different network and could not be detected, please try to alternate the setting:"
echo "(The setting will be applied to the configurations above)"
echo "0: no source validation"
echo "1: RFC3704 strict reverse path"
echo "2: RFC3704 loose reverse path (recommended)"
echo "3: Keep current setting (no changes)"
echo -n "Default [3] : "
read RPVALUE
if [ -z "$RPVALUE" ]; then
    RPVALUE="3"
fi
if [[ $RPVALUE = 0 || $RPVALUE = 1 || $RPVALUE = 2 ]]; then
    for i in ${rplist[@]}; do
        if [[ $EUID -ne 0 ]]; then
            sudo sh -c "echo $RPVALUE > /proc/sys/net/ipv4/conf/$i/rp_filter"; 
            RES0=$?
            if [[ "RES0" = "127" ]]; then
                echo $SUERROR
                exit 1
            fi
        else
            echo $RPVALUE > /proc/sys/net/ipv4/conf/$i/rp_filter
            RES0=$?
        fi
        if [[ $RES0 = 0 ]]; then
            echo "Setting reverse path filtering to $RPVALUE for $i: Success!"
        else
            echo "Setting reverse path filtering to $RPVALUE for $i: Failed! [Error code: $RES0]"
        fi
    done
else
    echo "Setting reverse path filtering is skipped."
fi

# Set jumbo frame
echo $HR
echo "2. Jumbo frames setting:"
while true; do
    echo -n "Input MTU value (leave empty to use default value $MTUVAL) : "
    read INPUTVALUE
    if [ -z "$INPUTVALUE" ]; then
        INPUTVALUE=$MTUVAL
    fi
    re='^[0-9]+$'
    if ! [[ $INPUTVALUE =~ $re ]] ; then
        echo "MTU value must be a number".
    else
        MTUVAL=$INPUTVALUE
        break;
    fi
done
if [[ $EUID -ne 0 ]]; then
    sudo sh -c "ip link set dev $1 mtu $MTUVAL"
    RES0=$?
    if [[ "RES0" = "127" ]]; then
        echo $SUERROR
        exit 1
    fi
else
    ip link set dev $1 mtu $MTUVAL
    RES0=$?
fi
if [[ $RES0 = 0 ]]; then
    RESULT="Success!"
else
    RESULT="Failed! [Error code: $RES0]"
fi
echo "Set MTU to $MTUVAL (change is discarded when reboot): $RESULT"
ip address | grep $1
echo "To permanently change MTU size, edit the network script's MTU value"

# Increase read/write memory buffer
echo $HR
echo "3. Packet memory buffer setting:"
while true; do
    echo -n "Input socket buffer size (leave empty to use default value $MEMMAX) : "
    read INPUTVALUE
    if [ -z "$INPUTVALUE" ]; then
        INPUTVALUE=$MEMMAX
    fi
    re='^[0-9]+$'
    if ! [[ $INPUTVALUE =~ $re ]] ; then
        echo "Buffer size value must be a number".
    else
        MEMMAX=$INPUTVALUE
        break;
    fi
done
paramlist=(rmem_max wmem_max rmem_default wmem_default)
for item in ${paramlist[*]}
do
    if [[ $EUID -ne 0 ]]; then
        sudo sh -c "sysctl -w net.core.$item=$MEMMAX"
        RES0=$?
        if [[ "$RES0" = "127" ]]; then
            echo $SUERROR
            exit 1
        fi
    else
        sysctl -w net.core.$item=$MEMMAX
        RES0=$?
    fi
    if [[ $RES0 = 0 ]]; then
        echo "Success to update net.core.$item=$MEMMAX (change is discarded when reboot)"
    else
        echo "Failed to update net.core.$item. [Error code: $RES0]"
    fi
done
echo $HR
echo "To permanently change the sysctl settings, edit /etc/sysctl.conf"
echo "Please refer to your Linux distribution manual for the detail."
echo $HR
echo ""

echo -n "Restart network now ? [Y/n] : [default: y] "
read yesno
if [ "$yesno" = "n" ]; then
    echo "Please manually restart the network."
else
    if [ -f /etc/init.d/network ]; then
        CMD="service network restart"
    elif [ -f /etc/init.d/networking ]; then
        CMD="service networking restart"
    else
        CMD="service network-manager restart"
    fi
    if [[ $EUID -ne 0 ]]; then
        sudo $CMD
        RES0=$?
        if [[ "$RES0" = "127" ]]; then
            echo $SUERROR
            exit 1
        fi
    else
        $CMD
        RES0=$?
    fi
    if [[ $RES0 = 0 ]]; then
        echo "Restart network: Success!"
    else
        echo "Restart network: Failed! [Error code: $RES0]" 
        echo "Please refer to your Linux distribution manual for manually restart the network service."
    fi
fi

echo $HR
echo "Please refer to your board documentation to further optimize the performance."
echo $HR
echo ""

