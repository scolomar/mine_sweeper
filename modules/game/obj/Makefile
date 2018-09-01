# -*- MakeFile -*-

# MACRO = substitute with this

# directories

LIBALX_INC_DIR = $(LIBALX_DIR)/inc/

PLAY_INC_DIR = $(PLAY_DIR)/inc/
SAVE_INC_DIR = $(SAVE_DIR)/inc/
XYZZY_INC_DIR = $(XYZZY_DIR)/inc/

INC_DIR = $(GAME_DIR)/inc/
SRC_DIR = $(GAME_DIR)/src/

# dependencies

_ALL = game.o game_iface.o
ALL = $(_ALL) game_mod.o

GAME_INC_LIBALX =	alx_seed.h
GAME_INC_SAVE =		save.h
GAME_INC =	game.h
GAME_DEPS = $(SRC_DIR)/game.c \
			$(patsubst %,$(INC_DIR)/%,$(GAME_INC)) \
			$(patsubst %,$(LIBALX_INC_DIR)/%,$(GAME_INC_LIBALX)) \
			$(patsubst %,$(SAVE_INC_DIR)/%,$(GAME_INC_SAVE))
GAME_INC_DIRS = -I $(INC_DIR) \
			-I $(SAVE_INC_DIR) \
			-I $(LIBALX_INC_DIR)

GAMEI_INC_PLAY =	player_iface.h
GAMEI_INC_SAVE =	save.h score.h
GAMEI_INC_XYZZY =	xyzzy.h
GAMEI_INC =	game_iface.h	game.h
GAMEI_DEPS = $(SRC_DIR)/game_iface.c \
			$(patsubst %,$(INC_DIR)/%,$(GAME_INC)) \
			$(patsubst %,$(PLAY_INC_DIR)/%,$(GAMEI_INC_PLAY)) \
			$(patsubst %,$(SAVE_INC_DIR)/%,$(GAME_INC_SAVE)) \
			$(patsubst %,$(XYZZY_INC_DIR)/%,$(GAMEI_INC_XYZZY))
GAMEI_INC_DIRS = -I $(INC_DIR) \
			-I $(PLAY_INC_DIR) \
			-I $(SAVE_INC_DIR) \
			-I $(XYZZY_INC_DIR)

# target: dependencies
#	action

all: $(ALL)
	

game_mod.o: $(_ALL)
	$(Q)$(LD) -r $^ -o $@
	@echo  "\tLD $@"
	@echo  ""


game.o: $(GAME_DEPS)
	$(Q)$(CC) $(CFLAGS) $(GAME_INC_DIRS) -c $< -o $@ $(LIBS)
	@echo  "\tCC $<"
	@echo  ""

game_iface.o: $(GAMEI_DEPS)
	$(Q)$(CC) $(CFLAGS) $(GAMEI_INC_DIRS) -c $< -o $@ $(LIBS)
	@echo  "\tCC $<"
	@echo  ""


clean:
	$(Q)rm -f *.o
