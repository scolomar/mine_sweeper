# -*- MakeFile -*-

# MACRO = substitute with this

# directories

PNP_DIR = ../../../

LIBALX_DIR = $(PNP_DIR)/libalx/
LIBALX_INC_DIR = $(LIBALX_DIR)/inc/

MODULES_DIR = $(PNP_DIR)/modules/

DATA_DIR = $(MODULES_DIR)/data/
DATA_INC_DIR = $(DATA_DIR)/inc/

PRN_DIR = $(MODULES_DIR)/prn/
PRN_INC_DIR = $(PRN_DIR)/inc/

CHK_DIR = $(MODULES_DIR)/chk/
INC_DIR = $(CHK_DIR)/inc/
SRC_DIR = $(CHK_DIR)/src/
TST_DIR = $(CHK_DIR)/tst/

# dependencies

ALL = check.o

CHCK_INC_DATA =		data.h
CHCK_INC_PRN =		print.h
CHCK_INC =	check.h
CHCK_DEPS = $(SRC_DIR)/check.c \
			$(patsubst %,$(DATA_INC_DIR)/%,$(CHCK_INC_DATA)) \
			$(patsubst %,$(PRN_INC_DIR)/%,$(CHCK_INC_PRN)) \
			$(patsubst %,$(INC_DIR)/%,$(CHCK_INC))
CHCK_INC_DIRS = -I $(DATA_INC_DIR) \
			-I $(PRN_INC_DIR) \
			-I $(INC_DIR)

# target: dependencies
#	action

all: $(ALL)
	

check.o: $(CHCK_DEPS)
	$(CC) $(CFLAGS) $(CHCK_INC_DIRS) -c $< -o $@ $(LIBS)


clean:
	rm -f *.o
