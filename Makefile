CXX = clang++
SDL = -framework SDL2 -framework SDL2_image
# If your compiler is a bit older you may need to change -std=c++11 to -std=c++0x
CXXFLAGS = -F/Library/Frameworks -Wall -c -std=c++11
LDFLAGS = -v -F/Library/Frameworks $(SDL)
EXE = Castle_of_the_Winds-_Universal

.PHONY: clean all

all: $(EXE)

$(EXE): main.o
	$(CXX) $(LDFLAGS) bin/$< -o bin/$@

main.o: main.cpp
	$(CXX) $(CXXFLAGS) $< -o bin/$@

clean:
	$(RM) bin/*.o
	$(RM) bin/$(EXE)
