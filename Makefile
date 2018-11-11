all: 
	g++ -c AStarTests.cpp
	g++ -c AStar.cpp

	g++ -o harmony-pf-test AStarTests.o AStar.o /usr/lib/libgtest.a /usr/lib/libgtest_main.a -lpthread

clean:
	rm -rf *o *~
