all: code

code: main.cpp
	g++ -O2 -std=gnu++17 -pipe -s -o code main.cpp

.PHONY: clean
clean:
	rm -f code
