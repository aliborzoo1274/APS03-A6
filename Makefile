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
EXECUTABLE = utms.exe

# specify the source files
SRCS = $(wildcard $(SRCDIR)/*.cpp)

# specify the object files
OBJS = $(patsubst $(SRCDIR)/%.cpp, $(BUILDDIR)/%.o, $(SRCS))

# specify the include files
INCLUDES = $(wildcard $(INCLUDEDIR)/*.hpp)

# default rule
all: $(EXECUTABLE)

directories:
	if not exist $(BUILDDIR) mkdir $(BUILDDIR)
	if not exist $(SRCDIR) mkdir $(SRCDIR)
	if not exist $(INCLUDEDIR) mkdir $(INCLUDEDIR)

# rule to link the program
$(EXECUTABLE): $(OBJS)
	$(CXX) $(CXXFLAGS) -I$(INCLUDEDIR) -o $(EXECUTABLE) $^

# rule to compile the program
$(BUILDDIR)/%.o: $(SRCDIR)/%.cpp $(INCLUDES) | directories
	$(CXX) $(CXXFLAGS) -I$(INCLUDEDIR) -c $< -o $@

# rule to clean the build files
clean:
	rm -f $(BUILDDIR)/*.o $(EXECUTABLE)