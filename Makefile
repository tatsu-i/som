CC = gcc
PROGRAM = main
PROGRAM_FILES = main.c som.c

CFLAGS	+= -g $(shell pkg-config --cflags --libs libglade-2.0 gmodule-2.0)
LDFLAGS	+= -g
LIBS 	= -lstdc++

all: $(PROGRAM)

%: %.c 
	$(CC) $(PROGRAM_FILES) $(CFLAGS) $(LDFLAGS) -o $(PROGRAM) $(LIBS)

run: $(PROGRAM)
	./$(PROGRAM)

clean:
	@rm -rf $(PROGRAM) tags
