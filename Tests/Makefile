# all: 
# 	g++ -c AStarTests.cpp
# 	g++ -c AStar.cpp

# 	g++ -o harmony-pf-test AStarTests.o AStar.o /usr/lib/libgtest.a /usr/lib/libgtest_main.a -lpthread

# clean:
# 	rm -rf *o *~

#Makefile for AStarTests

INC = -I ../Source

executable: AStarTests.o AStar.o
	g++ -o harmony-pf-test AStarTests.o AStar.o /usr/lib/libgtest.a /usr/lib/libgtest_main.a -lpthread

AStarTests.o: AStarTests.cpp ../Source/AStar.h
	g++ $(INC) -c AStarTests.cpp

AStar.o: ../Source/AStar.cpp ../Source/AStar.h
	g++ $(INC) -c ../Source/AStar.cpp

clean:
	rm -rf *o *~