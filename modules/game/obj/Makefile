# -*- MakeFile -*-

# MACRO = substitute with this

# directories

LIBALX_INC_DIR = $(LIBALX_DIR)/inc/

DATA_INC_DIR = $(DATA_DIR)/inc/
GEN_INC_DIR = $(GEN_DIR)/inc/
SAVE_INC_DIR = $(SAVE_DIR)/inc/

INC_DIR = $(GAME_DIR)/inc/
SRC_DIR = $(GAME_DIR)/src/

# dependencies

ALL = game.o

GAME_INC_LIBALX =
GAME_INC_DATA =		data.h
GAME_INC_GEN =		init.h
GAME_INC_SAVE =		save.h
GAME_INC =	game.h
GAME_DEPS = $(SRC_DIR)/game.c \
			$(patsubst %,$(INC_DIR)/%,$(GAME_INC)) \
			$(patsubst %,$(LIBALX_INC_DIR)/%,$(GAME_INC_LIBALX)) \
			$(patsubst %,$(DATA_INC_DIR)/%,$(GAME_INC_DATA)) \
			$(patsubst %,$(GEN_INC_DIR)/%,$(GAME_INC_GEN)) \
			$(patsubst %,$(SAVE_INC_DIR)/%,$(GAME_INC_SAVE))
GAME_INC_DIRS = -I $(INC_DIR) \
			-I $(DATA_INC_DIR) \
			-I $(GEN_INC_DIR) \
			-I $(SAVE_INC_DIR) \
			-I $(LIBALX_INC_DIR)

# target: dependencies
#	action

all: $(ALL)
	

game.o: $(GAME_DEPS)
	$(Q)$(CC) $(CFLAGS) $(GAME_INC_DIRS) -c $< -o $@ $(LIBS)
	@echo  "\tCC $<"
	@echo  ""


clean:
	$(Q)rm -f *.o
