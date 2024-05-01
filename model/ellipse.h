#ifndef ELLIPSE_H
#define ELLIPSE_H

#include "abstractfigure.h"

namespace model::figures
{
    class Rectangle;

    class Ellipse: public AbstractFigure
    {
    public:
        Ellipse();
        Ellipse(const QPointF& centerPoint, float width, float height);
        Ellipse(const Rectangle&);
    private:
        QPointF pointCenter;
    };
}

#endif
