# -*- MakeFile -*-

# MACRO = substitute with this

# directories

GAME_INC_DIR = $(GAME_DIR)/inc/
MENU_INC_DIR = $(MENU_DIR)/inc/
PLAY_INC_DIR = $(PLAY_DIR)/inc/

INC_DIR = $(CTRL_DIR)/inc/
SRC_DIR = $(CTRL_DIR)/src/
TST_DIR = $(CTRL_DIR)/tst/

# dependencies

_ALL = start.o
ALL = $(_ALL) ctrl_mod.o

STRT_INC_GAME	= game.h game_iface.h
STRT_INC_MENU	= menu_iface.h
STRT_INC_PLAY	= player_iface.h
STRT_INC	= start.h
STRT_DEPS	= $(SRC_DIR)/start.c \
			$(patsubst %,$(GAME_INC_DIR)/%,$(STRT_INC_GAME)) \
			$(patsubst %,$(MENU_INC_DIR)/%,$(STRT_INC_MENU)) \
			$(patsubst %,$(PLAY_INC_DIR)/%,$(STRT_INC_PLAY)) \
			$(patsubst %,$(INC_DIR)/%,$(STRT_INC))
STRT_INC_DIRS = -I $(INC_DIR) \
			-I $(GAME_INC_DIR) \
			-I $(MENU_INC_DIR) \
			-I $(PLAY_INC_DIR)

# target: dependencies
#	action

all: $(ALL)
	

ctrl_mod.o: $(_ALL)
	$(Q)$(LD) -r $^ -o $@
	@echo  "\tLD $@"
	@echo  ""


start.o: $(STRT_DEPS)
	$(Q)$(CC) $(CFLAGS) $(STRT_INC_DIRS) -c $< -o $@ $(LIBS)
	@echo  "\tCC $<"
	@echo  ""


clean:
	$(Q)rm -f *.o
