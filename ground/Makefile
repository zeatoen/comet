CXX = g++
CXXFLAGS = -std=c++20 -fmodules

# Objects
OBJS =  command_sanitisation.o main.o

# Final executable
all: app

app: $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Compile module interfaces into BMIs and objects

command_sanitisation.o: command_sanitisation.cppm 
	$(CXX) $(CXXFLAGS) -c $< -o $@

main.o: main.cpp  command_sanitisation.o
	C -c $< -o $@

external:
	 $(CXX) $(CXXFLAGS)  -fmodules -xc++-system-header \
		vector cstdlib filesystem iostream \
				 string cstring
# Cleanup
clean:
	rm -f *.o  app

