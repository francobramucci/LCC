
CC = gcc
CFLAGS = -O2 -Wall
SRC_DIR = src/c/
BUILD_DIR = build/

$(BUILD_DIR)main: $(SRC_DIR)main.c $(BUILD_DIR)generacion.o $(BUILD_DIR)utils.o | $(BUILD_DIR)
	$(CC) $(CFLAGS) -o $@ $(SRC_DIR)main.c $(BUILD_DIR)generacion.o $(BUILD_DIR)utils.o
$(BUILD_DIR)generacion.o: $(SRC_DIR)generacion.c $(SRC_DIR)generacion.h | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@
$(BUILD_DIR)utils.o: $(SRC_DIR)utils.c $(SRC_DIR)utils.h | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

.PHONY: clean
clean:
	rm -rf $(BUILD_DIR)

