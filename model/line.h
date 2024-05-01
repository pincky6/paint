#ifndef LINE_H
#define LINE_H

#include "abstractfigure.h"

namespace model::figures
{
    class Line: public AbstractFigure
    {
    public:
        Line();
        Line(const QPointF&, const QPointF&);
        virtual ~Line();
    };
}

#endif // LINE_H
