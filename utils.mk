CC = g++
NAME = utils
OBJECTS = matrix.o
SOURCE = matrix.C
HEADERS = matrix.h

all: $(NAME).lib

$(NAME).lib: $(OBJECTS)
	ar ruvs $(NAME).lib $(OBJECTS)

$(OBJECTS): $(SOURCE) $(HEADERS)
	$(CC) -c $(SOURCE)

