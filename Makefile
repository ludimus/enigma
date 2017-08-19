CC=g++
CPPFLAGS=
LDFLAGS=
OBJ = enigmam3.o rotor.o reflector.o
enigma3 : $(OBJ)     
	$(CC) -o enigmam3 $(OBJ) 

enigmam3.o : enigmam3.cpp
	$(CC) $(CPPFLAGS) -c enigmam3.cpp

rotor.o : rotor.h rotor.cpp
	$(CC) $(CPPFLAGS) -c rotor.cpp

reflector.o : reflector.h reflector.cpp
	$(CC) $(CPPFLAGS) -c reflector.cpp

clean :
	rm *.o


