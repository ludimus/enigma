CC = g++
TARGETS = bin/enigmaM3 bin/encryptM3
SRCDIR = src
BUILDDIR = build
INCDIR = include
CLASSES = build/rotor.o build/reflector.o build/plugboard.o
CPPFLAGS=-g -std=c++11

# Header file dependencies for classes
#rotor.o : include/rotor.h
#reflector.o : include/reflector.h
#plugboard.o : include/plugboard.h

all : $(TARGETS)

bin/encryptM3 : $(BUILDDIR)/encryptm3.o $(CLASSES)
	$(CC) -g -o $@ $^

bin/enigmaM3 : $(BUILDDIR)/enigmam3.o $(CLASSES)
	$(CC) -g -o $@ $^

$(BUILDDIR)/%.o : $(SRCDIR)/%.cpp
	$(CC) $(CPPFLAGS) -I $(INCDIR) -o $@ -c $<  

clean : 
	rm -f $(BUILDDIR)/* $(TARGETS)
