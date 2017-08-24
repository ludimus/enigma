TARGETS = enigmaM3 encryptM3
CLASSES = rotor.o reflector.o plugboard.o
CPPFLAGS=-g -std=c++11

# Header file dependencies for classes
rotor.o : rotor.h
reflector.o : reflector.h
plugboard.o : plugboard.h

all : enigmaM3 encryptM3

encryptM3 : encryptm3.o $(CLASSES)
	g++ -g -o $@ $^

enigmaM3 : enigmam3.o $(CLASSES)
	g++ -g -o $@ $^

%.o : %.cpp
	g++ $(CPPFLAGS) -o $@ -c $<  

clean : 
	rm -f $(CLASSES) $(TARGETS)
