OBJS = rodcut.o piece_values.o vec.o cut_list.o cache.o
LIBS = random_replacement.so

all: rodcut $(LIBS)

CC = gcc
CFLAGS = -Wall

rodcut: $(OBJS)
	gcc -o rodcut $(CFLAGS) $(OBJS) -ldl

rodcut.o: rodcut.c piece_values.h cut_list.h vec.h cache.h

piece_values.o: piece_values.c piece_values.h

cut_list.o: cut_list.c cut_list.h vec.h piece_values.h

vec.o: vec.c vec.h

cache.o: cache.c cache.h

random_replacement.so: random_replacement.c cache.h
	$(CC) -fPIC -shared -o random_replacement.so random_replacement.c

clean:
	rm -f rodcut random_replacement.so $(OBJS)
