gdb grub/noOs.bin \
-ex 'target remote localhost:1234' \
-ex 'layout src' \
-ex 'layout regs' \
-ex 'break keyboard_isr' \
