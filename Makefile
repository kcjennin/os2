arch ?= x86_64
kernel := build/kernel-$(arch).bin
img := build/os-$(arch).img
mount = /mnt/osimg
blank_img = src/blank.img
export PATH := /home/kyle/opt/cross/bin:$(PATH)

linker_script := src/arch/$(arch)/linker.ld
grub_cfg := src/arch/$(arch)/grub.cfg
assembly_source := $(wildcard src/arch/$(arch)/*.asm)
assembly_object := $(patsubst src/arch/$(arch)/%.asm, \
		build/arch/$(arch)/%.o, $(assembly_source))
c_source := $(wildcard src/arch/$(arch)/*.c)
c_object := $(patsubst src/arch/$(arch)/%.c, \
		build/arch/$(arch)/%.o, $(c_source))
c_include_dir = src/arch/x86_64

loop := $(shell losetup -f)

.PHONY: all clean run img

all: $(kernel)

clean:
	@rm -rf build

run: $(img)
	@qemu-system-x86_64 -s -drive format=raw,file=$(img) -serial stdio

img: $(img)

$(img): $(kernel) $(grub_cfg)
	@mkdir -p build/img/boot/grub
	@cp $(kernel) build/img/boot/kernel.bin
	@cp $(grub_cfg) build/img/boot/grub
	@cp $(blank_img) $(img)
	@losetup $(loop) $(img) -o 1048576
	@mount $(loop) $(mount)
	@cp -r build/img/* $(mount)
	@umount $(mount)
	@losetup -d $(loop)

$(kernel): $(assembly_object) $(c_object) $(linker_script)
	@x86_64-elf-ld -n -o $(kernel) -T $(linker_script) $(assembly_object) $(c_object)

build/arch/$(arch)/%.o: src/arch/$(arch)/%.asm
	@mkdir -p $(shell dirname $@)
	@nasm -felf64 $< -o $@

build/arch/$(arch)/%.o: src/arch/$(arch)/%.c
	@mkdir -p $(shell dirname $@)
	@x86_64-elf-gcc -g -c $< -o $@ -I$(c_include_dir)
