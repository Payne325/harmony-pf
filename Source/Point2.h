#pragma once
#ifdef _WIN32
#  define MODULE_API __declspec(dllexport)
#else
#  define MODULE_API
#endif

MODULE_API struct Point2
{
public:

    Point2()
    {
        X = 0;
        Y = 0;
    }

    Point2(int x, int y)
    {
        X = x;
        Y = y;
    }

    bool operator== (const Point2& rhs) const
    {
        return
            this->X == rhs.X &&
            this->Y == rhs.Y;
    }
    int X;
    int Y;
};