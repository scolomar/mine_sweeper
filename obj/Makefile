# -*- MakeFile -*-

# MACRO = substitute with this

# directories

PNP_DIR = ../

LIBALX_DIR = $(PNP_DIR)/libalx/
LIBALX_INC_DIR = $(LIBALX_DIR)/inc/

MODULES_DIR = $(PNP_DIR)/modules/

CTRL_DIR = $(MODULES_DIR)/ctrl/
CTRL_INC_DIR = $(CTRL_DIR)/inc/

DATA_DIR = $(MODULES_DIR)/data/
DATA_INC_DIR = $(DATA_DIR)/inc/

GEN_DIR = $(MODULES_DIR)/gen/
GEN_INC_DIR = $(GEN_DIR)/inc/

PRN_DIR = $(MODULES_DIR)/prn/
PRN_INC_DIR = $(PRN_DIR)/inc/

UI_DIR = $(MODULES_DIR)/ui/
UI_INC_DIR = $(UI_DIR)/inc/

SRC_DIR = $(PNP_DIR)/src/

# dependencies

ALL = main.o

MAIN_INC_LIBALX =	alx_ncur.h
MAIN_INC_CTRL =		start.h
MAIN_INC_DATA =		data.h
MAIN_INC_GEN =		init.h
MAIN_INC_PRN =		about.h print.h
MAIN_INC_UI =		clui.h tui.h
MAIN_DEPS = $(SRC_DIR)/main.c \
			$(patsubst %,$(LIBALX_INC_DIR)/%,$(MAIN_INC_LIBALX)) \
			$(patsubst %,$(CTRL_INC_DIR)/%,$(MAIN_INC_CTRL)) \
			$(patsubst %,$(DATA_INC_DIR)/%,$(MAIN_INC_DATA)) \
			$(patsubst %,$(GEN_INC_DIR)/%,$(MAIN_INC_GEN)) \
			$(patsubst %,$(PRN_INC_DIR)/%,$(MAIN_INC_PRN)) \
			$(patsubst %,$(UI_INC_DIR)/%,$(MAIN_INC_UI))
MAIN_INC_DIRS = -I $(LIBALX_INC_DIR) \
			-I $(CTRL_INC_DIR) \
			-I $(DATA_INC_DIR) \
			-I $(GEN_INC_DIR) \
			-I $(PRN_INC_DIR) \
			-I $(UI_INC_DIR)


# target: dependencies
#	action

all: $(ALL)

main.o: $(MAIN_DEPS)
	$(CC) $(CFLAGS) $(MAIN_INC_DIRS) -c $< -o $@ $(LIBS)


clean:
	rm -f *.o

################################################################################
######## End of file ###########################################################
################################################################################
######## End of file ###########################################################
################################################################################
######## End of file ###########################################################
################################################################################
