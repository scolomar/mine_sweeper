# -*- MakeFile -*-

# MACRO = substitute with this

# directories

LIBALX_INC_DIR = $(LIBALX_DIR)/inc/

DATA_INC_DIR = $(DATA_DIR)/inc/
SAVE_INC_DIR = $(SAVE_DIR)/inc/

INC_DIR = $(GEN_DIR)/inc/
SRC_DIR = $(GEN_DIR)/src/

# dependencies

ALL = init.o

INIT_INC_LIBALX =	alx_seed.h
INIT_INC_DATA =		data.h
INIT_INC_SAVE =		save.h
INIT_INC =	init.h
INIT_DEPS = $(SRC_DIR)/init.c \
			$(patsubst %,$(INC_DIR)/%,$(INIT_INC)) \
			$(patsubst %,$(LIBALX_INC_DIR)/%,$(INIT_INC_LIBALX)) \
			$(patsubst %,$(DATA_INC_DIR)/%,$(INIT_INC_DATA)) \
			$(patsubst %,$(SAVE_INC_DIR)/%,$(INIT_INC_SAVE))
INIT_INC_DIRS = -I $(INC_DIR) \
			-I $(DATA_INC_DIR) \
			-I $(SAVE_INC_DIR) \
			-I $(LIBALX_INC_DIR)

# target: dependencies
#	action

all: $(ALL)
	

init.o: $(INIT_DEPS)
	$(Q)$(CC) $(CFLAGS) $(INIT_INC_DIRS) -c $< -o $@ $(LIBS)
	@echo  "\tCC $<"
	@echo  ""


clean:
	$(Q)rm -f *.o
