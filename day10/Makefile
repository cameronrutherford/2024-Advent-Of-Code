CXX := g++
CXXFLAGS := -O0 -g -Wall -std=c++23

clean:
	rm -rf ./*.out

check: main.cpp
	@dos2unix $^ > /dev/null 2>&1
	@cppcheck --check-level=exhaustive --language=c++ --enable=style,warning $^

%.out: %.cpp
	@$(CXX) $(CXXFLAGS) $^ -o $@

main: main.out
	./$<

all: clean check main.out main
