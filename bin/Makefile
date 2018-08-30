# -*- MakeFile -*-

# directories

LIBALX_OBJ_DIR	= $(LIBALX_DIR)/obj/

ABOUT_DIR	= $(MODULES_DIR)/about/
ABOUT_OBJ_DIR	= $(ABOUT_DIR)/obj/

CTRL_DIR	= $(MODULES_DIR)/ctrl/
CTRL_OBJ_DIR	= $(CTRL_DIR)/obj/

GAME_DIR	= $(MODULES_DIR)/game/
GAME_OBJ_DIR	= $(GAME_DIR)/obj/

MENU_DIR	= $(MODULES_DIR)/menu/
MENU_OBJ_DIR	= $(MENU_DIR)/obj/

PLAY_DIR	= $(MODULES_DIR)/player/
PLAY_OBJ_DIR	= $(PLAY_DIR)/obj/

SAVE_DIR	= $(MODULES_DIR)/save/
SAVE_OBJ_DIR	= $(SAVE_DIR)/obj/

XYZZY_DIR	= $(MODULES_DIR)/xyzzy/
XYZZY_OBJ_DIR	= $(XYZZY_DIR)/obj/

OBJ_DIR	= $(MAIN_DIR)/obj/

# dependencies
_ALL	= mine_sweeper mine_sweeper.exe

ifeq ($(OS), linux)
  ALL	= mine_sweeper
else ifeq ($(OS), win)
  ALL	= mine_sweeper.exe
endif

MAIN_OBJ_LIBALX	= alx_file.o alx_getnum.o alx_ncur.o alx_seed.o
MAIN_OBJ_ABOUT	= about_mod.o
MAIN_OBJ_CTRL	= ctrl_mod.o
MAIN_OBJ_GAME	= game_mod.o
MAIN_OBJ_MENU	= menu_mod.o
MAIN_OBJ_PLAY	= player_mod.o
MAIN_OBJ_SAVE	= save_mod.o
MAIN_OBJ_XYZZY	= xyzzy_mod.o

MAIN_OBJS	= $(OBJ_DIR)/main.o \
			$(patsubst %,$(LIBALX_OBJ_DIR)/%,$(MAIN_OBJ_LIBALX)) \
			$(patsubst %,$(ABOUT_OBJ_DIR)/%,$(MAIN_OBJ_ABOUT)) \
			$(patsubst %,$(CTRL_OBJ_DIR)/%,$(MAIN_OBJ_CTRL)) \
			$(patsubst %,$(GAME_OBJ_DIR)/%,$(MAIN_OBJ_GAME)) \
			$(patsubst %,$(MENU_OBJ_DIR)/%,$(MAIN_OBJ_MENU)) \
			$(patsubst %,$(PLAY_OBJ_DIR)/%,$(MAIN_OBJ_PLAY)) \
			$(patsubst %,$(SAVE_OBJ_DIR)/%,$(MAIN_OBJ_SAVE)) \
			$(patsubst %,$(XYZZY_OBJ_DIR)/%,$(MAIN_OBJ_XYZZY))


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
	$(Q)rm -f $(_ALL)
	@echo  "Clean binaries"

################################################################################
######## End of file ###########################################################
################################################################################
######## End of file ###########################################################
################################################################################
######## End of file ###########################################################
################################################################################
