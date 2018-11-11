//#pragma once
#include "AStar.h"
#include <gtest/gtest.h>

using namespace Algorithms;

char** ConstructMapWithNoObsticles(int size)
{
	char** map = new char*[size];

	for(int i = 0; i < size; ++i)
	{
		map[i] = new char[size];
	}

	for(int i = 0; i < size; ++i)
	{
		for(int j = 0; j < size; ++j)
		{
			map[i][j] = 'E';
		}
	}

	return map;
}

TEST(AStarSpecification, AStarIsConstructedWithMap)
{
	char** map = ConstructMapWithNoObsticles(32);
	Point2 startPosition(0, 0);
	Point2 endPosition(31, 31);

	IAlgorithm* pathFinder = new AStar(map, startPosition, endPosition);
	
	ASSERT_FALSE(pathFinder->MapContainsObsticles());
	ASSERT_TRUE(pathFinder->StartPosition() == startPosition);
	ASSERT_TRUE(pathFinder->EndPosition() == endPosition);

	delete pathFinder;

	for(int i = 0; i < 32; ++i)
	{
		delete map[i];
	}

	delete map;
}