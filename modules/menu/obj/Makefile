# -*- MakeFile -*-

# MACRO = substitute with this

# directories

LIBALX_INC_DIR	= $(LIBALX_DIR)/inc/

ABOUT_INC_DIR	= $(ABOUT_DIR)/inc/
CTRL_INC_DIR	= $(CTRL_DIR)/inc/
GAME_INC_DIR	= $(GAME_DIR)/inc/
PLAY_INC_DIR	= $(PLAY_DIR)/inc/
SAVE_INC_DIR	= $(SAVE_DIR)/inc/

INC_DIR	= $(MENU_DIR)/inc/
SRC_DIR	= $(MENU_DIR)/src/

# dependencies

_ALL	= parser.o menu_iface.o menu_clui.o menu_tui.o
ALL	= $(_ALL) menu_mod.o

PARS_INC_LIBALX	= alx_seed.h
PARS_INC_ABOUT	= about.h
PARS_INC_CTRL	= start.h
PARS_INC_GAME	= game_iface.h
PARS_INC_PLAY	= player_iface.h
PARS_INC_SAVE	= save.h
PARS_INC	= parser.h	menu_iface.h
PARS_DEPS	= $(SRC_DIR)/parser.c \
			$(patsubst %,$(INC_DIR)/%,$(PARS_INC)) \
			$(patsubst %,$(LIBALX_INC_DIR)/%,$(PARS_INC_LIBALX)) \
			$(patsubst %,$(ABOUT_INC_DIR)/%,$(PARS_INC_ABOUT)) \
			$(patsubst %,$(CTRL_INC_DIR)/%,$(PARS_INC_CTRL)) \
			$(patsubst %,$(GAME_INC_DIR)/%,$(PARS_INC_GAME)) \
			$(patsubst %,$(PLAY_INC_DIR)/%,$(PARS_INC_PLAY)) \
			$(patsubst %,$(SAVE_INC_DIR)/%,$(PARS_INC_SAVE))
PARS_INC_DIRS	= -I $(INC_DIR) \
			-I $(LIBALX_INC_DIR) \
			-I $(ABOUT_INC_DIR) \
			-I $(CTRL_INC_DIR) \
			-I $(GAME_INC_DIR) \
			-I $(PLAY_INC_DIR) \
			-I $(SAVE_INC_DIR)

MENUI_INC_CTRL	= start.h
MENUI_INC_GAME	= game_iface.h
MENUI_INC	= menu_iface.h	menu_clui.h menu_tui.h
MENUI_DEPS	= $(SRC_DIR)/menu_iface.c \
			$(patsubst %,$(INC_DIR)/%,$(MENUI_INC)) \
			$(patsubst %,$(CTRL_INC_DIR)/%,$(MENUI_INC_CTRL)) \
			$(patsubst %,$(GAME_INC_DIR)/%,$(MENUI_INC_GAME))
MENUI_INC_DIRS	= -I $(INC_DIR) \
			-I $(CTRL_INC_DIR) \
			-I $(GAME_INC_DIR)

MENUCLUI_INC_LIBALX	= alx_getnum.h
MENUCLUI_INC_ABOUT	= about.h
MENUCLUI_INC_CTRL	= start.h
MENUCLUI_INC_GAME	= game_iface.h
MENUCLUI_INC_SAVE	= save.h
MENUCLUI_INC		= menu_clui.h	menu_iface.h
MENUCLUI_DEPS	= $(SRC_DIR)/menu_clui.c \
			$(patsubst %,$(INC_DIR)/%,$(MENUCLUI_INC)) \
			$(patsubst %,$(LIBALX_INC_DIR)/%,$(MENUCLUI_INC_LIBALX)) \
			$(patsubst %,$(ABOUT_INC_DIR)/%,$(MENUCLUI_INC_ABOUT)) \
			$(patsubst %,$(GAME_INC_DIR)/%,$(MENUCLUI_INC_GAME)) \
			$(patsubst %,$(CTRL_INC_DIR)/%,$(MENUCLUI_INC_CTRL)) \
			$(patsubst %,$(SAVE_INC_DIR)/%,$(MENUCLUI_INC_SAVE))
MENUCLUI_INC_DIRS	= -I $(INC_DIR) \
			-I $(LIBALX_INC_DIR) \
			-I $(ABOUT_INC_DIR) \
			-I $(CTRL_INC_DIR) \
			-I $(GAME_INC_DIR) \
			-I $(SAVE_INC_DIR)

MENUTUI_INC_LIBALX	= alx_ncur.h
MENUTUI_INC_ABOUT	= about.h
MENUTUI_INC_CTRL	= start.h
MENUTUI_INC_GAME	= game_iface.h
MENUTUI_INC_SAVE	= save.h
MENUTUI_INC		= menu_tui.h	menu_iface.h
MENUTUI_DEPS	= $(SRC_DIR)/menu_tui.c \
			$(patsubst %,$(INC_DIR)/%,$(MENUTUI_INC)) \
			$(patsubst %,$(LIBALX_INC_DIR)/%,$(MENUTUI_INC_LIBALX)) \
			$(patsubst %,$(ABOUT_INC_DIR)/%,$(MENUTUI_INC_ABOUT)) \
			$(patsubst %,$(GAME_INC_DIR)/%,$(MENUTUI_INC_GAME)) \
			$(patsubst %,$(CTRL_INC_DIR)/%,$(MENUTUI_INC_CTRL)) \
			$(patsubst %,$(SAVE_INC_DIR)/%,$(MENUTUI_INC_SAVE))
MENUTUI_INC_DIRS	= -I $(INC_DIR) \
			-I $(LIBALX_INC_DIR) \
			-I $(ABOUT_INC_DIR) \
			-I $(CTRL_INC_DIR) \
			-I $(GAME_INC_DIR) \
			-I $(SAVE_INC_DIR)

# target: dependencies
#	action

all: $(ALL)


menu_mod.o: $(_ALL)
	$(Q)$(LD) -r $^ -o $@
	@echo  "\tLD $@"
	@echo  ""


parser.o: $(PARS_DEPS)
	$(Q)$(CC) $(CFLAGS) $(PARS_INC_DIRS) -c $< -o $@ $(LIBS)
	@echo  "\tCC $<"
	@echo  ""

menu_iface.o: $(MENUI_DEPS)
	$(Q)$(CC) $(CFLAGS) $(MENUI_INC_DIRS) -c $< -o $@ $(LIBS)
	@echo  "\tCC $<"
	@echo  ""

menu_clui.o: $(MENUCLUI_DEPS)
	$(Q)$(CC) $(CFLAGS) $(MENUCLUI_INC_DIRS) -c $< -o $@ $(LIBS)
	@echo  "\tCC $<"
	@echo  ""

menu_tui.o: $(MENUTUI_DEPS)
	$(Q)$(CC) $(CFLAGS) $(MENUTUI_INC_DIRS) -c $< -o $@ $(LIBS)
	@echo  "\tCC $<"
	@echo  ""


clean:
	$(Q)rm -f *.o
