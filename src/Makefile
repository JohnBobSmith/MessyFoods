CC=g++
IDIR=include
CFLAGS=-I$(IDIR)
LIBS=-lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
DEPS = Bullet.h Enemy.h Shield.h CollisionBox.h UI.h Player.h
OBJ = main.o Bullet.o Enemy.o Shield.o CollisionBox.o UI.o Player.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

spaceyrocks: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)
	mv *.o obj

.PHONY: clean

clean:
	rm obj/*.o spaceyrocks
