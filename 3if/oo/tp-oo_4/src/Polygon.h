#ifndef POLYGON_H
#define POLYGON_H

#include <list>

#include "Figure.h"
#include "Vector2D.h"

class Polygon : public Figure
{
public:
    Polygon();

protected:
    virtual void addPoint(Vector2D point);
    virtual void serializePoints();

private:
    std::list<Vector2D> points;
};

#endif // POLYGON_H
