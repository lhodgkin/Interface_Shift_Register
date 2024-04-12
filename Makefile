


file=Interface_SR

CC=avr-gcc 
cflags= -Os -DF_CPU=16000000UL -mmcu=atmega328p -o

push=avrdude
pushflags=-p m328p -c arduino -P/dev/cu.usbmodem1421 -C /Users/lukehodgkin1/avr/etc/avrdude.conf -e -U flash:w:

cpy=avr-objcopy
cpyflags=-j .text -j .data -O ihex






build: Interface_SR.o	
	$(cpy) $(cpyflags) $(file).o $(file).hex
#	avr-objcopy -j .text -j .data -O ihex source.o source.hex


Interface_SR.o : Interface_SR.c 
	$(CC) $(cflags) $(file).o $(file).c
#	avr-gcc -Os -DF_CPU=16000000UL -mmcu=atmega328p -o  source.o source.c

flash: Interface_SR.hex 
	$(push) $(pushflags)$(file).hex
#	avrdude -p m328p -c arduino -P/dev/cu.usbmodem1421 -C /Users/lukehodgkin1/avr/etc/avrdude.conf -e -U flash:w:source.hex
	
clean: 
	rm *.o 
	rm *.hex
