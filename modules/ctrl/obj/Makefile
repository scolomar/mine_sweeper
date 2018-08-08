# -*- MakeFile -*-

# MACRO = substitute with this

# directories

PNP_DIR = ../../../

MODULES_DIR = $(PNP_DIR)/modules/

CHK_DIR = $(MODULES_DIR)/chk/
CHK_INC_DIR = $(CHK_DIR)/inc/

DATA_DIR = $(MODULES_DIR)/data/
DATA_INC_DIR = $(DATA_DIR)/inc/

GEN_DIR = $(MODULES_DIR)/gen/
GEN_INC_DIR = $(GEN_DIR)/inc/

PRN_DIR = $(MODULES_DIR)/prn/
PRN_INC_DIR = $(PRN_DIR)/inc/

UI_DIR = $(MODULES_DIR)/ui/
UI_INC_DIR = $(UI_DIR)/inc/

CTRL_DIR = $(MODULES_DIR)/ctrl/
INC_DIR = $(CTRL_DIR)/inc/
SRC_DIR = $(CTRL_DIR)/src/
TST_DIR = $(CTRL_DIR)/tst/

# dependencies

ALL = start.o

STRT_INC_CHK =		check.h
STRT_INC_DATA =		data.h
STRT_INC_GEN =		init.h
STRT_INC_PRN =		print.h
STRT_INC_UI =		game_ui.h
STRT_INC =	start.h
STRT_DEPS = $(SRC_DIR)/start.c \
			$(patsubst %,$(CHK_INC_DIR)/%,$(STRT_INC_CHK)) \
			$(patsubst %,$(DATA_INC_DIR)/%,$(STRT_INC_DATA)) \
			$(patsubst %,$(GEN_INC_DIR)/%,$(STRT_INC_GEN)) \
			$(patsubst %,$(PRN_INC_DIR)/%,$(STRT_INC_PRN)) \
			$(patsubst %,$(UI_INC_DIR)/%,$(STRT_INC_UI)) \
			$(patsubst %,$(INC_DIR)/%,$(STRT_INC))
STRT_INC_DIRS = -I $(INC_DIR) \
			-I $(CHK_INC_DIR) \
			-I $(DATA_INC_DIR) \
			-I $(GEN_INC_DIR) \
			-I $(PRN_INC_DIR) \
			-I $(UI_INC_DIR)

# target: dependencies
#	action

all: $(ALL)
	

start.o: $(STRT_DEPS)
	$(CC) $(CFLAGS) $(STRT_INC_DIRS) -c $< -o $@ $(LIBS)


clean:
	rm -f *.o
