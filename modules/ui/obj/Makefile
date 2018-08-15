# -*- MakeFile -*-

# MACRO = substitute with this

# directories

MSW_DIR = ../../../

LIBALX_DIR = $(MSW_DIR)/libalx/
LIBALX_INC_DIR = $(LIBALX_DIR)/inc/

MODULES_DIR = $(MSW_DIR)/modules/

CTRL_DIR = $(MODULES_DIR)/ctrl/
CTRL_INC_DIR = $(CTRL_DIR)/inc/

DATA_DIR = $(MODULES_DIR)/data/
DATA_INC_DIR = $(DATA_DIR)/inc/

GAME_DIR = $(MODULES_DIR)/game/
GAME_INC_DIR = $(GAME_DIR)/inc/

PRNT_DIR = $(MODULES_DIR)/prnt/
PRNT_INC_DIR = $(PRNT_DIR)/inc/

UI_DIR = $(MODULES_DIR)/ui/
INC_DIR = $(UI_DIR)/inc/
SRC_DIR = $(UI_DIR)/src/
TST_DIR = $(UI_DIR)/tst/

# dependencies

ALL = clui.o game_ui.o tui.o

CLUI_INC_LIBALX =	alx_seed.h
CLUI_INC_CTRL =		start.h
CLUI_INC_DATA =		data.h
CLUI_INC_PRNT =		about.h
CLUI_INC =	clui.h
CLUI_DEPS = $(SRC_DIR)/clui.c \
			$(patsubst %,$(INC_DIR)/%,$(CLUI_INC)) \
			$(patsubst %,$(LIBALX_INC_DIR)/%,$(CLUI_INC_LIBALX)) \
			$(patsubst %,$(CTRL_INC_DIR)/%,$(CLUI_INC_CTRL)) \
			$(patsubst %,$(DATA_INC_DIR)/%,$(CLUI_INC_DATA)) \
			$(patsubst %,$(PRNT_INC_DIR)/%,$(CLUI_INC_PRNT))
CLUI_INC_DIRS = -I $(INC_DIR) \
			-I $(LIBALX_INC_DIR) \
			-I $(CTRL_INC_DIR) \
			-I $(DATA_INC_DIR) \
			-I $(PRNT_INC_DIR)

GAMEUI_INC_LIBALX =	alx_ncur.h
GAMEUI_INC_DATA =	data.h
GAMEUI_INC_GAME =	game.h
GAMEUI_INC_PRNT =	about.h
GAMEUI_INC =	game_ui.h
GAMEUI_DEPS = $(SRC_DIR)/game_ui.c \
			$(patsubst %,$(INC_DIR)/%,$(GAMEUI_INC)) \
			$(patsubst %,$(LIBALX_INC_DIR)/%,$(GAMEUI_INC_LIBALX)) \
			$(patsubst %,$(DATA_INC_DIR)/%,$(GAMEUI_INC_DATA)) \
			$(patsubst %,$(GAME_INC_DIR)/%,$(GAMEUI_INC_GAME)) \
			$(patsubst %,$(PRNT_INC_DIR)/%,$(GAMEUI_INC_PRNT))
GAMEUI_INC_DIRS = -I $(INC_DIR) \
			-I $(LIBALX_INC_DIR) \
			-I $(DATA_INC_DIR) \
			-I $(GAME_INC_DIR) \
			-I $(PRNT_INC_DIR)

TUI_INC_LIBALX =	alx_ncur.h
TUI_INC_CTRL =		start.h
TUI_INC_DATA =		data.h
TUI_INC_PRNT =		about.h
TUI_INC =	tui.h
TUI_DEPS = $(SRC_DIR)/tui.c \
			$(patsubst %,$(INC_DIR)/%,$(TUI_INC)) \
			$(patsubst %,$(LIBALX_INC_DIR)/%,$(TUI_INC_LIBALX)) \
			$(patsubst %,$(CTRL_INC_DIR)/%,$(TUI_INC_CTRL)) \
			$(patsubst %,$(DATA_INC_DIR)/%,$(TUI_INC_DATA)) \
			$(patsubst %,$(PRNT_INC_DIR)/%,$(TUI_INC_PRNT))
TUI_INC_DIRS = -I $(INC_DIR) \
			-I $(CTRL_INC_DIR) \
			-I $(DATA_INC_DIR) \
			-I $(PRNT_INC_DIR) \
			-I $(LIBALX_INC_DIR)

# target: dependencies
#	action

all: $(ALL)
	

clui.o: $(CLUI_DEPS)
	$(CC) $(CFLAGS) $(CLUI_INC_DIRS) -c $< -o $@ $(LIBS)

game_ui.o: $(GAMEUI_DEPS)
	$(CC) $(CFLAGS) $(GAMEUI_INC_DIRS) -c $< -o $@ $(LIBS)

tui.o: $(TUI_DEPS)
	$(CC) $(CFLAGS) $(TUI_INC_DIRS) -c $< -o $@ $(LIBS)


clean:
	rm -f *.o
