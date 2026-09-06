CC ?= gcc
CFLAGS ?= -std=c11 -Wall -Wextra -pedantic
TARGET := data_structures_demo

SOURCES := src/assoc_list.c src/array_m2m_db.c src/avl_m2m_db.c src/hash_m2m_db.c examples/demo.c

.PHONY: all run clean

all: $(TARGET)

$(TARGET): $(SOURCES)
	$(CC) $(CFLAGS) $(SOURCES) -Isrc -o $(TARGET)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET)
