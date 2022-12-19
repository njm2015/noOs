KERNEL_SOURCES_C := $(wildcard kernel/**/*.c)
KERNEL_SOURCES_ASM := $(wildcard kernel/**/*.asm)
KERNEL_OBJS := $(KERNEL_SOURCES_ASM:%.asm=%.o) $(KERNEL_SOURCES_C:%.c=%.o)

BOOT_SOURCES_C := $(wildcard boot/**/*.c)
BOOT_SOURCES_ASM := $(wildcard boot/**/*.asm)
BOOT_OBJS := $(BOOT_SOURCES_ASM:%.asm=%.o) $(BOOT_SOURCES_C:%.c=%.o)

DRIVER_SOURCES_C := $(wildcard drivers/**/*.c)
DRIVER_SOURCES_ASM := $(wildcard drivers/**/*.asm)
DRIVER_OBJS := $(DRIVER_SOURCES_ASM:%.asm=%.o) $(DRIVER_SOURCES_C:%.c=%.o)

LIBDRIVER = drivers
LIBDRIVER_SUBDIRS = $(shell find $(LIBDRIVER) -mindepth 1 -maxdepth 2 -type d)
LIBDRIVER_INCLUDE = $(foreach d, $(LIBDRIVER_SUBDIRS), -I$(subst ,,$d))

CFLAGS = -c -g -ggdb -std=gnu99 -ffreestanding -Wall -Wextra $(LIBDRIVER_INCLUDE)

all: grub/noOs.iso

.PHONY: run
run:
	qemu-system-i386 -cdrom noOs.iso

.PHONY: rund
rund:
	qemu-system-i386 -cdrom noOs.iso -S -s

.PHONY: run64
run64:
	qemu-system-x86_64 -bios /usr/share/ovmf/OVMF.fd -cdrom grub/noOs.iso

grub/noOs.iso: grub/noOs.bin grub/grub.cfg
	bash -c "mkdir -p grub/build/boot"
	bash -c "mkdir -p grub/build/grub"
	bash -c "cp noOs.bin grub/build/boot"
	bash -c "cp grub.cfg grub/build/boot/grub/grub.cfg"
	bash -c "grub-mkrescue -o $@ grub/build"

grub/noOs.bin: linker.ld $(BOOT_OBJS) $(KERNEL_OBJS) $(DRIVER_OBJS)
	i686-elf-gcc -T $< -o $@ -g -ggdb -ffreestanding -nostdlib $(BOOT_OBJS) $(KERNEL_OBJS) $(DRIVER_OBJS) -lgcc 

%.o: %.c
	i686-elf-gcc $(CFLAGS) $< -o $@ 

%.o: %.asm
	nasm -g -F dwarf -felf32 $< -o $@

clean:
	rm -f $(BOOT_OBJS)
	rm -f $(KERNEL_OBJS)
	rm -f grub/noOs.bin
	rm -f grub/noOs.iso
