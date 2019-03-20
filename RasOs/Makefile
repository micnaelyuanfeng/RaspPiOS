##########################################################
#		MakeFile For Raspaberry Pi OS V0.01		
##########################################################
C_SRC  		 := main.c	\
				api.c	\
				uart.c	\
				printf.c \
				exception.c \
				timer.c \
				list.c \
				fpools.c \
				mm.c \
				process.c \
				scheduler.c \

S_SRC   	 := boot.s	\
				sysapi.s \
				eentry.s \
				ctxswitch.s \

C_OBJ        := main.o	\
				api.o	\
				uart.o	\
				printf.o \
				exception.o \
				timer.o \
				list.o \
				fpools.o \
				mm.o \
				process.o \
				scheduler.o \

S_OBJ		 := boot.o	\
				sysapi.o \
				eentry.o \
				ctxswitch.o \

ASM_FOLDER   := asm

HEADERS   	 := Include

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
QEMU_RUN := qemu-system-aarch64

#MEMORY
MEMORY_SIZE := 512

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
	$(LINKER) -T rslink.ld -nostdlib -nostartfiles -O2 $(C_OBJ) $(S_OBJ) -o $(TARGET_ELF)

##########################################################
# 		Copy to Disk for Real Hardware
##########################################################
copy_img:
	$(IMG) $(TARGET_ELF) -O binary $(TARGET_BIN)

##########################################################
# 		Dump Elf file
##########################################################
obj_dump:
	$(DUMP) -t $(TARGET_ELF)

##########################################################
# 		Qemu Run
##########################################################
run:
ifeq ($(ARCH3),1)
	$(QEMU_RUN) -M $(RASPIARCH)  -serial stdio -kernel $(TARGET_ELF)
else
	$(QEMU_RUN) -m $(MEMORY_SIZE) -M $(RASPIARCH) $(QEMU_FLAGS) -kernel $(TARGET_ELF)
endif

##########################################################
# 		Clean All Builds
##########################################################
clean:
	rm *.o
	rm *.elf

