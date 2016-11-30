CC=g++
IDIR=include
CFLAGS=-I$(IDIR)
LIBS=-lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
DEPS = Bullet.h Enemy.h Shield.h CollisionBox.h UI.h Player.h Audio.h Laser.h Mouse.h G_Miscfuncandvar.h
OBJ = main.o Bullet.o Enemy.o Shield.o CollisionBox.o UI.o Player.o Audio.o Laser.o Mouse.o G_Miscfuncandvar.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

spaceyrocks: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)
	mv *.o obj

.PHONY: clean

clean:
	rm obj/*.o spaceyrocks
