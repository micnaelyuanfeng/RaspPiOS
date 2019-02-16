##########################################################
#		MakeFile For Raspaberry Pi OS V0.01		
##########################################################
C_SRC  		 := main.c	\
				printf.c	\
S_SRC   	 := boot.s	\
				utility.s

C_OBJ        := main.o
S_OBJ		 := boot.o	\
				utility.o	\
				printf.o	\

HEADERS   	 := include

#CC			 := arm-none-eabi-gcc
CC           := aarch64-elf-gcc

LINKER       := aarch64-elf-ld

#IMG          := arm-none-eabi-objcopy
IMG          := aarch64-elf-objcopy

QEMU_RUN 	 := qemu-system-arm
QEMU_RUN64	 := qemu-system-aarch64

TARGET_ELF   := rasOS.elf
TARGET_BIN   := rasOS.bin

#Quad core Cortex A7 processor
ASM_FLAGS 	 := -fpic -ffreestanding
C_FLAGS   	 := -fpic -ffreestanding -std=gnu99 -Wall -Wall -O2 -ffreestanding -nostdinc -nostdlib -nostartfiles -I $(HEADERS)
QEMU_FLAGS   := -d in_asm

#CHIP_ARCHITECHTURE
ifeq ($(ARCH1),1)
	RASPIARCH = raspi
	ARCH64 = 0
endif

ifeq ($(ARCH2),1)
	RASPIARCH = raspi2
	ARCH64 = 1
endif

ifeq ($(ARCH3),1)
	RASPIARCH = raspi3
	ARCH64 = 1
endif

#QEMU
ifeq ($(ARCH64),1)
	QEMU_RUN = qemu-system-aarch64
else
	QEMU_RUN = qemu-system-arm
endif

#MEMORY
ifeq ($(ARCH64),1)
	MEMORY_SIZE = 512
else
	MEMORY_SIZE = 256
endif

##########################################################
# 		Build Kernel
##########################################################
.PHONY:	all

all: build_kernel link_kernel

build_kernel: $(C_OBJ) $(S_OBJ)

%.o:%.c
	$(CC) $(C_FLAGS) $< -c -o $@

%.o:%.s
	$(CC) $(ASM_FLAGS) $< -c -o $@

link_kernel:
	$(LINKER) -T rslink.ld -nostdlib -nostartfiles -O2 $(C_OBJ) $(S_OBJ) -o $(TARGET_ELF)

##########################################################
# 		Copy to Disk for Real Hardware
##########################################################
copy_img:
	$(IMG) $(TARGET_ELF) -O binary $(TARGET_BIN)

##########################################################
# 		Qemu Run
##########################################################
run_qemu:
	$(QEMU_RUN) -m $(MEMORY_SIZE) -M $(RASPIARCH) $(QEMU_FLAGS) -kernel $(TARGET_ELF)


##########################################################
# 		Clean All Builds
##########################################################
clean:
	rm *.o
	rm *.elf
