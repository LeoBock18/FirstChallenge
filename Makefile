CXX ?= g++
CXXFLAGS ?= -std=c++20 -Wall
CPPFLAGS ?= -I. -I../pacs-examples/Examples/include
TARGET = main
SRCS = main.cpp gradmet.cpp
OBJS = $(SRCS:.cpp=.o)

.PHONY: all clean distclean

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(TARGET)

%.o: %.cpp
	$(CXX) $(CPPFLAGS)  $(CXXFLAGS) -c $< -o $@

clean:
	$(RM) *.o
distclean: clean
	$(RM) $(TARGET)
