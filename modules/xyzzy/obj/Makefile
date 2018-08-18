# -*- MakeFile -*-

# MACRO = substitute with this

# directories

MSW_DIR = ../../../

LIBALX_DIR = $(MSW_DIR)/libalx/
LIBALX_INC_DIR = $(LIBALX_DIR)/inc/

MODULES_DIR = $(MSW_DIR)/modules/

DATA_DIR = $(MODULES_DIR)/data/
DATA_INC_DIR = $(DATA_DIR)/inc/

GEN_DIR = $(MODULES_DIR)/gen/
GEN_INC_DIR = $(GEN_DIR)/inc/

SAVE_DIR = $(MODULES_DIR)/save/
SAVE_INC_DIR = $(SAVE_DIR)/inc/

XYZZY_DIR = $(MODULES_DIR)/xyzzy/
INC_DIR = $(XYZZY_DIR)/inc/
SRC_DIR = $(XYZZY_DIR)/src/
TST_DIR = $(XYZZY_DIR)/tst/

# dependencies

ALL = xyzzy.o

XYZZY_INC_LIBALX =
XYZZY_INC_DATA =	data.h
XYZZY_INC_GEN =		init.h
XYZZY_INC_SAVE =	save.h
XYZZY_INC =	xyzzy.h
XYZZY_DEPS = $(SRC_DIR)/game.c \
			$(patsubst %,$(INC_DIR)/%,$(XYZZY_INC)) \
			$(patsubst %,$(LIBALX_INC_DIR)/%,$(XYZZY_INC_LIBALX)) \
			$(patsubst %,$(DATA_INC_DIR)/%,$(XYZZY_INC_DATA)) \
			$(patsubst %,$(GEN_INC_DIR)/%,$(XYZZY_INC_GEN)) \
			$(patsubst %,$(SAVE_INC_DIR)/%,$(XYZZY_INC_SAVE))
XYZZY_INC_DIRS = -I $(INC_DIR) \
			-I $(DATA_INC_DIR) \
			-I $(GEN_INC_DIR) \
			-I $(SAVE_INC_DIR) \
			-I $(LIBALX_INC_DIR)

# target: dependencies
#	action

all: $(ALL)
	

xyzzy.o: $(GAME_DEPS)
	$(CC) $(CFLAGS) $(XYZZY_INC_DIRS) -c $< -o $@ $(LIBS)


clean:
	rm -f *.o
