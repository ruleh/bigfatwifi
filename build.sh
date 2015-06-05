#!/bin/bash

TOOLCHAIN="/home/gustavo/toolchain/bin/arm-cortex_a9-linux-gnueabihf-"
STRIP="/home/gustavo/toolchain/bin/arm-cortex_a9-linux-gnueabihf-strip"
OUTDIR="out"
CWM_INITRAMFS_SOURCE="/home/gustavo/kernel/usr/initramfs/cwm.list"
TWRP_INITRAMFS_SOURCE="/home/gustavo/kernel/usr/initramfs/twrp.list"
RAMDISK="/home/gustavo/ramdisk"
RAMDISK_LP="/home/gustavo/ramdisk_lp"
RAMDISK_OUT="/home/gustavo/kernel/usr/initramfs/ramdisk.cpio"
MODULES=("/home/gustavo/kernel/net/sunrpc/auth_gss/auth_rpcgss.ko" "/home/gustavo/kernel/fs/cifs/cifs.ko" "drivers/net/wireless/bcmdhd/dhd.ko" "/home/gustavo/kernel/fs/lockd/lockd.ko" "/home/gustavo/kernel/fs/nfs/nfs.ko" "/home/gustavo/kernel/net/sunrpc/auth_gss/rpcsec_gss_krb5.ko" "drivers/scsi/scsi_wait_scan.ko" "drivers/samsung/fm_si4709/Si4709_driver.ko" "/home/gustavo/kernel/net/sunrpc/sunrpc.ko")
KERNEL_DIR="/home/gustavo/kernel"
MODULES_DIR="/home/gustavo/kernel/out/system/lib/modules"
CURRENTDATE=$(date +"%d-%m")

case "$1" in
	clean)
        cd ${KERNEL_DIR}
        make clean && make mrproper
		;;
	kk)
        # compress the ramdisk in cpio
        cd ${RAMDISK}
        rm *.cpio
        find . -not -name ".gitignore" | cpio -o -H newc > ${RAMDISK_OUT}
        
        cd ${KERNEL_DIR}
        make -j3 kernel_defconfig ARCH=arm CROSS_COMPILE=${TOOLCHAIN}

        # build modules first to include them into zip file
        make -j3 ARCH=arm CROSS_COMPILE=${TOOLCHAIN} modules
       
        for module in "${MODULES[@]}" ; do
            cp "${module}" ${MODULES_DIR}
            ${STRIP} --strip-unneeded ${MODULES_DIR}/*
        done
      
        # build the CWM kernel with trim
        cd ${KERNEL_DIR}
        make -j3 ARCH=arm CROSS_COMPILE=${TOOLCHAIN} CONFIG_INITRAMFS_SOURCE=${CWM_INITRAMFS_SOURCE}
        cp arch/arm/boot/zImage ${OUTDIR}
        cd ${OUTDIR}
		echo "Creating kk CWM kernel zip..."
        zip -r kk-kernel-$CURRENTDATE-CWM-TRIM.zip ./ -x *.zip *.gitignore
        # build the TWRP kernel with trim
        cd ${KERNEL_DIR}
        make -j3 ARCH=arm CROSS_COMPILE=${TOOLCHAIN} CONFIG_INITRAMFS_SOURCE=${TWRP_INITRAMFS_SOURCE}
        cp arch/arm/boot/zImage ${OUTDIR}
        cd ${OUTDIR}
		echo "Creating kk TWRP kernel zip..."
        zip -r kk-kernel-$CURRENTDATE-TWRP-TRIM.zip ./ -x *.zip *.gitignore
        
         # build the CWM kernel
        cd ${KERNEL_DIR}
        patch -Rp1 < trim.patch
        make -j3 ARCH=arm CROSS_COMPILE=${TOOLCHAIN} CONFIG_INITRAMFS_SOURCE=${CWM_INITRAMFS_SOURCE}
        cp arch/arm/boot/zImage ${OUTDIR}
        cd ${OUTDIR}
		echo "Creating kk CWM kernel zip..."
        zip -r kk-kernel-$CURRENTDATE-CWM.zip ./ -x *.zip *.gitignore
        # build the TWRP kernel
        cd ${KERNEL_DIR}
        make -j3 ARCH=arm CROSS_COMPILE=${TOOLCHAIN} CONFIG_INITRAMFS_SOURCE=${TWRP_INITRAMFS_SOURCE}
        cp arch/arm/boot/zImage ${OUTDIR}
        cd ${OUTDIR}
		echo "Creating kk TWRP kernel zip..."
        zip -r kk-kernel-$CURRENTDATE-TWRP.zip ./ -x *.zip *.gitignore
        
        cd ${KERNEL_DIR}
        patch -p1 < ${KERNEL_DIR}/trim.patch
        
		echo "Done!"
	    ;;
	  lp)
	    # compress the ramdisk in cpio
        cd ${RAMDISK_LP}
        rm *.cpio
        find . -not -name ".gitignore" | cpio -o -H newc > ${RAMDISK_OUT}
        
	    cd ${KERNEL_DIR}
        make kernel_defconfig ARCH=arm CROSS_COMPILE=${TOOLCHAIN}

        # build modules first to include them into zip file
        make -j3 ARCH=arm CROSS_COMPILE=${TOOLCHAIN} modules
       
        for module in "${MODULES[@]}" ; do
            cp "${module}" ${MODULES_DIR}
            ${STRIP} --strip-unneeded ${MODULES_DIR}/*
        done
      
        # build the CWM lollipop kernel
        cd ${KERNEL_DIR}
        make -j3 ARCH=arm CROSS_COMPILE=${TOOLCHAIN} CONFIG_INITRAMFS_SOURCE=${CWM_INITRAMFS_SOURCE} zImage
        cp arch/arm/boot/zImage ${OUTDIR}
        cd ${OUTDIR}
		echo "Creating lp kernel zip..."
        zip -r lp-kernel-$CURRENTDATE-CWM.zip ./ -x *.zip *.gitignore
        
         # build the TWRP lollipop kernel
        cd ${KERNEL_DIR}
        make -j3 ARCH=arm CROSS_COMPILE=${TOOLCHAIN} CONFIG_INITRAMFS_SOURCE=${TWRP_INITRAMFS_SOURCE}
        cp arch/arm/boot/zImage ${OUTDIR}
        cd ${OUTDIR}
		echo "Creating kk TWRP kernel zip..."
        zip -r lp-kernel-$CURRENTDATE-TWRP.zip ./ -x *.zip *.gitignore
        
		echo "Done!"
esac
