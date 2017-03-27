CC= colorgcc
CFLAGS = -g -O2 -Wall -ansi
LDFLAGS = -lMLV -lm
PATH_BIN = ./bin
PATH_SRC = ./src
PATH_INC = ./include

all :
	make shoot
	

shoot : $(PATH_BIN)/main.o  $(PATH_BIN)/player.o  $(PATH_BIN)/bullet.o  $(PATH_BIN)/vector.o  $(PATH_BIN)/cercle.o  $(PATH_BIN)/bonus.o  $(PATH_BIN)/bonuses.o  $(PATH_BIN)/input.o  $(PATH_BIN)/display.o  $(PATH_BIN)/enemies.o  $(PATH_BIN)/enemy.o  $(PATH_BIN)/collision.o  $(PATH_BIN)/animation.o  $(PATH_BIN)/animations.o  $(PATH_BIN)/score.o
	mv *.o $(PATH_BIN)/
	$(CC) -o $@ $^ $(LDFLAGS)

$(PATH_BIN)/main.o : $(PATH_SRC)/main.c $(PATH_INC)/input.h $(PATH_INC)/score.h
	$(CC) -c $< $(CFLAGS)

$(PATH_BIN)/player.o : $(PATH_SRC)/player.c $(PATH_INC)/player.h $(PATH_INC)/bullet.h
	$(CC) -c $< $(CFLAGS) 

$(PATH_BIN)/bullet.o : $(PATH_SRC)/bullet.c $(PATH_INC)/bullet.h $(PATH_INC)/cercle.h 
	$(CC) -c $< $(CFLAGS)

$(PATH_BIN)/input.o : $(PATH_SRC)/input.c $(PATH_INC)/input.h $(PATH_INC)/player.h
	$(CC) -c $< $(CFLAGS) 

$(PATH_BIN)/vector.o : $(PATH_SRC)/vector.c $(PATH_INC)/vector.h $(PATH_INC)/const.h
	$(CC) -c $< $(CFLAGS) 

$(PATH_BIN)/cercle.o : $(PATH_SRC)/cercle.c $(PATH_INC)/cercle.h $(PATH_INC)/vector.h
	$(CC) -c $< $(CFLAGS) 

$(PATH_BIN)/display.o : $(PATH_SRC)/display.c $(PATH_INC)/display.h $(PATH_INC)/collision.h
	$(CC) -c $< $(CFLAGS)

$(PATH_BIN)/enemies.o : $(PATH_SRC)/enemies.c $(PATH_INC)/enemies.h $(PATH_INC)/enemy.h $(PATH_INC)/player.h
	$(CC) -c $< $(CFLAGS)

$(PATH_BIN)/enemy.o : $(PATH_SRC)/enemy.c $(PATH_INC)/enemy.h $(PATH_INC)/cercle.h
	$(CC) -c $< $(CFLAGS)

$(PATH_BIN)/collision.o : $(PATH_SRC)/collision.c $(PATH_INC)/collision.h $(PATH_INC)/bonuses.h $(PATH_INC)/animations.h
	$(CC) -c $< $(CFLAGS)

$(PATH_BIN)/bonuses.o : $(PATH_SRC)/bonuses.c $(PATH_INC)/bonuses.h $(PATH_INC)/bonus.h
	$(CC) -c $< $(CFLAGS)

$(PATH_BIN)/bonus.o : $(PATH_SRC)/bonus.c $(PATH_INC)/bonus.h $(PATH_INC)/enemies.h
	$(CC) -c $< $(CFLAGS)

$(PATH_BIN)/animations.o : $(PATH_SRC)/animations.c $(PATH_INC)/animations.h $(PATH_INC)/animation.h
	$(CC) -c $< $(CFLAGS)

$(PATH_BIN)/animation.o : $(PATH_SRC)/animation.c $(PATH_INC)/animation.h 
	$(CC) -c $< $(CFLAGS)

$(PATH_BIN)/score.o : $(PATH_SRC)/score.c $(PATH_INC)/score.h $(PATH_INC)/display.h
	$(CC) -c $< $(CFLAGS)


clean : 
	rm $(PATH_BIN)/*.o
	rm -f shoot



