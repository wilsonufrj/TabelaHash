CXX = g++

CXXFLAGS = -std=c++17 -Wall -fpermissive -I.

SRCS = Registro.cpp \
	   TabelaHash.cpp \
	   main.cpp

OBJS = $(SRCS:.cpp=.o)

TARGET = main

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

%.o: %.cpp LinearDataStructure.hpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all clean
