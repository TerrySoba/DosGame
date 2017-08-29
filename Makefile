OBJ = main.o image_utils.o mikmod_sound.o engine.o logging.o

CFLAGS = -Wall -O2  -I./3rd_party/mikmod/include -I./3rd_party/allegro/include
LDFLAGS = -L./3rd_party/allegro/lib -lalleg -L./3rd_party/mikmod/lib -lmikmod


all: gamec.exe

# compress executable
gamec.exe: game.exe $(OBJ)
	rm -f gamec.exe
	upx --lzma game.exe -o gamec.exe

game.exe: $(OBJ)
	g++ $(CFLAGS) -o game.exe $(OBJ) $(LDFLAGS)

%.o: %.cpp
	g++ $(CFLAGS) -c $<

clean:
	rm -f game.exe gamec.exe
	rm $(OBJ)
