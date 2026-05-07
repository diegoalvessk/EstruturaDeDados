# Compilador e flags
CC = gcc
CFLAGS = -Wall -Wextra -Werror -std=c99 -g
TARGET = exe

# Arquivos objeto
OBJS = mochila.o pratica.o

# Alvo principal
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

# Regra para mochila.o
mochila.o: mochila.c mochila.h
	$(CC) $(CFLAGS) -c mochila.c

# Regra para pratica.o
pratica.o: pratica.c mochila.h
	$(CC) $(CFLAGS) -c pratica.c

# Limpeza
clean:
	rm -f $(OBJS) $(TARGET)

# Limpeza completa
purge: clean
	rm -f output.out

.PHONY: clean purge