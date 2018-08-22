# -*- MakeFile -*-

# MACRO = substitute with this

# directories

LIBALX_INC_DIR = $(LIBALX_DIR)/inc/

CTRL_INC_DIR = $(CTRL_DIR)/inc/
DATA_INC_DIR = $(DATA_DIR)/inc/
GAME_INC_DIR = $(GAME_DIR)/inc/
PRNT_INC_DIR = $(PRNT_DIR)/inc/

INC_DIR = $(UI_DIR)/inc/
SRC_DIR = $(UI_DIR)/src/

# dependencies

ALL = parser.o game_iface.o game_clui.o game_tui.o tui.o

PARS_INC_LIBALX =	alx_seed.h
PARS_INC_CTRL =		start.h
PARS_INC_DATA =		data.h
PARS_INC_PRNT =		about.h
PARS_INC =	parser.h
PARS_DEPS = $(SRC_DIR)/parser.c \
			$(patsubst %,$(INC_DIR)/%,$(PARS_INC)) \
			$(patsubst %,$(LIBALX_INC_DIR)/%,$(PARS_INC_LIBALX)) \
			$(patsubst %,$(CTRL_INC_DIR)/%,$(PARS_INC_CTRL)) \
			$(patsubst %,$(DATA_INC_DIR)/%,$(PARS_INC_DATA)) \
			$(patsubst %,$(PRNT_INC_DIR)/%,$(PARS_INC_PRNT))
PARS_INC_DIRS = -I $(INC_DIR) \
			-I $(LIBALX_INC_DIR) \
			-I $(CTRL_INC_DIR) \
			-I $(DATA_INC_DIR) \
			-I $(PRNT_INC_DIR)

GAMEI_INC_LIBALX =
GAMEI_INC_DATA =	data.h
GAMEI_INC_GAME =	game.h
GAMEI_INC =	game_iface.h game_clui.h game_tui.h
GAMEI_DEPS = $(SRC_DIR)/game_iface.c \
			$(patsubst %,$(INC_DIR)/%,$(GAMEI_INC)) \
			$(patsubst %,$(LIBALX_INC_DIR)/%,$(GAMEI_INC_LIBALX)) \
			$(patsubst %,$(DATA_INC_DIR)/%,$(GAMEI_INC_DATA)) \
			$(patsubst %,$(GAME_INC_DIR)/%,$(GAMEI_INC_GAME))
GAMEI_INC_DIRS = -I $(INC_DIR) \
			-I $(LIBALX_INC_DIR) \
			-I $(DATA_INC_DIR) \
			-I $(GAME_INC_DIR)

GAMECLUI_INC_LIBALX =
GAMECLUI_INC_DATA =	data.h
GAMECLUI_INC =	game_clui.h
GAMECLUI_DEPS = $(SRC_DIR)/game_clui.c \
			$(patsubst %,$(INC_DIR)/%,$(GAMECLUI_INC)) \
			$(patsubst %,$(LIBALX_INC_DIR)/%,$(GAMECLUI_INC_LIBALX)) \
			$(patsubst %,$(DATA_INC_DIR)/%,$(GAMECLUI_INC_DATA))
GAMECLUI_INC_DIRS = -I $(INC_DIR) \
			-I $(LIBALX_INC_DIR) \
			-I $(DATA_INC_DIR)

GAMETUI_INC_LIBALX =	alx_ncur.h
GAMETUI_INC_DATA =	data.h
GAMETUI_INC =	game_tui.h
GAMETUI_DEPS = $(SRC_DIR)/game_tui.c \
			$(patsubst %,$(INC_DIR)/%,$(GAMETUI_INC)) \
			$(patsubst %,$(LIBALX_INC_DIR)/%,$(GAMETUI_INC_LIBALX)) \
			$(patsubst %,$(DATA_INC_DIR)/%,$(GAMETUI_INC_DATA))
GAMETUI_INC_DIRS = -I $(INC_DIR) \
			-I $(LIBALX_INC_DIR) \
			-I $(DATA_INC_DIR)

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
	

parser.o: $(PARS_DEPS)
	$(Q)$(CC) $(CFLAGS) $(PARS_INC_DIRS) -c $< -o $@ $(LIBS)
	@echo  "\tCC $<"
	@echo  ""

game_iface.o: $(GAMEI_DEPS)
	$(Q)$(CC) $(CFLAGS) $(GAMEI_INC_DIRS) -c $< -o $@ $(LIBS)
	@echo  "\tCC $<"
	@echo  ""

game_clui.o: $(GAMECLUI_DEPS)
	$(Q)$(CC) $(CFLAGS) $(GAMECLUI_INC_DIRS) -c $< -o $@ $(LIBS)
	@echo  "\tCC $<"
	@echo  ""

game_tui.o: $(GAMETUI_DEPS)
	$(Q)$(CC) $(CFLAGS) $(GAMETUI_INC_DIRS) -c $< -o $@ $(LIBS)
	@echo  "\tCC $<"
	@echo  ""

tui.o: $(TUI_DEPS)
	$(Q)$(CC) $(CFLAGS) $(TUI_INC_DIRS) -c $< -o $@ $(LIBS)
	@echo  "\tCC $<"
	@echo  ""


clean:
	$(Q)rm -f *.o
