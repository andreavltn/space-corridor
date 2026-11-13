CFLAGS = -O3 `sdl2-config --cflags`
LDFLAGS = `sdl2-config --libs` -lSDL2_ttf -lm

INC = sdl2-light.h sdl2-ttf-light.h constantes.h affichage.h logique.h
SRC = main.c sdl2-light.c sdl2-ttf-light.c affichage.c logique.c
OBJ = $(SRC:%.c=%.o)

PROG = spacecorridor

%.o: %.c $(INC)
	gcc $(CFLAGS) -c $<

spacecorridor: $(OBJ)
	gcc $(CFLAGS) $(OBJ) $(LDFLAGS) -o $@

clean:
	rm -f *~ *.o $(PROG)

