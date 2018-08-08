# -*- MakeFile -*-

# MACRO = substitute with this

# directories

LIBALX_DIR = ../

INC_DIR = $(LIBALX_DIR)/inc/
OBJ_DIR = $(LIBALX_DIR)/obj/
SRC_DIR = $(LIBALX_DIR)/src/

# dependencies

ALL = alx_cmp.o alx_file.o alx_getnum.o alx_mask.o alx_math.o alx_ncur.o alx_seed.o

CMP_INC = alx_cmp.h
CMP_DEPS = $(SRC_DIR)/alx_cmp.c $(patsubst %,$(INC_DIR)/%,$(CMP_INC))
CMP_INC_DIRS = -I $(INC_DIR)

FILE_INC = alx_file.h
FILE_DEPS = $(SRC_DIR)/alx_file.c $(patsubst %,$(INC_DIR)/%,$(FILE_INC))
FILE_INC_DIRS = -I $(INC_DIR)

GETN_INC = alx_getnum.h
GETN_DEPS = $(SRC_DIR)/alx_getnum.c $(patsubst %,$(INC_DIR)/%,$(GETN_INC))
GETN_INC_DIRS = -I $(INC_DIR)

MASK_INC = alx_mask.h
MASK_DEPS = $(SRC_DIR)/alx_mask.c $(patsubst %,$(INC_DIR)/%,$(MASK_INC))
MASK_INC_DIRS = -I $(INC_DIR)

MATH_INC = alx_math.h
MATH_DEPS = $(SRC_DIR)/alx_math.c $(patsubst %,$(INC_DIR)/%,$(MATH_INC))
MATH_INC_DIRS = -I $(INC_DIR)

NCUR_INC = alx_ncur.h
NCUR_DEPS = $(SRC_DIR)/alx_ncur.c $(patsubst %,$(INC_DIR)/%,$(NCUR_INC))
NCUR_INC_DIRS = -I $(INC_DIR)

SEED_INC = alx_seed.h
SEED_DEPS = $(SRC_DIR)/alx_seed.c $(patsubst %,$(INC_DIR)/%,$(SEED_INC))
SEED_INC_DIRS = -I $(INC_DIR)

# target: dependencies
#	action

all: $(ALL)


alx_cmp.o: $(CMP_DEPS)
	$(CC) $(CFLAGS) $(CMP_INC_DIRS) -c $< -o $@ $(LIBS)

alx_file.o: $(FILE_DEPS)
	$(CC) $(CFLAGS) $(FILE_INC_DIRS) -c $< -o $@ $(LIBS)

alx_getnum.o: $(GETN_DEPS)
	$(CC) $(CFLAGS) $(GETN_INC_DIRS) -c $< -o $@ $(LIBS)

alx_mask.o: $(MASK_DEPS)
	$(CC) $(CFLAGS) $(MASK_INC_DIRS) -c $< -o $@ $(LIBS)

alx_math.o: $(MATH_DEPS)
	$(CC) $(CFLAGS) $(MATH_INC_DIRS) -c $< -o $@ $(LIBS)

alx_ncur.o: $(NCUR_DEPS)
	$(CC) $(CFLAGS) $(NCUR_INC_DIRS) -c $< -o $@ $(LIBS)

alx_seed.o: $(SEED_DEPS)
	$(CC) $(CFLAGS) $(SEED_INC_DIRS) -c $< -o $@ $(LIBS)


clean:
	rm -f *.o
