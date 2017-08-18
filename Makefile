CC=g++
iCFLAGS=-I ./inc
LDFLAGS= 
OBJECTS= enigma
EXECUTABLE=enigma_1

enigma1 : enigma1.o rotor.o
	$(CC) $(LDFLAGS) -o enigma1 enigma1.o rotor.o

enigma1.o :
	$(CC) $(CPPFLAGS) -c enigma1.cpp

rotor.o : rotor.h
	$(CC) $(CPPFLAGS) -c rotor.cpp

clean :
	rm *.o


