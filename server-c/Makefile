CC=gcc
CFLAGS=-O2 -Wall -pthread
SRC=src/server.c src/protocol.c src/telemetry.c src/utils.c
OUT=build/server

ifeq ($(OS),Windows_NT)
  LDLIBS += -lws2_32
endif

all: $(OUT)

$(OUT): $(SRC)
	@mkdir -p build
	$(CC) $(CFLAGS) $(SRC) -o $(OUT) $(LDLIBS)

clean:
	rm -rf build
