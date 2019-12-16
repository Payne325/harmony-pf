#pragma once
#ifdef _WIN32
#  define MODULE_API __declspec(dllexport)
#else
#  define MODULE_API
#endif

#include "Point2.h"

MODULE_API struct Node
{
    Point2 position;
    bool isObsticle;
    float cost;
    Node* parent;
};
