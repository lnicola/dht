CC = clang
CFLAGS = -DNDEBUG -O2 -mcpu=arm1176jzf-s -pipe -fvisibility=hidden -std=gnu99 -Wall
#CFLAGS = -ggdb -mcpu=arm1176jzf-s -pipe -std=c++11 -Wall
LDFLAGS = -lbcm2835

SRC = dht.c

all: dht

dht: $(SRC)
	        $(CC) -o $@ $(SRC) $(CFLAGS) $(LDFLAGS)

clean:
	        rm -f dht 