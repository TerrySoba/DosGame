OBJ = main.o gm_state.o first_enemy.o image_utils.o
CFLAGS = -Wall -O3 -pedantic -fdata-sections -ffunction-sections -s
LDFLAGS = -Wl,--gc-sections -s -lalleg

game.exe: $(OBJ)
	g++ $(CFLAGS) -o game.exe $(OBJ) $(LDFLAGS)

%.o: %.cpp
	g++ $(CFLAGS) -c $<

clean:
	rm game.exe
	rm $(OBJ)
