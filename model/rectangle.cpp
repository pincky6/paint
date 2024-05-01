#include "rectangle.h"

using namespace model::figures;

Rectangle::Rectangle(): Rectangle(QPointF(0.0f, 0.0f), QPointF(1.0f, 1.0f))
{

}

Rectangle::Rectangle(const QPointF& firstPoint, const QPointF& secondPoint)
{
    qreal left = qMin(firstPoint.x(), secondPoint.x());
    qreal right = qMax(firstPoint.x(), secondPoint.x());
    qreal bottom = qMin(firstPoint.y(), secondPoint.y());
    qreal top = qMax(firstPoint.y(), secondPoint.y());

    vertices.push_back(QPointF(left, bottom));
    vertices.push_back(QPointF(right, bottom));
    vertices.push_back(QPointF(right, top));
    vertices.push_back(QPointF(left, top));
}

qreal Rectangle::getHeight()
{
    return vertices[2].y() - vertices[0].y();
}

qreal Rectangle::getHeight() const
{
    return vertices[2].y() - vertices[0].y();
}

qreal Rectangle::getWidth()
{
    return vertices[1].x() - vertices[0].x();
}


qreal Rectangle::getWidth() const
{
    return vertices[1].x() - vertices[0].x();
}
