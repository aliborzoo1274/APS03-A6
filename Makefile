# specify the compiler
CXX = g++

# specify compiler flags
CXXFLAGS = -Wall -std=c++17

# specify the build directory
BUILDDIR = build

# specify the source directory
SRCDIR = src

# specify the include directory
INCLUDEDIR = include

# specify the executable file
EXECUTABLE = UTms.exe

# specify the source files
SRCS = $(wildcard $(SRCDIR)/*.cpp)

# specify the object files
OBJS = $(patsubst $(SRCDIR)/%cpp, $(BUILDDIR)/%o, $(SRCS))

# specify the include files
INCLUDES = $(wildcard $(INCLUDEDIR)/*.hpp)

# default rule
all: directories $(EXECUTABLE)

directories:
	mkdir $(BUILDDIR)

# rule to link the program
$(EXECUTABLE): $(OBJS)
	$(CXX) $(CXXFLAGS) -I$(INCLUDEDIR) -o $(EXECUTABLE) $^

# rule to compile the program
$(BUILDDIR)/%o: $(SRCDIR)/%cpp $(INCLUDES)
	$(CXX) $(CXXFLAGS) -I$(INCLUDEDIR) -c $< -o $@

# rule to clean the build files
clean:
	rm -f $(BUILDDIR)/*.o $(EXECUTABLE)