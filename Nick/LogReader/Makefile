all:
	g++  src/logReader.cpp src/utils/math/math.cpp src/utils/csvParser.cpp -I include/ -o logReader -std=c++11 -Wall -pg

debug:
	g++  src/logReader.cpp src/utils/math/math.cpp src/utils/csvParser.cpp -I include/ -o logReader -std=c++11 -DDEBUG -pg 

test:
	g++  src/logReader.cpp src/utils/math/math.cpp src/utils/csvParser.cpp -I include/ -o logReader -std=c++11 -DTEST -pg
	yes no | ./logReader.out

.PHONY: clean
clean:
	rm -f logReader
