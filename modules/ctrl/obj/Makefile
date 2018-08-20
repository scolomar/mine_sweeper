# -*- MakeFile -*-

# MACRO = substitute with this

# directories

DATA_INC_DIR = $(DATA_DIR)/inc/
GEN_INC_DIR = $(GEN_DIR)/inc/
PRNT_INC_DIR = $(PRNT_DIR)/inc/
UI_INC_DIR = $(UI_DIR)/inc/

INC_DIR = $(CTRL_DIR)/inc/
SRC_DIR = $(CTRL_DIR)/src/
TST_DIR = $(CTRL_DIR)/tst/

# dependencies

ALL = start.o

STRT_INC_DATA =		data.h
STRT_INC_GEN =		init.h
STRT_INC_PRNT =		print.h
STRT_INC_UI =		game_ui.h
STRT_INC =	start.h
STRT_DEPS = $(SRC_DIR)/start.c \
			$(patsubst %,$(DATA_INC_DIR)/%,$(STRT_INC_DATA)) \
			$(patsubst %,$(GEN_INC_DIR)/%,$(STRT_INC_GEN)) \
			$(patsubst %,$(PRNT_INC_DIR)/%,$(STRT_INC_PRNT)) \
			$(patsubst %,$(UI_INC_DIR)/%,$(STRT_INC_UI)) \
			$(patsubst %,$(INC_DIR)/%,$(STRT_INC))
STRT_INC_DIRS = -I $(INC_DIR) \
			-I $(DATA_INC_DIR) \
			-I $(GEN_INC_DIR) \
			-I $(PRNT_INC_DIR) \
			-I $(UI_INC_DIR)

# target: dependencies
#	action

all: $(ALL)
	

start.o: $(STRT_DEPS)
	$(Q)$(CC) $(CFLAGS) $(STRT_INC_DIRS) -c $< -o $@ $(LIBS)
	@echo  "\tCC $<"
	@echo  ""


clean:
	$(Q)rm -f *.o
