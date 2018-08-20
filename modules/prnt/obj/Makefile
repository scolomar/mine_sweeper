# -*- MakeFile -*-

# MACRO = substitute with this

# directories

LIBALX_INC_DIR = $(LIBALX_DIR)/inc/

DATA_INC_DIR = $(DATA_DIR)/inc/

INC_DIR = $(PRNT_DIR)/inc/
SRC_DIR = $(PRNT_DIR)/src/

# dependencies

ALL = about.o print.o

ABOU_INC_LIBALX =	alx_file.h
ABOU_INC_DATA =		data.h
ABOU_INC =	about.h
ABOU_DEPS = $(SRC_DIR)/about.c \
			$(patsubst %,$(LIBALX_INC_DIR)/%,$(ABOU_INC_LIBALX)) \
			$(patsubst %,$(DATA_INC_DIR)/%,$(ABOU_INC_DATA)) \
			$(patsubst %,$(INC_DIR)/%,$(ABOU_INC))
ABOU_INC_DIRS = -I $(INC_DIR) \
			-I $(LIBALX_INC_DIR) \
			-I $(DATA_INC_DIR)

PRNT_INC_LIBALX =
PRNT_INC_DATA =		data.h
PRNT_INC =	print.h
PRNT_DEPS = $(SRC_DIR)/print.c \
			$(patsubst %,$(LIBALX_INC_DIR)/%,$(PRNT_INC_LIBALX)) \
			$(patsubst %,$(DATA_INC_DIR)/%,$(PRNT_INC_DATA)) \
			$(patsubst %,$(INC_DIR)/%,$(PRNT_INC))
PRNT_INC_DIRS = -I $(INC_DIR) \
			-I $(LIBALX_INC_DIR) \
			-I $(DATA_INC_DIR)

# target: dependencies
#	action

all: $(ALL)
	

about.o: $(ABOU_DEPS)
	$(Q)$(CC) $(CFLAGS) $(ABOU_INC_DIRS) -c $< -o $@ $(LIBS)
	@echo  "\tCC $<"
	@echo  ""

print.o: $(PRNT_DEPS)
	$(Q)$(CC) $(CFLAGS) $(PRNT_INC_DIRS) -c $< -o $@ $(LIBS)
	@echo  "\tCC $<"
	@echo  ""


clean:
	$(Q)rm -f *.o
