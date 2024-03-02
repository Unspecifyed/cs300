CC = g++
CXXFLAGS = -std=c++11 -Wall
LDFLAGS =

# List all your source files here
SRCS := $(wildcard *.cpp)
HDRS := $(wildcard *.h)

# Derive object file names from source files
OBJS := $(SRCS:.cpp=.o)

# The target executable name
TARGET = Main

# Include directories containing header files
INC_DIRS =

# Libraries to link
LIBS =

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CXXFLAGS) $(INC_DIRS) -o $(TARGET) $(OBJS) $(LIBS) $(LDFLAGS)

# Compile each source file into its object file
%.o: %.cpp
	$(CC) $(CXXFLAGS) $(INC_DIRS) -c -o $@ $<

# Dependency generation
$(SRCS:.cpp=.d):%.d:%.cpp
	@set -e; rm -f $@; \
	$(CC) -MM $(CXXFLAGS) $< > $@.$$$$; \
	sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $@.$$$$ > $@; \
	rm -f $@.$$$$

-include $(SRCS:.cpp=.d)

clean:
	rm -f $(OBJS) $(TARGET) $(SRCS:.cpp=.d)

