# -*- MakeFile -*-

# MACRO = substitute with this

# directories

PNP_DIR = ../../../

LIBALX_DIR = $(PNP_DIR)/libalx/
LIBALX_INC_DIR = $(LIBALX_DIR)/inc/

MODULES_DIR = $(PNP_DIR)/modules/

DATA_DIR = $(MODULES_DIR)/data/
DATA_INC_DIR = $(DATA_DIR)/inc/

GEN_DIR = $(MODULES_DIR)/gen/
INC_DIR = $(GEN_DIR)/inc/
SRC_DIR = $(GEN_DIR)/src/
TST_DIR = $(GEN_DIR)/tst/

# dependencies

ALL = init.o

INIT_INC_LIBALX =	alx_seed.h
INIT_INC_DATA =		data.h
INIT_INC =	init.h
INIT_DEPS = $(SRC_DIR)/init.c \
			$(patsubst %,$(INC_DIR)/%,$(INIT_INC)) \
			$(patsubst %,$(LIBALX_INC_DIR)/%,$(INIT_INC_LIBALX)) \
			$(patsubst %,$(DATA_INC_DIR)/%,$(INIT_INC_DATA))
INIT_INC_DIRS = -I $(INC_DIR) \
			-I $(DATA_INC_DIR) \
			-I $(LIBALX_INC_DIR)

# target: dependencies
#	action

all: $(ALL)
	

init.o: $(INIT_DEPS)
	$(CC) $(CFLAGS) $(INIT_INC_DIRS) -c $< -o $@ $(LIBS)


clean:
	rm -f *.o
