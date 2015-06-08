# ipgw


How to upgrade rootfs wdm 4100B
v0.0.3

update tar rootfs- lib folder into device rootfs /lib to update libc glibc
mux-arm-rootfs.tar.bz2



How to run appweb in arm
gcc version 4.0.0 (DENX ELDK 4.1 4.0.0)


ch root
cp appweb-5.2.0.tar.bz2 /home/nfs/source
cd /home/nfs/source
chown root:root appweb-5.2.0.tar.bz2
tar -jxvf appweb-5.2.0.tar.bz2

compile esp needa
/usr/local/lib/esp/5.2.0/bin/esp.conf
#option one to put file
1. cp -a mux-arm /usr/local/
2. tar -jcvf mux-arm.tar.bz2 -C /usr/local/

2. vi /etc/profile
export PATH="/usr/local/mux-arm/bin:/usr/bin:/bin:/usr/local/sbin:/usr/sbin:/sbin"
export LD_LIBRARY_PATH="/usr/local/mux-arm/lib:/usr/lib:/lib"

3.run

appweb --home /usr/local/mux-arm/muxnms/ --show --config /usr/local/mux-arm/muxnms/appweb.conf&

vi /usr/local/Dev_Info/dev_run.local


/*编译到设备侧运行*/
~/work/newsheng/hfc/mux$ :
	make -f Makefile.arm
	cd ../muxnms/
	esp clean
	./esp.arm.compile.sh
	sudo -s
	cd /home/nfs/
	rm -rf build-arm/ mux-arm.tar.bz2
	 cp /home/stan/work/newsheng/ipgw/muxnms/mux-arm.tar.bz2 .
	 tar -jxvf mux-arm.tar.bz2
	chown root:root -R build-arm/mux-arm

telnet 192.168.1.49
	rm -rf /usr/local/mux-arm
	reboot
	mount -t nfs -o nolock 192.168.1.249:/home/nfs /mnt/nfs
	cd /mnt/nfs
	cp -a build-arm/mux-arm /usr/local/
	/usr/local/mux-arm/bin/appweb --home /usr/local/mux-arm/muxnms/ --show --config /usr/local/mux-arm/muxnms/appweb.conf&
