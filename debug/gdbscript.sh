gdb grub/noOs.bin \
-ex 'target remote localhost:1234' \
-ex 'layout src' \
-ex 'layout regs' \
-ex 'break _start' \
-ex 'break keyboard_isr'
#-ex 'break test_irq' \
#-ex 'break irq1_wrapper'
