TARGET = bst

$(TARGET) : tree.o test_tree.o
	g++ -g -std=c++11 tree.o test_tree.o -o $(TARGET)

tree.o : tree.cpp
	g++ -c -g -std=c++11 tree.cpp -o tree.o

test_tree.o : test_tree.cpp
	g++ -c -g -std=c++11 test_tree.cpp -o test_tree.o

do :
	./$(TARGET)

clean :
	rm *.o $(TARGET)

debug :
	gdb ./$(TARGET)
