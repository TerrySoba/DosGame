
OBJ = main.o gm_state.o
CFLAGS = -Wall -O3 -pedantic -fdata-sections -ffunction-sections -s
LDFLAGS = -Wl,--gc-sections -s -lalleg

game.exe: $(OBJ)
	gcc $(CFLAGS) -o game.exe $(OBJ) $(LDFLAGS)

%.o: %.c
	gcc $(CFLAGS) -c $<

clean:
	rm game.exe
	rm $(OBJ)


