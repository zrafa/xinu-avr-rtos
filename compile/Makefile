PLATFORM	=	-Dlgt8f328p
F_CPU   = 4000000

#PLATFORM	=	-DATMEGA
#F_CPU   = 16000000

MCU     = atmega328p
AS      = avr-as
CC      = avr-gcc
LD      = avr-ld

TOPDIR		=	..
OBJDIR		=	binaries

CSOURCES = $(wildcard $(TOPDIR)/main/*.c) \
           $(wildcard $(TOPDIR)/lib/*.c) \
           $(wildcard $(TOPDIR)/system/*.c)

ASSOURCES = $(wildcard $(TOPDIR)/main/*.S) \
            $(wildcard $(TOPDIR)/lib/*.S) \
            $(wildcard $(TOPDIR)/system/*.S)
  
INCLUDES = -I$(TOPDIR)/include \
           -I$(TOPDIR)/main

# Extrae solo el nombre del archivo y lo redirige a OBJDIR
OBJECTS = $(addprefix $(OBJDIR)/, $(notdir $(CSOURCES:.c=.o) $(ASSOURCES:.S=.o)))

TARGET = xinu-avr-rtos

CFLAGS = -g -std=c99 -Wall -Os -mmcu=${MCU} -DF_CPU=${F_CPU} -fno-builtin -nostdlib -nostartfiles 

ASFLAGS = -g -mmcu=${MCU}

LDFLAGS = -mavr5 -T ld.script -Map=$(TARGET).map

$(TARGET) : $(OBJECTS)
	$(LD) -o $(TARGET).elf $^ $(LDFLAGS)
	avr-objcopy -j .text -j .data -O ihex $(TARGET).elf $(TARGET).hex
	avr-objcopy -O binary $(TARGET).elf $(TARGET).bin
	avr-size -C --mcu=${MCU} $(TARGET).elf

# Regla para compilar .c a obj/*.o
$(OBJDIR)/%.o: $(TOPDIR)/main/%.c | $(OBJDIR)
	${CC} ${CFLAGS} ${INCLUDES} -c $< -o $@

$(OBJDIR)/%.o: $(TOPDIR)/lib/%.c | $(OBJDIR)
	${CC} ${CFLAGS} ${INCLUDES} -c $< -o $@

$(OBJDIR)/%.o: $(TOPDIR)/system/%.c | $(OBJDIR)
	${CC} ${CFLAGS} ${INCLUDES} -c $< -o $@

# Regla para compilar .S a obj/*.o
$(OBJDIR)/%.o: $(TOPDIR)/main/%.S | $(OBJDIR)
	${CC} ${ASFLAGS} ${INCLUDES} -c $< -o $@

$(OBJDIR)/%.o: $(TOPDIR)/lib/%.S | $(OBJDIR)
	${CC} ${ASFLAGS} ${INCLUDES} -c $< -o $@

$(OBJDIR)/%.o: $(TOPDIR)/system/%.S | $(OBJDIR)
	${CC} ${ASFLAGS} ${INCLUDES} -c $< -o $@

# Crea la carpeta obj si no existe
$(OBJDIR):
	mkdir -p $(OBJDIR)

.PHONY: clean flash

clean:
	rm -rf $(OBJDIR) $(TARGET).elf $(TARGET).bin $(TARGET).hex $(TARGET).nm $(TARGET).map $(TARGET).asm core

flash: $(TARGET)
	avr-objcopy -O ihex -R .eeprom $(TARGET).elf $(TARGET).hex
	avrdude -p atmega328p -c arduino -P `ls -1 /dev/ttyUSB* /dev/ttyACM* 2>/dev/null | head -1` -b 115200 -D -U flash:w:$(TARGET).hex:i
