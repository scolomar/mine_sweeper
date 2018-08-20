# -*- MakeFile -*-

# MACRO = substitute with this

# directories

LIBALX_INC_DIR = $(LIBALX_DIR)/inc/

INC_DIR = $(DATA_DIR)/inc/
SRC_DIR = $(DATA_DIR)/src/
TST_DIR = $(DATA_DIR)/tst/

# dependencies

ALL = data.o

DATA_INC_LIBALX =	alx_seed.h
DATA_INC =	data.h
DATA_DEPS = $(SRC_DIR)/data.c \
			$(patsubst %,$(INC_DIR)/%,$(DATA_INC)) \
			$(patsubst %,$(LIBALX_INC_DIR)/%,$(DATA_INC_LIBALX))
DATA_INC_DIRS = -I $(INC_DIR) \
			-I $(LIBALX_INC_DIR)

# target: dependencies
#	action

all: $(ALL)
	

data.o: $(DATA_DEPS)
	$(Q)$(CC) $(CFLAGS) $(DATA_INC_DIRS) -c $< -o $@ $(LIBS)
	@echo  "\tCC $<"
	@echo  ""


clean:
	$(Q)rm -f *.o
