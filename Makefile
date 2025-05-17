OBJS = rodcut.o piece_values.o vec.o cut_list.o cache.o
LIBS = random_replacement.so least_recently_used.so least_frequently_used.so

CC = gcc
CFLAGS = -Wall -fPIC
DLFLAGS = -ldl

.PHONY: all clean

all: rodcut_rr rodcut_lru rodcut_lfu $(LIBS)

rodcut_rr: $(OBJS)
	$(CC) -o $@ $(CFLAGS) $(OBJS) $(DLFLAGS)

rodcut_lru: $(OBJS)
	$(CC) -o $@ $(CFLAGS) $(OBJS) $(DLFLAGS)

rodcut_lfu: $(OBJS)
	$(CC) -o $@ $(CFLAGS) $(OBJS) $(DLFLAGS)

rodcut.o: rodcut.c piece_values.h cut_list.h vec.h cache.h
	$(CC) -c $(CFLAGS) rodcut.c

piece_values.o: piece_values.c piece_values.h
	$(CC) -c $(CFLAGS) piece_values.c

cut_list.o: cut_list.c cut_list.h vec.h piece_values.h
	$(CC) -c $(CFLAGS) cut_list.c

vec.o: vec.c vec.h
	$(CC) -c $(CFLAGS) vec.c

cache.o: cache.c cache.h
	$(CC) -c $(CFLAGS) cache.c

random_replacement.so: random_replacement.c cache.h
	$(CC) -shared $(CFLAGS) -o $@ $<

least_recently_used.so: least_recently_used.c cache.h
	$(CC) -shared $(CFLAGS) -o $@ $<

least_frequently_used.so: least_frequently_used.c cache.h
	$(CC) -shared $(CFLAGS) -o $@ $<

clean:
	rm -f rodcut_rr rodcut_lru $(OBJS) $(LIBS)
