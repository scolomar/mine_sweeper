# -*- MakeFile -*-

# MACRO = substitute with this

# export

export	OS = linux
export	TST = false
export	DBG = false

 ifeq ($(OS), linux)
export	CC = gcc
export	CFLAGS = -std=c11 -mcmodel=medium -O3 -march=native
export	LIBS = -l ncurses -l m
 else ifeq ($(OS), win)
CFLAGS_NCURSESW6 = -D _XOPEN_SOURCE=500 -I /mingw/include/ncursesw -I /mingw/include
LIBS_NCURSESW6 = -L /mingw/lib -l ncursesw -l psapi
export	CC = gcc.exe
export	CFLAGS = -std=c11 -O3 $(CFLAGS_NCURSESW6)
export	LIBS = -static -l m $(LIBS_NCURSESW6)
 endif

# directories

PNP_DIR = ./

LIBALX_DIR = $(PNP_DIR)/libalx/
MODULES_DIR = $(PNP_DIR)/modules/
OBJ_DIR = $(PNP_DIR)/obj/
BIN_DIR = $(PNP_DIR)/bin/
WIN_DIR = $(PNP_DIR)/win/
TST_DIR = $(PNP_DIR)/tst/


# target: dependencies
#	action

all:
	cd $(LIBALX_DIR) && $(MAKE) && cd ..
	cd $(MODULES_DIR) && $(MAKE) && cd ..
	cd $(OBJ_DIR) && $(MAKE) && cd ..

 ifeq ($(OS), linux)
	cd $(BIN_DIR) && $(MAKE) && cd ..
 else ifeq ($(OS), win)
	cd $(WIN_DIR) && $(MAKE) && cd ..
 endif

 ifeq ($(TST), true)
	cd $(TST_DIR) && $(MAKE) && cd ..
 endif

mrproper: clean
	cd $(WIN_DIR) && $(MAKE) clean && cd ..
	cd $(BIN_DIR) && $(MAKE) clean && cd ..

clean:
	cd $(LIBALX_DIR) && $(MAKE) clean && cd ..
	cd $(MODULES_DIR) && $(MAKE) clean && cd ..
	cd $(OBJ_DIR) && $(MAKE) clean && cd ..
#	cd $(TST_DIR) && $(MAKE) clean && cd ..

################################################################################
######## End of file ###########################################################
################################################################################
######## End of file ###########################################################
################################################################################
######## End of file ###########################################################
################################################################################
