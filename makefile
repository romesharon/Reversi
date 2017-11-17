#aviv shisman 206558157
a.out: compile
	g++ *.o 
	rm -f *.o

compile:*.h *.cpp
	g++ -c *.cpp
