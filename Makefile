Q ?= @
APP_INDEX ?= 0
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
LDFLAGS = -e _eadk_main -Wl,--gc-sections -lgcc -Wl,-T,eadk/eadk-nwa.ld -Wl,-Ur
LDFLAGS += --specs=nosys.specs -nostartfiles -lm

.PHONY: run
run: $(BUILD_DIR)/voord.elf $(BUILD_DIR)/device_information.ld
	@echo "RUN    $<"
	$(Q) python3 eadk/run.py $< --app-index $(APP_INDEX) --device-information $(filter-out $<,$^)

.PHONY: build
build: $(BUILD_DIR)/voord.nwa

$(BUILD_DIR)/voord.elf: $(BUILD_DIR)/voord.nwa $(call object_for,eadk/eadk.s) $(BUILD_DIR)/device_information.ld
	@echo "LD     $@"
	$(Q) arm-none-eabi-ld -T eadk/eadk-bin.ld $(filter-out %.ld,$^) -o $@

$(BUILD_DIR)/voord.nwa: $(call object_for,$(src)) $(BUILD_DIR)/icon.o
	@echo "LD     $@"
	$(Q) arm-none-eabi-gcc $(LDFLAGS) $(SFLAGS) $(filter-out %.ld,$^) -o $@

$(addprefix $(BUILD_DIR)/,%.o): %.cpp | $(BUILD_DIR)
	@echo "CXX    $^"
	$(Q) arm-none-eabi-g++ $(CPPFLAGS) $(SFLAGS) -c $^ -o $@

$(addprefix $(BUILD_DIR)/,%.o): %.s | $(BUILD_DIR)
	@echo "AS     $^"
	$(Q) arm-none-eabi-as $^ -o $@

# This recipe is needed to build the icon
$(addprefix $(BUILD_DIR)/,%.o): $(BUILD_DIR)/%.c
	@echo "CC     $^"
	$(Q) arm-none-eabi-gcc $(CFLAGS) $(SFLAGS) -c $^ -o $@

# This recipe is needed to get _eadk_start assembly
#start.o: eadk/start.c
#	arm-none-eabi-gcc -Os -Wall -MD -MP -ggdb3 -mthumb -mfloat-abi=hard -mcpu=cortex-m7  -mfloat-abi=hard -mfpu=fpv5-sp-d16 -fno-common -fdata-sections -ffunction-sections -fno-exceptions  -ffreestanding -c eadk/start.c

.PRECIOUS: $(BUILD_DIR)/icon.c
$(BUILD_DIR)/icon.c: src/icon.png | $(BUILD_DIR)
	@echo "INLINE $<"
	$(Q) python3 eadk/inliner.py $< $@

.PRECIOUS: $(BUILD_DIR)/device_information.ld
$(BUILD_DIR)/device_information.ld: | $(BUILD_DIR)
	@echo "EXTRACT LINKING INFO"
	$(Q) python3 eadk/get_device_information.py $@

.PRECIOUS: $(BUILD_DIR)
$(BUILD_DIR):
	$(Q) mkdir -p $@/src $@/eadk

.PHONY: clean
clean:
	@echo "CLEAN"
	$(Q) rm -rf $(BUILD_DIR)
