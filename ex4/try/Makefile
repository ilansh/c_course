HashInts: HashIntMain.c MyIntFunctions.o GenericHashTable.o
	gcc -Wall -g MyIntFunctions.o GenericHashTable.o TableErrorHandle.o HashIntMain.c -lm -o HashInts
MyIntFunctions.o: MyIntFunctions.c MyIntFunctions.h
	gcc -Wall -g -c MyIntFunctions.c
GenericHashTable.o: GenericHashTable.c GenericHashTable.h TableErrorHandle.o
	gcc -lm -Wall -g -c GenericHashTable.c
TableErrorHandle.o: TableErrorHandle.c TableErrorHandle.h
	gcc -Wall -g -c TableErrorHandle.c
clean:
	rm -f *.o *~ HashInt
