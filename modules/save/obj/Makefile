# -*- MakeFile -*-

# MACRO = substitute with this

# directories

GAME_INC_DIR = $(GAME_DIR)/inc/

INC_DIR = $(SAVE_DIR)/inc/
SRC_DIR = $(SAVE_DIR)/src/

# dependencies

_ALL = save.o
ALL = $(_ALL) save_mod.o

SAVE_INC_GAME =		game.h
SAVE_INC =	save.h
SAVE_DEPS = $(SRC_DIR)/save.c \
			$(patsubst %,$(INC_DIR)/%,$(SAVE_INC)) \
			$(patsubst %,$(GAME_INC_DIR)/%,$(SAVE_INC_GAME))
SAVE_INC_DIRS = -I $(INC_DIR) \
			-I $(GAME_INC_DIR)

# target: dependencies
#	action

all: $(ALL)


save_mod.o: $(_ALL)
	$(Q)$(LD) -r $^ -o $@
	@echo  "\tLD $@"
	@echo  ""
	

save.o: $(SAVE_DEPS)
	$(Q)$(CC) $(CFLAGS) $(SAVE_INC_DIRS) -c $< -o $@ $(LIBS)
	@echo  "\tCC $<"
	@echo  ""


clean:
	$(Q)rm -f *.o
