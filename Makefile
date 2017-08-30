CC = g++
TARGETS = bin/m3menu bin/m3encrypt zygalski/zygalski
SRCDIR = src
BUILDDIR = build
INCDIR = include
CLASSES = build/enigmam3.o build/rotor.o build/reflector.o build/plugboard.o
CPPFLAGS =-g -std=c++11

all : $(TARGETS) 

bin/m3encrypt : $(BUILDDIR)/m3encrypt.o $(CLASSES)
	$(CC) -g -o $@ $^

bin/m3menu : $(BUILDDIR)/m3menu.o $(CLASSES)
	$(CC) -g -o $@ $^
    
zygalski/zygalski : $(BUILDDIR)/zygalski.o $(CLASSES)
	$(CC) -g -o $@ $^

$(BUILDDIR)/%.o : $(SRCDIR)/%.cpp
	$(CC) $(CPPFLAGS) -I $(INCDIR) -o $@ -c $<  
    
sheets : zygalski/zygalski 
	cd zygalski/;./makesheets.sh
    
clean : 
	rm -f $(BUILDDIR)/*.o $(TARGETS) zygalski/sheets/*

