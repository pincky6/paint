#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "abstractfigure.h"

namespace model::figures
{
    class Rectangle;

    class Triangle: public AbstractFigure
    {
    public:
        Triangle();
        Triangle(const QPointF&, const QPointF&, const QPointF&);
        Triangle(const Rectangle&);
    };
}

#endif
