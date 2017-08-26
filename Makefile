OBJ = main.o gm_state.o first_enemy.o image_utils.o mikmod_sound.o
CFLAGS = -Wall -O3 -fdata-sections -ffunction-sections -s -I./3rd_party/mikmod/include -I./3rd_party/allegro/include
LDFLAGS = -Wl,--gc-sections -s -L./3rd_party/allegro/lib -lalleg -L./3rd_party/mikmod/lib -lmikmod

all: gamec.exe

# compress executable
gamec.exe: game.exe
	rm gamec.exe
	upx game.exe -o gamec.exe

game.exe: $(OBJ)
	g++ $(CFLAGS) -o game.exe $(OBJ) $(LDFLAGS)

%.o: %.cpp
	g++ $(CFLAGS) -c $<

clean:
	rm game.exe gamec.exe
	rm $(OBJ)
