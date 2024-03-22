CXX ?= g++
CXXFLAGS ?= -std=c++20
CPPFLAGS ?= -Wall -I. -I/../../../pacs-examples/Examples/include

LDLIBS ?= -/../../../pacs-examples/Examples/lib
LIBS ?= -lmuparser
TARGET = main

all: $(TARGET)

$(TARGET): %: %.o
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $< $(LIBS) -o $@

%.o: %.cpp
	$(CXX) -c $(CPPFLAGS)  $(CXXFLAGS) $<

clean:
	$(RM) *.o
distclean: clean
	$(RM) *~
