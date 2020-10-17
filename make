EXEC=target
CC=$TIGCC/bin/tigcc
CFLAGS= -Wall -std=c99

TARGET := mtograph
SOURCEDIR := src
SOURCE := $(foreach DIR,$(SOURCEDIR),$(wildcard $(DIR)/*.c))

%.o: %.c
	$(CC) -o $@ -c $< $(CFLAGS)

all: $(EXEC)

target: $(OBJ)
	$(CC) $(SOURCE) -o $(TARGET) $^ $(CFLAGS) $(CPPFLAGS)

.PHONY: clean

clean:
	rm $(TARGET)