#Makefile for Harmony-pf Tests

INC = -I ../Source

executable: MapTests.o Map.o AStarTests.o AStar.o
	g++ -std=c++11 -o harmony-pf-test MapTests.o Map.o AStarTests.o AStar.o /usr/lib/libgtest.a /usr/lib/libgtest_main.a -lpthread

MapTests.o: MapTests.cpp ../Source/Map.h
	g++ $(INC) -std=c++11 -c MapTests.cpp

Map.o: ../Source/Map.cpp ../Source/Map.h
	g++ $(INC) -std=c++11 -c ../Source/Map.cpp

AStarTests.o: AStarTests.cpp ../Source/AStar.h
	g++ $(INC) -std=c++11 -c AStarTests.cpp

AStar.o: ../Source/AStar.cpp ../Source/AStar.h
	g++ $(INC) -std=c++11 -c ../Source/AStar.cpp

clean:
	rm -rf *o *~