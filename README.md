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

#for ipgw
    EspCompile ${CC} -shared ${DEBUG} -Wall -unused-result -DPIC -fPIC -I. -I/home/nixinlong/work/digit-nms/src/ipgw/mux  -I${APPINC} -I${INC} -L${LIBPATH} -Wl,--enable-new-dtags -Wl,-rpath,$ORIGIN/:/home/nixinlong/work/digit-nms/src/ipgw/mux/build/lib ${CFLAGS} ${LIBS} -L/home/nixinlong/work/digit-nms/src/ipgw/mux/build/lib -o ${MOD}${SHOBJ} ${SRC} ${LDFLAGS} -ltcpclient
#
    #EspCompile ${CC} -shared ${DEBUG} -Wall -unused-result -DPIC -fPIC -I. -I/home/stan/work/newsheng/hfc/mux  -I${APPINC} -I${INC} -L${LIBPATH} -Wl,--enable-new-dtags -Wl,-rpath,$ORIGIN/:/home/stan/work/newsheng/hfc/mux/build/lib ${CFLAGS} ${LIBS} -L/home/stan/work/newsheng/hfc/mux/build/lib -o ${MOD}${SHOBJ} ${SRC} ${LDFLAGS} -ltcpclient

    #esp compile for arm
    #EspCompile ${CC} -shared ${DEBUG} -Wall -DPIC -fPIC -I. -I/home/stan/work/newsheng/hfc/mux  -I/opt/eldk-4.0/arm/usr/include   -I${APPINC} -I${INC} -L${LIBPATH} -Wl,--enable-new-dtags -Wl,-rpath,$ORIGIN/:/usr/local/mux-arm/lib:/usr/local/mux-arm/muxnms/cache ${CFLAGS} ${LIBS} -L/home/stan/work/newsheng/hfc/mux/build/lib -o ${MOD}${SHOBJ} ${SRC} ${LDFLAGS} -ltcpclient



/*编译到设备侧运行*/
~/work/newsheng/hfc/mux$ :

    make -f Makefile.arm

    cd ../muxnms/

    esp clean

    ./esp.arm.compile.sh

    sudo -s

    cd /home/nfs/

    rm -rf build-arm/ mux-arm.tar.bz2

    cp /home/long/work/ipgw/muxnms/mux-arm.tar.bz2 .

    tar -jxvf mux-arm.tar.bz2

    chown root:root -R build-arm/mux-arm


telnet 192.168.1.49
    rm -rf /usr/local/mux-arm

    reboot

    mount -t nfs -o nolock 192.168.1.233:/home/nfs /mnt/nfs

    cd /mnt/nfs

    cp -a build-arm/mux-arm /usr/local/

    /usr/local/mux-arm/bin/appweb --home /usr/local/mux-arm/muxnms/ --show --config /usr/local/mux-arm/muxnms/appweb.conf&
