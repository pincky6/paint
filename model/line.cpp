#include "line.h"

using namespace model::figures;

Line::Line(): Line(QPointF(0.0f, 0.0f),
                   QPointF(1.0f, 1.0f))
{

}

Line::Line(const QPointF& point1, const QPointF& point2)
{
    vertices.push_back(point1);
    vertices.push_back(point2);
}

Line::~Line()
{

}
