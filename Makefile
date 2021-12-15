obj-m := myled.o #←<ターゲット>: <必要なファイル>と書く

myled.ko: myled.c
		make -C /usr/src/linux-headers-`uname -r` M=`pwd` V=1 modules

clean:
		make -C /usr/src/linux-headers-`uname -r` M=`pwd` V=1 clean
