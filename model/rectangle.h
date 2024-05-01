#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "abstractfigure.h"

namespace model::figures
{
    class Rectangle: public AbstractFigure
    {
    public:
        Rectangle();
        Rectangle(const QPointF&, const QPointF&);
        qreal getHeight();
        qreal getHeight() const;

        qreal getWidth();
        qreal getWidth() const;
    };
}

#endif
