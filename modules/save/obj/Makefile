# -*- MakeFile -*-

# MACRO = substitute with this

# directories

LIBALX_INC_DIR = $(LIBALX_DIR)/inc/

DATA_INC_DIR = $(DATA_DIR)/inc/

INC_DIR = $(SAVE_DIR)/inc/
SRC_DIR = $(SAVE_DIR)/src/

# dependencies

ALL = save.o

SAVE_INC_LIBALX =
SAVE_INC_DATA =		data.h
SAVE_INC =	save.h
SAVE_DEPS = $(SRC_DIR)/save.c \
			$(patsubst %,$(INC_DIR)/%,$(SAVE_INC)) \
			$(patsubst %,$(LIBALX_INC_DIR)/%,$(SAVE_INC_LIBALX)) \
			$(patsubst %,$(DATA_INC_DIR)/%,$(SAVE_INC_DATA))
SAVE_INC_DIRS = -I $(INC_DIR) \
			-I $(DATA_INC_DIR) \
			-I $(LIBALX_INC_DIR)

# target: dependencies
#	action

all: $(ALL)
	

save.o: $(SAVE_DEPS)
	$(Q)$(CC) $(CFLAGS) $(SAVE_INC_DIRS) -c $< -o $@ $(LIBS)
	@echo  "\tCC $<"
	@echo  ""


clean:
	$(Q)rm -f *.o
