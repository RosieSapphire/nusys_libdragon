GAME=nu1
CFLAGS=-Wall -Wextra -Iinclude -Ofast
BUILD_DIR=build
include $(N64_INST)/include/n64.mk

src = $(wildcard src/*.c src/*/*.c)

all: $(GAME).z64

$(BUILD_DIR)/$(GAME).elf: $(src:%.c=$(BUILD_DIR)/%.o)

$(GAME).z64: N64_ROM_TITLE="$(GAME)"

clean:
	rm -rf $(BUILD_DIR) $(GAME).z64

-include $(wildcard $(BUILD_DIR)/*.d)

BETTY_SCAN=include/*.h src/*.c

betty-style:
	betty-style --allow-global-variables $(BETTY_SCAN)

betty-doc:
	betty-doc $(BETTY_SCAN)

betty:
	clear; make betty-doc; make betty-style;

.PHONY: all clean
