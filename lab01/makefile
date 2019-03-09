SRCS := $(wildcard *.c)
OBJS := $(SRCS:.c=.o)

CC := gcc
CFLAGS := -std=c11 -Wall -pedantic -Wextra -Werror
LDFLAGS := -lm -lGL -lGLU -lglut

wm3dv: $(OBJS)
	$(CC) $^ -o $@.exec $(LDFLAGS)

%.o: %.c %.h
	$(CC) -c $< $(CFLAGS)

%.o: %.c
	$(CC) -c $< $(CFLAGS)

clean:
	rm -f *.o wm3dv 2>/dev/null
