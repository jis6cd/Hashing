#Jessica Shaughnessy
#jis6cd
#10/15/2017
#Makefile
#lab section: 106 (3:30-4:45)


CXX = clang++ -O2 -std=c++11
OFILES = wordPuzzle.o timer.o hashTable.o
.SUFFIXES: .o .cpp


main:$(OFILES)
	$(CXX) $(OFILES)

clean:
	-rm -f *.o *~

#without -O2 flag runtime for "words.txt 4x7.grid.txt" : .287481 sec
#with -O2 flag runtime for "words.txt 4x7.grid.txt": .283522 sec
