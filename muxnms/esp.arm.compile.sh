 
rm -rf cache/*

CC=/opt/eldk-4.0/usr/bin/arm-linux-gcc LD=/opt/eldk-4.0/usr/bin/arm-linux-ld AR=/opt/eldk-4.0/usr/bin/arm-linux-ar esp --platform /home/nfs/source/appweb-5.2.0/build/linux-arm-debug --appweb ./appweb.conf compile

rm -rf ../build-arm/mux-arm/muxnms/cache/*
arm-linux-strip cache/*.so
cp -a cache/*.so ../build-arm/mux-arm/muxnms/cache/

rm -rf ../build-arm/mux-arm/muxnms/client/*
cp -a client/* ../build-arm/mux-arm/muxnms/client/

rm -rf ../build-arm/mux-arm/muxnms/db/*
cp -a db/* ../build-arm/mux-arm/muxnms/db/

tar -jcvf mux-arm.tar.bz2 ../build-arm/mux-arm
