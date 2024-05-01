#include "figurefactory.h"

#include "figuresenum.h"

#include "rectangle.h"
#include "triangle.h"
#include "ellipse.h"
#include "path.h"

using namespace model::figures;

std::shared_ptr<AbstractFigure> FigureFactory::producePointerByRectangle(FigureType type,
                                                                  const QPointF &point1, const QPointF &point2)
{
    AbstractFigure* figure = nullptr;
    switch(type)
    {
    case FigureType::RECTANGLE:
        figure = new Rectangle(point1, point2);
        break;
    case FigureType::TRIANGLE:
        figure = new Triangle(Rectangle(point1, point2));
        break;
    case FigureType::ELLIPSE:
        figure = new Ellipse(Rectangle(point1, point2));
        break;
    case FigureType::PATH:
        figure = new Path(point1, point2);
        break;
    default:
        figure = new AbstractFigure();
    }
    return std::shared_ptr<AbstractFigure>(figure);
}

std::shared_ptr<AbstractFigure> FigureFactory::produceByType(FigureType type)
{
    AbstractFigure* figure = nullptr;
    switch(type)
    {
    case FigureType::RECTANGLE:
        figure = new Rectangle();
        break;
    case FigureType::TRIANGLE:
        figure = new Triangle(Rectangle());
        break;
    case FigureType::ELLIPSE:
        figure = new Ellipse(Rectangle());
        break;
    case FigureType::PATH:
        figure = new Path();
        break;
    default:
        figure = new AbstractFigure();
    }
    return std::shared_ptr<AbstractFigure>(figure);
}
