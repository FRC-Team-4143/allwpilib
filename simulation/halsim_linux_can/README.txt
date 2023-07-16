#for Jetson Orin Nano untested
sudo busybox devmem 0x0c303018 w 0x458
sudo busybox devmem 0x0c303010 w 0x400
sudo modprobe can_raw
sudo modprobe can
sudo modprobe mttcan
sudo ip link set can0 up type can bitrate 250000
sudo ip link set up can0

