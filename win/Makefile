# -*- MakeFile -*-

# MACRO = substitute with this

# directories

MSW_DIR = ../

LIBALX_DIR = $(MSW_DIR)/libalx/
LIBALX_OBJ_DIR = $(LIBALX_DIR)/obj/

MODULES_DIR = $(MSW_DIR)/modules/

CHK_DIR = $(MODULES_DIR)/chk/
CHK_OBJ_DIR = $(CHK_DIR)/obj/

CTRL_DIR = $(MODULES_DIR)/ctrl/
CTRL_OBJ_DIR = $(CTRL_DIR)/obj/

DATA_DIR = $(MODULES_DIR)/data/
DATA_OBJ_DIR = $(DATA_DIR)/obj/

GAME_DIR = $(MODULES_DIR)/game/
GAME_OBJ_DIR = $(GAME_DIR)/obj/

GEN_DIR = $(MODULES_DIR)/gen/
GEN_OBJ_DIR = $(GEN_DIR)/obj/

PRN_DIR = $(MODULES_DIR)/prn/
PRN_OBJ_DIR = $(PRN_DIR)/obj/

UI_DIR = $(MODULES_DIR)/ui/
UI_OBJ_DIR = $(UI_DIR)/obj/

OBJ_DIR = $(MSW_DIR)/obj/

# dependencies

ALL = exe.exe

MSW_OBJ_LIBALX =	alx_file.o alx_getnum.o alx_ncur.o alx_seed.o
MSW_OBJ_CHK =		check.o
MSW_OBJ_CTRL =		start.o
MSW_OBJ_DATA =		data.o
MSW_OBJ_GEN =		init.o
MSW_OBJ_PRN =		about.o print.o
MSW_OBJ_UI =		clui.o game_ui.o tui.o

MSW_OBJS = $(OBJ_DIR)/main.o \
			$(patsubst %,$(LIBALX_OBJ_DIR)/%,$(MSW_OBJ_LIBALX)) \
			$(patsubst %,$(CHK_OBJ_DIR)/%,$(MSW_OBJ_CHK)) \
			$(patsubst %,$(CTRL_OBJ_DIR)/%,$(MSW_OBJ_CTRL)) \
			$(patsubst %,$(DATA_OBJ_DIR)/%,$(MSW_OBJ_DATA)) \
			$(patsubst %,$(GAME_OBJ_DIR)/%,$(MSW_OBJ_GAME)) \
			$(patsubst %,$(GEN_OBJ_DIR)/%,$(MSW_OBJ_GEN)) \
			$(patsubst %,$(PRN_OBJ_DIR)/%,$(MSW_OBJ_PRN)) \
			$(patsubst %,$(UI_OBJ_DIR)/%,$(MSW_OBJ_UI))


# target: dependencies
#	action

all: $(ALL)


exe.exe: $(MSW_OBJS)
	$(CC) $(CFLAGS) $^ -o $@ $(LIBS)


clean:
	rm -f $(ALL)

################################################################################
######## End of file ###########################################################
################################################################################
######## End of file ###########################################################
################################################################################
######## End of file ###########################################################
################################################################################
