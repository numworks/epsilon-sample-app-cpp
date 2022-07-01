Q ?= @
BUILD_DIR = target

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

SFLAGS = -I. -Isrc -Os -Wall -MD -MP -ggdb3 -mthumb -mfloat-abi=hard -mcpu=cortex-m7  -mfloat-abi=hard -mfpu=fpv5-sp-d16
SFLAGS += -fno-common -fdata-sections -ffunction-sections -fno-exceptions
CPPFLAGS = -std=c++11 -ffreestanding -fno-rtti -nostdinc -nostdlib -fno-threadsafe-statics
LDFLAGS = -e _eadk_main -Wl,--gc-sections -lgcc -Wl,-T,eadk/eadk.ld -Wl,-Ur
LDFLAGS += --specs=nosys.specs -nostartfiles -lm

.PHONY: build
build: $(BUILD_DIR)/voord.nwa

.PHONY: run
run: $(BUILD_DIR)/voord.nwa
	@echo "INSTALL $<"
	$(Q) nwlink install-nwa $<

$(BUILD_DIR)/voord.nwa: $(call object_for,$(src)) $(BUILD_DIR)/icon.o
	@echo "LD      $@"
	$(Q) arm-none-eabi-gcc $(LDFLAGS) $(SFLAGS) $^ -o $@

$(addprefix $(BUILD_DIR)/,%.o): %.cpp | $(BUILD_DIR)
	@echo "CXX     $^"
	$(Q) arm-none-eabi-g++ $(CPPFLAGS) $(SFLAGS) -c $^ -o $@

$(BUILD_DIR)/icon.nwi: src/icon.png
	@echo "NWI     $<"
	$(Q) nwlink convert-nwi $< $@

$(BUILD_DIR)/icon.o: $(BUILD_DIR)/icon.nwi
	@echo "INLINE  $<"
	$(Q) arm-none-eabi-g++ -c -DFILE=$< -DSYMBOL=eadk_app_icon eadk/incbin.S -o $@

.PRECIOUS: $(BUILD_DIR)
$(BUILD_DIR):
	$(Q) mkdir -p $@/src $@/eadk

.PHONY: clean
clean:
	@echo "CLEAN"
	$(Q) rm -rf $(BUILD_DIR)
