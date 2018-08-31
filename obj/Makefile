# -*- MakeFile -*-

# MACRO = substitute with this

# directories

LIBALX_INC_DIR	= $(LIBALX_DIR)/inc/

ABOUT_DIR	= $(MODULES_DIR)/about/
ABOUT_INC_DIR	= $(ABOUT_DIR)/inc/

CTRL_DIR	= $(MODULES_DIR)/ctrl/
CTRL_INC_DIR	= $(CTRL_DIR)/inc/

GAME_DIR	= $(MODULES_DIR)/game/
GAME_INC_DIR	= $(GAME_DIR)/inc/

MENU_DIR	= $(MODULES_DIR)/menu/
MENU_INC_DIR	= $(MENU_DIR)/inc/

PLAY_DIR	= $(MODULES_DIR)/player/
PLAY_INC_DIR	= $(PLAY_DIR)/inc/

SAVE_DIR	= $(MODULES_DIR)/save/
SAVE_INC_DIR	= $(SAVE_DIR)/inc/

SRC_DIR	= $(MAIN_DIR)/src/

# dependencies

ALL = main.o

MAIN_INC_LIBALX	= alx_ncur.h
MAIN_INC_ABOUT	= about.h
MAIN_INC_CTRL	= start.h
MAIN_INC_GAME	= game.h
MAIN_INC_MENU	= parser.h menu_iface.h
MAIN_INC_PLAY	= player_iface.h
MAIN_INC_SAVE	= save.h
MAIN_DEPS	= $(SRC_DIR)/main.c \
			$(patsubst %,$(LIBALX_INC_DIR)/%,$(MAIN_INC_LIBALX)) \
			$(patsubst %,$(ABOUT_INC_DIR)/%,$(MAIN_INC_ABOUT)) \
			$(patsubst %,$(CTRL_INC_DIR)/%,$(MAIN_INC_CTRL)) \
			$(patsubst %,$(GAME_INC_DIR)/%,$(MAIN_INC_GAME)) \
			$(patsubst %,$(MENU_INC_DIR)/%,$(MAIN_INC_MENU)) \
			$(patsubst %,$(PLAY_INC_DIR)/%,$(MAIN_INC_PLAY)) \
			$(patsubst %,$(SAVE_INC_DIR)/%,$(MAIN_INC_SAVE))
MAIN_INC_DIRS	= -I $(LIBALX_INC_DIR) \
			-I $(ABOUT_INC_DIR) \
			-I $(CTRL_INC_DIR) \
			-I $(GAME_INC_DIR) \
			-I $(MENU_INC_DIR) \
			-I $(PLAY_INC_DIR) \
			-I $(SAVE_INC_DIR)


# target: dependencies
#	action

all: $(ALL)

main.o: $(MAIN_DEPS)
	$(Q)$(CC) $(CFLAGS) $(MAIN_INC_DIRS) -c $< -o $@ $(LIBS)
	@echo  "\tCC $<"
	@echo  ""


clean:
	$(Q)rm -f *.o

################################################################################
######## End of file ###########################################################
################################################################################
######## End of file ###########################################################
################################################################################
######## End of file ###########################################################
################################################################################
