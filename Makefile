LIBKERNEL = kernel
LIBBOOT = boot
LIBDRIVER = drivers

KERNEL_COMPONENTS := $(shell find $(LIBKERNEL) -mindepth 1 -maxdepth 1 -type d)
BOOT_COMPONENTS := $(shell find $(LIBBOOT) -mindepth 1 -maxdepth 1 -type d)
DRIVER_COMPONENTS := $(shell find $(LIBDRIVER) -mindepth 1 -maxdepth 1 -type d)

KERNEL_SOURCES_C := $(foreach d, $(KERNEL_COMPONENTS), $(wildcard $d/*.c))
KERNEL_SOURCES_ASM := $(foreach d, $(KERNEL_COMPONENTS), $(wildcard $d/*.asm))
KERNEL_OBJS := $(KERNEL_SOURCES_ASM:%.asm=%.o) $(KERNEL_SOURCES_C:%.c=%.o)

BOOT_SOURCES_C := $(foreach d, $(BOOT_COMPONENTS), $(wildcard $d/*.c))
BOOT_SOURCES_ASM := $(foreach d, $(BOOT_COMPONENTS), $(wildcard $d/*.asm))
BOOT_OBJS := $(BOOT_SOURCES_ASM:%.asm=%.o) $(BOOT_SOURCES_C:%.c=%.o)

DRIVER_SOURCES_C := $(foreach d, $(DRIVER_COMPONENTS), $(wildcard $d/*.c))
DRIVER_SOURCES_ASM := $(foreach d, $(DRIVER_COMPONENTS), $(wildcard $d/*.asm))
DRIVER_OBJS := $(DRIVER_SOURCES_ASM:%.asm=%.o) $(DRIVER_SOURCES_C:%.c=%.o)

ALL_OBJS := $(KERNEL_OBJS) $(BOOT_OBJS) $(DRIVER_OBJS)
SERIAL_OBJS := $(foreach obj, $(ALL_OBJS), $(obj).serial)

$(info $(SERIAL_OBJS))

KERNEL_INCLUDE_GCC = $(foreach d, $(KERNEL_COMPONENTS), -I$(subst ,,$d))
DRIVER_INCLUDE_GCC = $(foreach d, $(DRIVER_COMPONENTS), -I$(subst ,,$d))
BOOT_INCLUDE_GCC = $(foreach d, $(BOOT_COMPONENTS), -I$(subst ,,$d))

KERNEL_INCLUDE_NASM = $(foreach d, $(KERNEL_COMPONENTS), -i$(subst ,,$d))
DRIVER_INCLUDE_NASM = $(foreach d, $(DRIVER_COMPONENTS), -i$(subst ,,$d))
BOOT_INCLUDE_NASM = $(foreach d, $(BOOT_COMPONENTS), -i$(subst ,,$d))

INCLUDE_GCC = $(BOOT_INCLUDE_GCC) $(KERNEL_INCLUDE_GCC) $(DRIVER_INCLUDE_GCC)
INCLUDE_NASM = $(BOOT_INCLUDE_NASM) $(KERNEL_INCLUDE_NASM) $(DRIVER_INCLUDE_NASM)

CFLAGS = -c -g -ggdb -std=gnu99 -ffreestanding -Wall -Wextra $(INCLUDE_GCC)
SERIAL=-DSERIAL

all: clean grub/noOs.iso grub/noOs-serial.iso

.PRECIOUS: grub/noOs.bin grub/noOs-serial.bin

.PHONY: run
run:
	qemu-system-i386 -d int -cdrom grub/noOs.iso

.PHONY: rund
rund:
	qemu-system-i386 -cdrom grub/noOs.iso -S -s

.PHONY: run64
run64:
	qemu-system-x86_64 -bios /usr/share/ovmf/OVMF.fd -cdrom grub/noOs.iso

.PHONY: usb
usb:
	bash -c "sudo dd if=/dev/zero of=/dev/sda bs=512 count=245760"
	bash -c "read -p \"Reinsert USB Drive. Then press any key to continue... \" -n1 -s"
	bash -c "sleep 2"
	bash -c "sudo mkfs.vfat -F 32 -n NOOS -I /dev/sda"
	bash -c "sudo dd bs=4M if=grub/noOs.iso of=/dev/sda conv=fdatasync"

.PHONY: clean
clean:
	rm -f $(BOOT_OBJS)
	rm -f $(KERNEL_OBJS)
	rm -f $(DRIVER_OBJS)
	rm -f grub/noOs.bin
	rm -f grub/noOs.iso

%.iso: %.bin grub/grub.cfg
	bash -c "mkdir -p grub/build/boot"
	bash -c "mkdir -p grub/build/boot/grub"
	bash -c "cp $< grub/build/boot"
	bash -c "cp grub/grub.cfg grub/build/boot/grub/grub.cfg"
	bash -c "grub-mkrescue -o $@ grub/build"

grub/noOs.bin: linker.ld $(ALL_OBJS) 
	i686-elf-gcc -T $< -o $@ -g -ggdb -ffreestanding -nostdlib $(ALL_OBJS) -lgcc 

grub/noOs-serial.bin: linker.ld $(SERIAL_OBJS)
	i686-elf-gcc -T $< -o $@ -g -ggdb -ffreestanding -nostdlib $(SERIAL_OBJS) -lgcc

%.o: %.c
	i686-elf-gcc $(CFLAGS) $< -o $@ 

%.o.serial: %.c
	i686-elf-gcc $(CFLAGS) $(SERIAL) $< -o $@

%.o: %.asm
	nasm $(INCLUDE_NASM) -g -F dwarf -felf32 $< -o $@

%.o.serial: %.asm
	nasm $(INCLUDE_NASM) -g -F dwarf -felf32 $< -o $@ $(SERIAL)
