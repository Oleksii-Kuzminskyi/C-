TARGET = dll

SRC_DIR = ./source/src/
INC_DIR = ./source/inc/
OBJ_DIR = ./build/obj/

SRCMODULES = $(wildcard $(SRC_DIR)*.cpp)
OBJMODULES = $(patsubst $(SRC_DIR)%.cpp, $(OBJ_DIR)%.o, $(SRCMODULES))

CXXFLAGS = -g -Wall -std=c++11 -I $(INC_DIR)
CC = g++


$(OBJ_DIR)%.o: $(SRC_DIR)%.cpp
	$(CC) $(CXXFLAGS) -c $< -o $@

$(TARGET): $(OBJMODULES)
	$(CC) $(CXXFLAGS) $(OBJMODULES) -o $@

do:
	./$(TARGET)

clean:
	rm $(OBJ_DIR)*.o $(TARGET)

debug:
	gdb ./$(TARGET)
