
OBJ = main.o
CFLAGS = -Wall -Os -pedantic -fdata-sections -ffunction-sections -s
LDFLAGS = -Wl,--gc-sections -s -lalleg

game.exe: $(OBJ)
	gcc $(CFLAGS) -o game.exe $(OBJ) $(LDFLAGS)

%.o: %.c
	gcc $(CFLAGS) -c $<

clean:
	del game.exe
	del $(OBJ)


