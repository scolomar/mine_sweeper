# -*- MakeFile -*-

# MACRO = substitute with this

# directories

LIBALX_INC_DIR = $(LIBALX_DIR)/inc/

GAME_INC_DIR = $(GAME_DIR)/inc/

INC_DIR = $(PLAY_DIR)/inc/
SRC_DIR = $(PLAY_DIR)/src/

# dependencies

_ALL = player_iface.o player_clui.o player_tui.o
ALL = $(_ALL) player_mod.o

PLAYI_INC_GAME =	game_iface.h
PLAYI_INC =	player_iface.h	player_clui.h player_tui.h
PLAYI_DEPS = $(SRC_DIR)/player_iface.c \
			$(patsubst %,$(INC_DIR)/%,$(PLAYI_INC)) \
			$(patsubst %,$(GAME_INC_DIR)/%,$(PLAYI_INC_GAME))
PLAYI_INC_DIRS = -I $(INC_DIR) \
			-I $(GAME_INC_DIR)

PLAYCLUI_INC_GAME =	game_iface.h
PLAYCLUI_INC =	player_clui.h	player_iface.h
PLAYCLUI_DEPS = $(SRC_DIR)/player_clui.c \
			$(patsubst %,$(INC_DIR)/%,$(PLAYCLUI_INC)) \
			$(patsubst %,$(GAME_INC_DIR)/%,$(PLAYCLUI_INC_GAME))
PLAYCLUI_INC_DIRS = -I $(INC_DIR) \
			-I $(GAME_INC_DIR)

PLAYTUI_INC_LIBALX =	alx_ncur.h
PLAYTUI_INC_GAME =	game_iface.h
PLAYTUI_INC =	player_tui.h	player_iface.h
PLAYTUI_DEPS = $(SRC_DIR)/player_tui.c \
			$(patsubst %,$(INC_DIR)/%,$(PLAYTUI_INC)) \
			$(patsubst %,$(LIBALX_INC_DIR)/%,$(PLAYTUI_INC_LIBALX)) \
			$(patsubst %,$(GAME_INC_DIR)/%,$(PLAYCLUI_INC_GAME))
PLAYTUI_INC_DIRS = -I $(INC_DIR) \
			-I $(LIBALX_INC_DIR) \
			-I $(GAME_INC_DIR)

# target: dependencies
#	action

all: $(ALL)


player_mod.o: $(_ALL)
	$(Q)$(LD) -r $^ -o $@
	@echo  "\tLD $@"
	@echo  ""


player_iface.o: $(PLAYI_DEPS)
	$(Q)$(CC) $(CFLAGS) $(PLAYI_INC_DIRS) -c $< -o $@ $(LIBS)
	@echo  "\tCC $<"
	@echo  ""

player_clui.o: $(PLAYCLUI_DEPS)
	$(Q)$(CC) $(CFLAGS) $(PLAYCLUI_INC_DIRS) -c $< -o $@ $(LIBS)
	@echo  "\tCC $<"
	@echo  ""

player_tui.o: $(PLAYTUI_DEPS)
	$(Q)$(CC) $(CFLAGS) $(PLAYTUI_INC_DIRS) -c $< -o $@ $(LIBS)
	@echo  "\tCC $<"
	@echo  ""


clean:
	$(Q)rm -f *.o
