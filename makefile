CXX = clang++
SDL = -framework SDL2
# If your compiler is a bit older you may need to change -std=c++11 to -std=c++0x
CXXFLAGS = -F/Library/Frameworks -Wall -c -std=c++11
LDFLAGS = -F/Library/Frameworks $(SDL)
EXE = Castle_of_the_Winds-_Universal

all: $(EXE)

$(EXE): main.o
	$(CXX) $(LDFLAGS) $< -o bin/$@

main.o: main.cpp
	$(CXX) $(CXXFLAGS) $< -o $@

clean:
	rm *.o && rm $(EXE)
