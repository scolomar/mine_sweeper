# -*- MakeFile -*-

# directories

LIBALX_OBJ_DIR = $(LIBALX_DIR)/obj/

CTRL_DIR = $(MODULES_DIR)/ctrl/
CTRL_OBJ_DIR = $(CTRL_DIR)/obj/

DATA_DIR = $(MODULES_DIR)/data/
DATA_OBJ_DIR = $(DATA_DIR)/obj/

GAME_DIR = $(MODULES_DIR)/game/
GAME_OBJ_DIR = $(GAME_DIR)/obj/

GEN_DIR = $(MODULES_DIR)/gen/
GEN_OBJ_DIR = $(GEN_DIR)/obj/

PRNT_DIR = $(MODULES_DIR)/prnt/
PRNT_OBJ_DIR = $(PRNT_DIR)/obj/

SAVE_DIR = $(MODULES_DIR)/save/
SAVE_OBJ_DIR = $(SAVE_DIR)/obj/

UI_DIR = $(MODULES_DIR)/ui/
UI_OBJ_DIR = $(UI_DIR)/obj/

OBJ_DIR = $(MAIN_DIR)/obj/

# dependencies
_ALL = mine_sweeper mine_sweeper.exe

ifeq ($(OS), linux)
  ALL = mine_sweeper
else ifeq ($(OS), win)
  ALL = mine_sweeper.exe
endif

MAIN_OBJ_LIBALX =	alx_file.o alx_getnum.o alx_ncur.o alx_seed.o
MAIN_OBJ_CTRL =		start.o
MAIN_OBJ_DATA =		data.o
MAIN_OBJ_GAME =		game.o
MAIN_OBJ_GEN =		init.o
MAIN_OBJ_PRNT =		about.o print.o
MAIN_OBJ_SAVE =		save.o
MAIN_OBJ_UI =		clui.o game_ui.o tui.o

MAIN_OBJS = $(OBJ_DIR)/main.o \
			$(patsubst %,$(LIBALX_OBJ_DIR)/%,$(MAIN_OBJ_LIBALX)) \
			$(patsubst %,$(CTRL_OBJ_DIR)/%,$(MAIN_OBJ_CTRL)) \
			$(patsubst %,$(DATA_OBJ_DIR)/%,$(MAIN_OBJ_DATA)) \
			$(patsubst %,$(GAME_OBJ_DIR)/%,$(MAIN_OBJ_GAME)) \
			$(patsubst %,$(GEN_OBJ_DIR)/%,$(MAIN_OBJ_GEN)) \
			$(patsubst %,$(PRNT_OBJ_DIR)/%,$(MAIN_OBJ_PRNT)) \
			$(patsubst %,$(SAVE_OBJ_DIR)/%,$(MAIN_OBJ_SAVE)) \
			$(patsubst %,$(UI_OBJ_DIR)/%,$(MAIN_OBJ_UI))


# target: dependencies
#	action

all: $(ALL)


mine_sweeper: $(MAIN_OBJS)
	$(Q)$(CC) $^ -o $@ $(LIBS)
	@echo  "\tLD $<"
	@echo  ""

mine_sweeper.exe: $(MAIN_OBJS)
	$(Q)$(CC) $^ -o $@ $(LIBS)
	@echo  "\tLD $<"
	@echo  ""


clean:
	$(Q)rm -f $(ALL)
	@echo  "Clean binaries"

################################################################################
######## End of file ###########################################################
################################################################################
######## End of file ###########################################################
################################################################################
######## End of file ###########################################################
################################################################################
