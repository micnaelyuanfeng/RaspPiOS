##########################################################
#		MakeFile For Raspaberry Pi OS V0.02		
##########################################################


C_SRC := $(shell find.exe . -name "*.c")
S_SRC := $(shell find.exe . -name "*.S")

C_OBJ := $(patsubst %.c,%.o,$(C_SRC))
S_OBJ := $(patsubst %.S,%.o,$(S_SRC))

HEADERS   	 := include
#CC			 := arm-none-eabi-gcc
CC           := aarch64-elf-gcc

#LINKER       := arm-none-eabi-objdump.exe
LINKER       := aarch64-elf-ld

#IMG          := arm-none-eabi-objcopy.exe
IMG          := aarch64-elf-objcopy

DUMP         := aarch64-elf-objdump

QEMU_RUN 	 := qemu-system-arm
QEMU_RUN64	 := qemu-system-aarch64

TARGET_ELF   := kernel8.elf
TARGET_BIN   := kernel8.bin

#Quad core Cortex A7 processor
ASM_FLAGS 	 := -I $(HEADERS)
C_FLAGS   	 := -Wall -nostdlib -nostartfiles -ffreestanding -I $(HEADERS) -mgeneral-regs-only
QEMU_FLAGS   := -d in_asm

#QEMU
QEMU_RUN := qemu-system-aarch64

#ARCHITECTURE
RASPIARCH = raspi3

#MEMORY
MEMORY_SIZE := 1024

##########################################################
# 		Build Kernel
##########################################################
.PHONY:	all
all: build_kernel link_kernel

build_kernel: $(C_OBJ) $(S_OBJ)

%.o:%.c
	$(CC) $(C_FLAGS) -c $< -o $@

%.o:%.s
	$(CC) $(ASM_FLAGS) $< -c -o $@

link_kernel:
	$(LINKER) -T link.ld -nostdlib -nostartfiles -O2 $(C_OBJ) $(S_OBJ) -o $(TARGET_ELF)

##########################################################
# 		Copy to Disk for Real Hardware
##########################################################
copy_img:
	$(IMG) $(TARGET_ELF) -O binary $(TARGET_BIN)

##########################################################
# 		Dump Elf file
##########################################################
obj_dump:
	$(DUMP) -D $(TARGET_ELF)

##########################################################
# 		Qemu Run
##########################################################
run:
	$(QEMU_RUN) -m 1024 -M $(RASPIARCH)  -serial stdio -kernel $(TARGET_ELF)


##########################################################
# 		Clean All Builds
##########################################################
.PHONY: clean
clean:
	rm $(C_OBJ)
	rm $(S_OBJ)
	rm *.elf
