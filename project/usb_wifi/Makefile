#################################################################
#					Toolchain configuration						#
#################################################################
RM = rm -f
SHELL = /bin/bash

target_x86 = x86
target_arm = arm

TARGET_ARCH = $(target)
ifeq ($(TARGET_ARCH), $(target_x86))
	CC = gcc
else ifeq ($(TARGET_ARCH), $(target_arm))
	CC = $(CC)
endif

#################################################################
#					Project configuration						#
#################################################################
INCLUDE_ROOT=../../package/include 

ifeq ($(ARCH), $(target_arm))
	LIB_ROOT=../../package/lib
else 
	LIB_ROOT=../../package/lib_x86
endif

SRC_PATH = .
SRC_PATH += ../modules_common


PROJ_NAME=wifi
# C source files
SRC_DIRS = $(shell find $(SRC_PATH) -maxdepth 6 -type d)
C_SRCS = $(foreach dir, $(SRC_DIRS), $(wildcard $(dir)/*.c))

#################################################################
#						Do formatting							#
#################################################################
#LIBS = -Wl,--start-group -llogger_c -ldl -lm -Wl,--end-group
LIBS =  -ldl -lm -lpthread -lcc -Wl,-rpath=.

# flags for C compiler  -Wall -Werror
CFLAGS+= $(addprefix -I,$(INCLUDE_ROOT)) $(addprefix -I,$(SRC_PATH)) -g  -Wall
LDFLAGS= -L$(LIB_ROOT)

OBJS = $(patsubst %.c,%.o,$(C_SRCS))

# ROOT=$(shell pwd)

.PHONY: clean

all: $(PROJ_NAME) 

#####################################
#			.o -> .elf				#
#####################################
$(PROJ_NAME): $(OBJS)
	$(CC) $(LDFLAGS)  $^ -o $@ $(LIBS)
	@echo -e "\033[42;37m OK, build success! \033[0m"
#####################################
#			.c -> .o				#
#####################################
%.o : %.c
	$(CC) $(CFLAGS) -c -o  $@ $^
	@echo -e "\033[44;37m Compile done \033[0m"

	
cp:
	cp wifi /nfs_files/ -r
	@echo -e "\033[42;37mcp to arm OK\033[0m"

clean:
	@echo -e "\033[41;37mRemoving\033[0m *.o"
	@$(RM) $(PROJ_NAME) *.o
	@echo -e "\033[42;37mOK\033[0m"
	

	
