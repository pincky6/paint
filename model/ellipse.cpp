#include "ellipse.h"
#include "rectangle.h"

using namespace model::figures;

Ellipse::Ellipse(): Ellipse(QPointF(0.0f, 0.0f), 1, 1)
{

}

Ellipse::Ellipse(const QPointF &pointCenter, float width, float height)
{
    qreal numPoints = width + height;
    for (int i = 0; i < numPoints; i++)
    {
        qreal theta = 2.0 * M_PI * (float)i / numPoints;
        qreal x = width / 2.0 * cos(theta) + pointCenter.x();
        qreal y = height / 2.0 * sin(theta) + pointCenter.y();
        vertices.push_back(QPointF(x, y));
    }
}

Ellipse::Ellipse(const Rectangle& rectangle):
    Ellipse(QPointF((rectangle.getVertices()[1].x() + rectangle.getVertices()[0].x()) / 2.0f,
                    (rectangle.getVertices()[3].y() + rectangle.getVertices()[1].y()) / 2.0f),
                    rectangle.getWidth(),
                    rectangle.getHeight())
{
}
