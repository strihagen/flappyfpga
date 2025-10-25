# ================================
# Project Configuration
# ================================

SRC_DIR     ?= src
INC_DIR     ?= include
BUILD_DIR   ?= build
OBJ_DIR 	:= $(BUILD_DIR)/objs
LIB_DIR     ?= lib
LINKER_DIR  ?= linker
TOOL_DIR    ?= tools

LINKER      ?= $(LINKER_DIR)/dtekv-script.lds
TOOLCHAIN   ?= riscv32-unknown-elf-

TARGET      ?= flappyfpga
LIBS        ?= -L$(LIB_DIR) -l:softfloat.a

CFLAGS      ?= -Wall -nostdlib -O3 -mabi=ilp32 -march=rv32imzicsr -fno-builtin -I$(INC_DIR)
LDFLAGS     ?= -T$(LINKER) $(LIBS)

# ================================
# Source and Object Discovery
# ================================

# Recursively find .c and .S files
SOURCES     := $(shell find $(SRC_DIR) -type f \( -name '*.c' -o -name '*.S' \))

# Convert each source file into a matching object file in the build directory
OBJECTS     := $(patsubst $(SRC_DIR)/%, $(OBJ_DIR)/%, $(SOURCES:.c=.o))
OBJECTS     := $(OBJECTS:.S=.o)

BOOT_OBJ := $(filter %boot.o, $(OBJECTS))

# ================================
# Build Rules
# ================================

# Default target
build: $(BUILD_DIR)/$(TARGET).bin

# Create build directory structure automatically
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(TOOLCHAIN)gcc $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.S
	@mkdir -p $(dir $@)
	$(TOOLCHAIN)gcc $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/$(TARGET).elf: $(OBJECTS)
	@echo "Linking ELF..."
	$(TOOLCHAIN)ld -o $@ $(BOOT_OBJ) $(filter-out $(BOOT_OBJ), $^) $(LDFLAGS)

# Convert ELF -> BIN + generate disassembly
$(BUILD_DIR)/$(TARGET).bin: $(BUILD_DIR)/$(TARGET).elf
	$(TOOLCHAIN)objcopy -O binary $< $@
	$(TOOLCHAIN)objdump -D $< > $<.dump.txt

# ================================
# Helper Targets
# ================================

clean:
	rm -rf $(BUILD_DIR)

run: $(BUILD_DIR)/$(TARGET).bin
	$(MAKE) -C $(TOOL_DIR) "FILE_TO_RUN=$(CURDIR)/$<"

# ================================
# Phony Targets
# ================================
.PHONY: build clean run

