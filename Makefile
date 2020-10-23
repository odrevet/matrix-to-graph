EXEC=target
CC=${TIGCC}/bin/tigcc
CFLAGS= -Wall -O2
CPPFLAGS= -DUSE_TI89 -DSAVE_SCREEN

TARGET := mtograph
SOURCEDIR := src
SOURCE := $(foreach DIR,$(SOURCEDIR)/TI,$(wildcard $(DIR)/*.c)) \
$(SOURCEDIR)/print.c \
$(SOURCEDIR)/graph.c \
$(SOURCEDIR)/matrix.c \
$(SOURCEDIR)/node.c \
$(SOURCEDIR)/print.c 

%.o: %.c
	$(CC) -o $@ -c $< $(CFLAGS)

all: $(EXEC)

target: $(OBJ)
	$(CC) $(SOURCE) -o $(TARGET) $^ $(CFLAGS) $(CPPFLAGS)

.PHONY: clean

clean:
	rm $(TARGET).89z