LINK_TARGET = enigmaM3
OBJS =  enigmam3.o rotor.o reflector.o plugboard.o
REBUILDABLES = $(OBJS) $(LINK_TARGET)
CPPFLAGS=-g -std=c++11

# Header file dependencies
rotor.o : rotor.h
reflector.o : reflector.h
plugboard.o : plugboard.h

# The rule for "all" is used to incrementally build your system.
# It does this by expressing a dependency on the results of that system,
# which in turn have their own rules and dependencies.

all : $(LINK_TARGET)

# Here is a Rule that uses some built-in Make Macros in its command:
# $@ expands to the rule's target, in this case "test_me.exe".
# $^ expands to the rule's dependencies, in this case the three files
# main.o, test1.o, and  test2.o.

$(LINK_TARGET) : $(OBJS)
	g++ -g -o $@ $^

# Here is a Pattern Rule, often used for compile-line.
# It says how to create a file with a .o suffix, given a file with a .cpp suffix.
# The rule's command uses some built-in Make Macros:
# $@ for the pattern-matched target
# $< for the pattern-matched dependency

%.o : %.cpp
	g++ $(CPPFLAGS) -o $@ -c $<  
  
# Here is a simple Rule (used for "cleaning" your build environment).
# It has a Target named "clean" (left of the colon ":" on the first line),
# no Dependencies (right of the colon),
# and two Commands (indented by tabs on the lines that follow).
# The space before the colon is not required but added here for clarity.

clean : 
	rm -f $(REBUILDABLES)
