EXE = test
CC = g++

$(EXE).exe: $(EXE).cpp utils.lib 
	$(CC) -g $(EXE).cpp utils.lib -o $(EXE).exe

clean: FRC
	rm -f *.o *.lib *.stackdump *~ \#*\#

FRC:

include utils.mk
