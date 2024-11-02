
AS = nasm
CC = gcc
LD = ld

ASFLAGS = -f elf32
CFLAGS = -m32 -c -ffreestanding -I./includes
LDFLAGS = -m elf_i386 -T src/boot/linker.ld -nostdlib

SRC_DIR = src
BOOT_DIR = $(SRC_DIR)/boot
KERNEL_DIR = $(SRC_DIR)/kernel
DRIVERS_DIR = $(KERNEL_DIR)/drivers
FUNCTIONS_DIR = $(KERNEL_DIR)/functions
BUILD_DIR = build


BOOT_SRC = $(BOOT_DIR)/boot.s
KERNEL_SRC = $(KERNEL_DIR)/kernel.c
DRIVERS_SRC = $(DRIVERS_DIR)/keyboard.c
FUNCTIONS_SRC = $(FUNCTIONS_DIR)/print.c


BOOT_OBJ = $(BUILD_DIR)/boot.o
KERNEL_OBJ = $(BUILD_DIR)/kernel.o
DRIVERS_OBJ = $(BUILD_DIR)/keyboard.o
FUNCTIONS_OBJ = $(BUILD_DIR)/print.o
ISO = SystemOS.iso
ISO_DIR = bin

KERNEL = $(BUILD_DIR)/kernel.bin


all: $(BUILD_DIR) $(KERNEL)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(KERNEL): $(BOOT_OBJ) $(KERNEL_OBJ) $(DRIVERS_OBJ) $(FUNCTIONS_OBJ)
	$(LD) $(LDFLAGS) -o $@ $^

$(BOOT_OBJ): $(BOOT_SRC)
	$(AS) $(ASFLAGS) $< -o $@

$(KERNEL_OBJ): $(KERNEL_SRC)
	$(CC) $(CFLAGS) $< -o $@

$(DRIVERS_OBJ): $(DRIVERS_SRC)
	$(CC) $(CFLAGS) $< -o $@

$(FUNCTIONS_OBJ): $(FUNCTIONS_SRC)
	$(CC) $(CFLAGS) $< -o $@

iso: $(KERNEL)
	mkdir -p $(ISO_DIR)/boot/grub
	cp $(KERNEL) $(ISO_DIR)/boot/
	cp boot/grub/grub.cfg $(ISO_DIR)/boot/grub/
	grub-mkrescue -o $(ISO) $(ISO_DIR)

clean:
	rm -rf $(BUILD_DIR)

.PHONY: all clean iso