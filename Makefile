CC=g++
iCFLAGS= 
LDFLAGS= 
EXECUTABLE=enigma_1

enigma1 : enigma1.o rotor.o reflector.o
	$(CC) $(LDFLAGS) -o enigma1 enigma1.o rotor.o reflector.o

enigma1.o : enigma1.cpp
	$(CC) $(CPPFLAGS) -c enigma1.cpp

rotor.o : rotor.h rotor.cpp
	$(CC) $(CPPFLAGS) -c rotor.cpp

reflector.o : reflector.h reflector.cpp
	$(CC) $(CPPFLAGS) -c reflector.cpp

clean :
	rm *.o


