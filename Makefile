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


KERNEL_INCLUDE = $(foreach d, $(KERNEL_COMPONENTS), -I$(subst ,,$d))
DRIVER_INCLUDE = $(foreach d, $(DRIVER_COMPONENTS), -I$(subst ,,$d))
BOOT_INCLUDE = $(foreach d, $(BOOT_COMPONENTS), -I$(subst ,,$d))


$(info $(KERNEL_INCLUDE))
$(info $(BOOT_INCLUDE))
$(info $(DRIVER_INCLUDE))

INCLUDE = $(BOOT_INCLUDE) $(KERNEL_INCLUDE) $(DRIVER_INCLUDE)
CFLAGS = -c -g -ggdb -std=gnu99 -ffreestanding -Wall -Wextra $(INCLUDE)

all: grub/noOs.iso

.PHONY: run
run:
	qemu-system-i386 -cdrom grub/noOs.iso

.PHONY: rund
rund:
	qemu-system-i386 -cdrom grub/noOs.iso -S -s

.PHONY: run64
run64:
	qemu-system-x86_64 -bios /usr/share/ovmf/OVMF.fd -cdrom grub/noOs.iso

grub/noOs.iso: grub/noOs.bin grub/grub.cfg
	bash -c "mkdir -p grub/build/boot"
	bash -c "mkdir -p grub/build/boot/grub"
	bash -c "cp grub/noOs.bin grub/build/boot"
	bash -c "cp grub/grub.cfg grub/build/boot/grub/grub.cfg"
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
	rm -f $(DRIVER_OBJS)
	rm -f grub/noOs.bin
	rm -f grub/noOs.iso
