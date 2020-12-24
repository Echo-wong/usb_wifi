ROOT_DIR=/home/root/app
ifconfig wlan0 192.168.2.1
udhcpd -fS $ROOT_DIR/hostap/udhcpd.conf &
$ROOT_DIR/hostap/hostapd -d $ROOT_DIR/hostap/hostapd.conf 1>/dev/null  & 
iptables -t nat -A POSTROUTING -o eth1 -j MASQUERADE 
