#include "abstractfigure.h"

using namespace model::figures;

AbstractFigure::AbstractFigure()
{

}

AbstractFigure::~AbstractFigure()
{

}

QVector<QPointF>& AbstractFigure::getVertices()
{
    return vertices;
}

const QVector<QPointF>& AbstractFigure::getVertices() const
{
    return vertices;
}

AbstractFigure &AbstractFigure::operator+=(const QPointF& point)
{
    std::for_each(vertices.begin(), vertices.end(), [&point](auto&& vertex){
        vertex += point;
    });
    return *this;
}

bool AbstractFigure::containsPoint(const QPointF &point)
{
    bool inside = false;
    int size = vertices.size();
    for (int i = 0, j = size - 1; i < size; j = i++)
    {
        if (((vertices[i].y() > point.y()) != (vertices[j].y() > point.y())) &&
            (point.x() < (vertices[j].x() - vertices[i].x()) * (point.y() - vertices[i].y()) /
                                 (vertices[j].y() - vertices[i].y()) + vertices[i].x())
            )
        {
            inside = !inside;
        }
    }
    return inside;
}

QPointF AbstractFigure::getCenter()
{
    QPointF result = QPointF(0.0, 0.0);
    foreach (const QPointF& point, vertices)
    {
        result += point;
    }
    result /= vertices.size();
    return result;
}
