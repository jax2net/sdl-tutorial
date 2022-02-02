CC=gcc
CFLAGS=-Wall -Werror
LDLIBS=-lSDL2 -lSDL2_image -lSDL2_ttf

texture:
	$(CC) $(CFLAGS) texture.c $(LDLIBS) -o texture

viewport:
	$(CC) $(CFLAGS) viewport.c $(LDLIBS) -o viewport

sprite_sheet:
	$(CC) $(CFLAGS) sprite_sheet.c $(LDLIBS) -o sprite_sheet

mouse:
	$(CC) $(CFLAGS) mouse.c $(LDLIBS) -o mouse

