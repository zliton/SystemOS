
AS = as
CC = gcc
LD = ld

ASFLAGS = --32
CFLAGS = -m32 -c -ffreestanding -I./includes -Wall -Wextra
LDFLAGS = -m elf_i386 -T src/boot/linker.ld -nostdlib

SRC_DIR = src
BOOT_DIR = $(SRC_DIR)/boot
KERNEL_DIR = $(SRC_DIR)/kernel
DRIVERS_DIR = $(KERNEL_DIR)/drivers
FUNCTIONS_DIR = $(KERNEL_DIR)/functions
OS_DIR = $(KERNEL_DIR)/os
BUILD_DIR = build
ISO_DIR = isodir


BOOT_SRC = $(BOOT_DIR)/boot.s
KERNEL_SRC = $(KERNEL_DIR)/kernel.c
DRIVERS_SRC = $(DRIVERS_DIR)/keyboard.c
FUNCTIONS_SRC = $(FUNCTIONS_DIR)/print.c
OS_SRC = $(OS_DIR)/a.c $(OS_DIR)/error.c


BOOT_OBJ = $(BUILD_DIR)/boot.o
KERNEL_OBJ = $(BUILD_DIR)/kernel.o
DRIVERS_OBJ = $(BUILD_DIR)/keyboard.o
FUNCTIONS_OBJ = $(BUILD_DIR)/print.o
OS_OBJS = $(OS_SRC:$(OS_DIR)/%.c=$(BUILD_DIR)/%.o)


KERNEL = $(BUILD_DIR)/kernel.bin
ISO = SystemOS.iso


all: $(BUILD_DIR) $(KERNEL)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(KERNEL): $(BOOT_OBJ) $(KERNEL_OBJ) $(DRIVERS_OBJ) $(FUNCTIONS_OBJ) $(OS_OBJS)
	$(LD) $(LDFLAGS) -o $@ $^

# Reglas de compilación
$(BOOT_OBJ): $(BOOT_SRC)
	$(AS) $(ASFLAGS) $< -o $@

$(KERNEL_OBJ): $(KERNEL_SRC)
	$(CC) $(CFLAGS) $< -o $@

$(DRIVERS_OBJ): $(DRIVERS_SRC)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $< -o $@

$(FUNCTIONS_OBJ): $(FUNCTIONS_SRC)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $< -o $@

$(BUILD_DIR)/%.o: $(OS_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $< -o $@


iso: $(KERNEL)
	@mkdir -p $(ISO_DIR)/boot/grub
	@cp $(KERNEL) $(ISO_DIR)/boot/
	@cp src/boot/grub.cfg $(ISO_DIR)/boot/grub/
	@grub-mkrescue -o $(ISO) $(ISO_DIR)
	@echo "ISO creada: $(ISO)"




clean:
	rm -rf $(BUILD_DIR) $(ISO_DIR) $(ISO)

.PHONY: all clean iso 