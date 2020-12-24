if [ ! -d /sys/class/gpio/gpio116 ]; 
then 
    echo 116 > /sys/class/gpio/export
    echo out > /sys/class/gpio/gpio116/direction
    echo 0 > /sys/class/gpio/gpio116/value
else
    echo 1 > /sys/class/gpio/gpio116/value
    sleep 1s;
    echo 0 > /sys/class/gpio/gpio116/value
fi

tmpfile=/tmp/wifi_file.$$
touch $tmpfile
lsmod |grep 8192 1>$tmpfile

str=$(cat $tmpfile)

if [ -z "$str" ]; then 
    echo  1 > /proc/sys/net/ipv4/ip_forward
    insmod /home/root/app/drivers/8192eu.ko
fi
