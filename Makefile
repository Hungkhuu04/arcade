# Compiler settings
CXX = g++


# Libraries
LIBS = -lGL -lGLU -lglut


# Source files
SRCS = Zombie/src/main.cpp Zombie/src/Renderer.cpp Zombie/src/GameController.cpp \
       Zombie/src/Player.cpp Zombie/src/Bullet.cpp Zombie/src/Zombie.cpp \
       Zombie/src/Utility.cpp Zombie/src/BossZombie.cpp Zombie/src/stb.cpp


# Object files
OBJS = $(SRCS:.cpp=.o)


# Executable name
EXEC = zombie_game


# Default target
all: $(EXEC)


# Linking the executable
$(EXEC): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(EXEC) $(OBJS) $(LIBS)


# Compiling each source file
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@


# Clean up
clean:
	rm -f $(OBJS) $(EXEC)


.PHONY: all clean
