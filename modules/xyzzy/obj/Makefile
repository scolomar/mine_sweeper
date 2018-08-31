# -*- MakeFile -*-

# MACRO = substitute with this

# directories

GAME_INC_DIR	= $(GAME_DIR)/inc/

INC_DIR	= $(XYZZY_DIR)/inc/
SRC_DIR	= $(XYZZY_DIR)/src/

# dependencies

_ALL	= xyzzy.o
ALL = $(_ALL) xyzzy_mod.o

XYZZY_INC_GAME	= game_iface.h
XYZZY_INC	= xyzzy.h
XYZZY_DEPS	= $(SRC_DIR)/xyzzy.c \
			$(patsubst %,$(INC_DIR)/%,$(XYZZY_INC)) \
			$(patsubst %,$(GAME_INC_DIR)/%,$(XYZZY_INC_GAME))
XYZZY_INC_DIRS	= -I $(INC_DIR) \
			-I $(GAME_INC_DIR)

# target: dependencies
#	action

all: $(ALL)


xyzzy_mod.o: $(_ALL)
	$(Q)$(LD) -r $^ -o $@
	@echo  "\tLD $@"
	@echo  ""
	

xyzzy.o: $(XYZZY_DEPS)
	$(Q)$(CC) $(CFLAGS) $(XYZZY_INC_DIRS) -c $< -o $@ $(LIBS)
	@echo  "\tCC $<"
	@echo  ""


clean:
	$(Q)rm -f *.o
