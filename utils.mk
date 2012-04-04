CC = g++
NAME = utils
OBJECTS = matrix.o misc.o boolean_matrix.o
SOURCE = matrix.C misc.C boolean_matrix.C
HEADERS = matrix.h misc.h boolean_matrix.h

all: $(NAME).lib

$(NAME).lib: $(OBJECTS)
	ar ruvs $(NAME).lib $(OBJECTS)

$(OBJECTS): $(SOURCE) $(HEADERS)
	$(CC) -c $(SOURCE)

