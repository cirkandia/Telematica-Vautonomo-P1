# ========== Windows-only (VS Code PowerShell/cmd) ==========
SHELL := cmd
.SHELLFLAGS := /C

# Usa la ruta completa de gcc de MSYS2 para no depender del PATH
CC = C:/msys64/mingw64/bin/gcc.exe

SRC = src/server.c src/protocol.c src/telemetry.c src/utils.c
OUT_DIR = build
OUT = $(OUT_DIR)/server.exe

CFLAGS = -O2 -Wall -D_WIN32 -D_WIN32_WINNT=0x0601 -DWIN32_LEAN_AND_MEAN
LDLIBS = -lws2_32 -lwinpthread

.PHONY: all clean

all: $(OUT)

# Compila; depende de que exista build/ (order-only prerequisite con "|")
$(OUT): $(SRC) | $(OUT_DIR)
	$(CC) $(CFLAGS) $(SRC) -o $(OUT) $(LDLIBS)

# Crea la carpeta build/ sin mostrar banner de cmd
$(OUT_DIR):
	@if not exist "$(OUT_DIR)" mkdir "$(OUT_DIR)"

clean:
	@if exist "$(OUT_DIR)" rmdir /S /Q "$(OUT_DIR)"
