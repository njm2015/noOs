CC=i386-elf-gcc

INCLUDES := -I./includes
SRC_DIRS := $(shell find . -mindepth 1 -maxdepth 2 -type d)
EXCLUDE  := ./boot ./debug ./includes ./.git ./grub

SRC_DIRS := $(filter-out $(EXCLUDE:%=%),$(SRC_DIRS))
SRC_C 	 := $(foreach d, $(SRC_DIRS), $(wildcard $d/*.c))
SRC_ASM  := $(foreach d, $(SRC_DIRS), $(wildcard $d/*.asm))

OBJS     := boot/boot.o $(SRC_ASM:%.asm=%.o) $(SRC_C:%.c=%.o)

CFLAGS = -O1 -c -g -ggdb -std=gnu99 -ffreestanding -Wall -Wextra $(INCLUDE_GCC)
LDFLAGS = -g -ggdb -ffreestanding -nostdlib -lgcc

all: clean grub/noOs.iso

.PHONY: serial
serial: DEFINES+=-DSERIAL
serial: grub/noOs-serial.iso

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

.PRECIOUS: grub/noOs.bin 
.PHONY: clean
clean:
	rm -f $(OBJS)
	rm -f grub/*.bin
	rm -f grub/*.iso

%.iso: %.bin grub/grub.cfg
	bash -c "mkdir -p grub/build/boot"
	bash -c "mkdir -p grub/build/boot/grub"
	bash -c "cp $< grub/build/boot"
	bash -c "cp grub/grub.cfg grub/build/boot/grub/grub.cfg"
	bash -c "grub-mkrescue -o $@ grub/build"

%.bin: linker.ld $(OBJS) 
	$(CC) -T $< -o $@ $(LDFLAGS) $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) $(DEFINES) $< -o $@ 

%.o: %.asm
	nasm $(INCLUDES) -g -F dwarf -felf32 $< -o $@
