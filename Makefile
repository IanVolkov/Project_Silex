# Makefile for Particle Simulation
# Optimized for Arch Linux (Endeavour OS)

CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O3 -march=native -mtune=native -flto
LIBS = -lSDL2 -lSDL2_ttf
TARGET = particle_simulation
SRC = main.cpp

# Debug build flags
DEBUG_FLAGS = -std=c++17 -Wall -Wextra -g -O0

.PHONY: all clean debug install uninstall

all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRC) $(LIBS)

debug:
	$(CXX) $(DEBUG_FLAGS) -o $(TARGET) $(SRC) $(LIBS)

clean:
	rm -f $(TARGET)

install: $(TARGET)
	install -Dm755 $(TARGET) /usr/local/bin/$(TARGET)
	install -Dm644 Parameters.txt /usr/local/share/particle_simulation/Parameters.txt

uninstall:
	rm -f /usr/local/bin/$(TARGET)
	rm -rf /usr/local/share/particle_simulation

run: $(TARGET)
	./$(TARGET)
