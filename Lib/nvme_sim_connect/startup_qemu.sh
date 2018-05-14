./qemu-system-i386 \
    -M pc \
    -kernel ../../../buildroot/bzImage \
    -hda ../../../buildroot/rootfs.ext2 \
    -drive id=drv1,if=none,file=null-co://,format=raw \
    -device nvme,drive=drv1,serial=foo \
    -net nic,model=virtio\
    -net user\
    -append "root=/dev/sda console=ttyS0" \
    -nographic \
    -s \
    -trace enable=nvme*,file=nvme_trace.log

#    -append "root=/dev/sda console=ttyS0" \
#    -qdebug \
#    -drive file=../../../buildroot/rootfs.ext2,if=ide \
