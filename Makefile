OBJDIR = obj
CXX = clang++
CXXFLAGS ?= -std=c++17 -Wall -Wextra -O2 -g
LDFLAGS = 
SRC = $(wildcard *.cpp)
OBJ = $(SRC:%.cpp=$(OBJDIR)/%.o)
TARGET = main

all: $(OBJDIR) $(TARGET)

$(OBJDIR):
	mkdir -p $(OBJDIR)

$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

$(OBJDIR)/%.o: %.cpp | $(OBJDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJDIR) $(TARGET)

.PHONY: all clean