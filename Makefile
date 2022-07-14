Q ?= @
BUILD_DIR = target
NAME = voord

define object_for
$(addprefix $(BUILD_DIR)/,$(addsuffix .o,$(basename $(1))))
endef

src = $(addprefix src/,\
  alien.cpp \
  eadk.cpp \
  life.cpp \
  main.cpp \
  rocket.cpp \
  spaceship.cpp \
  score.cpp \
)

SFLAGS = -I. -Isrc -Os -Wall -MD -MP -ggdb3 -mthumb -mfloat-abi=hard -mcpu=cortex-m7 -mfloat-abi=hard -mfpu=fpv5-sp-d16
SFLAGS += -fno-common -fdata-sections -ffunction-sections -ffreestanding -nostdinc -nostdlib
CFLAGS = -std=c11
CXXFLAGS = -std=c++11 -fno-exceptions -fno-rtti -fno-threadsafe-statics
LDFLAGS = -Wl,-Ur
LDFLAGS += --specs=nosys.specs -nostartfiles
LDFLAGS_END = -lm

.PHONY: all
all: build

.PHONY: build
build: $(BUILD_DIR)/$(NAME).bin

.PHONY: run
run: $(BUILD_DIR)/$(NAME).nwa
	@echo "INSTALL $<"
	$(Q) nwlink install-nwa $<

$(BUILD_DIR)/%.bin: $(BUILD_DIR)/%.nwa
	@echo "BIN     $@"
	$(Q) nwlink link-nwa $< $@

$(BUILD_DIR)/$(NAME).nwa: $(call object_for,$(src)) $(BUILD_DIR)/icon.o
	@echo "LD      $@"
	$(Q) arm-none-eabi-gcc $(LDFLAGS) $(SFLAGS) $^ $(LDFLAGS_END) -o $@

$(addprefix $(BUILD_DIR)/,%.o): %.c | $(BUILD_DIR)
	@echo "C       $^"
	$(Q) arm-none-eabi-gcc $(CFLAGS) $(SFLAGS) -c $^ -o $@

$(addprefix $(BUILD_DIR)/,%.o): %.cpp | $(BUILD_DIR)
	@echo "CXX     $^"
	$(Q) arm-none-eabi-g++ $(CXXFLAGS) $(SFLAGS) -c $^ -o $@

$(BUILD_DIR)/icon.nwi: src/icon.png
	@echo "NWI     $<"
	$(Q) nwlink convert-nwi $< $@

$(BUILD_DIR)/icon.o: $(BUILD_DIR)/icon.nwi
	@echo "INLINE  $<"
	$(Q) arm-none-eabi-g++ -c -DFILE=$< -DSYMBOL=eadk_app_icon src/incbin.S -o $@

.PRECIOUS: $(BUILD_DIR)
$(BUILD_DIR):
	$(Q) mkdir -p $@/src

.PHONY: clean
clean:
	@echo "CLEAN"
	$(Q) rm -rf $(BUILD_DIR)
