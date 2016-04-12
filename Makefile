CFLAGS=-g -W -Wall -I ~/Documents/include/
LDFLAGS= -L ~/Documents/lib -lpipocom

main: main.o grille.o algo.o
	gcc -o main main.o grille.o algo.o $(LDFLAGS)

main.o: main.c grille.c grille.h algo.c algo.h
	gcc -o main.o -c main.c $(CFLAGS)
	
grille.o: grille.c grille.h
	gcc -o grille.o -c grille.c $(CFLAGS)
	
algo.o: algo.c algo.h
	gcc -o algo.o -c algo.c $(CFLAGS)
	
clean:
	rm -rf *.o
