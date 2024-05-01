#include "triangle.h"
#include "rectangle.h"

using namespace model::figures;
Triangle::Triangle(): Triangle(QPointF(0.0f, 0.0f),
                               QPointF(0.5f, 1.0f),
                               QPointF(1.0f, 0.0f))
{}
Triangle::Triangle(const QPointF& pointFirst,
                   const QPointF& pointSecond,
                   const QPointF& pointThird)
{
    vertices.push_back(pointFirst);
    vertices.push_back(pointSecond);
    vertices.push_back(pointThird);
}

Triangle::Triangle(const Rectangle& rectangle)
{
    const QVector<QPointF>& rectangleVertices = rectangle.getVertices();
    vertices.push_back(rectangleVertices[2]);
    vertices.push_back(rectangleVertices[3]);
    vertices.push_back(QPointF((rectangleVertices[1].x() + rectangleVertices[0].x())/2.0f,
                               rectangleVertices[1].y()));
}

