# -*- MakeFile -*-

# MACRO = substitute with this

# directories

LIBALX_INC_DIR = $(LIBALX_DIR)/inc/

DATA_INC_DIR = $(DATA_DIR)/inc/
GAME_INC_DIR = $(GAME_DIR)/inc/
SAVE_INC_DIR = $(SAVE_DIR)/inc/

INC_DIR = $(XYZZY_DIR)/inc/
SRC_DIR = $(XYZZY_DIR)/src/

# dependencies

ALL = xyzzy.o

XYZZY_INC_LIBALX =
XYZZY_INC_DATA =	data.h
XYZZY_INC_GAME =	game.h
XYZZY_INC =	xyzzy.h
XYZZY_DEPS = $(SRC_DIR)/xyzzy.c \
			$(patsubst %,$(INC_DIR)/%,$(XYZZY_INC)) \
			$(patsubst %,$(LIBALX_INC_DIR)/%,$(XYZZY_INC_LIBALX)) \
			$(patsubst %,$(DATA_INC_DIR)/%,$(XYZZY_INC_DATA)) \
			$(patsubst %,$(GAME_INC_DIR)/%,$(XYZZY_INC_GAME))
XYZZY_INC_DIRS = -I $(INC_DIR) \
			-I $(DATA_INC_DIR) \
			-I $(GAME_INC_DIR) \
			-I $(LIBALX_INC_DIR)

# target: dependencies
#	action

all: $(ALL)
	

xyzzy.o: $(XYZZY_DEPS)
	$(Q)$(CC) $(CFLAGS) $(XYZZY_INC_DIRS) -c $< -o $@ $(LIBS)
	@echo  "\tCC $<"
	@echo  ""


clean:
	$(Q)rm -f *.o
