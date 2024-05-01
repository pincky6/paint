#ifndef FIGUREFACTORY_H
#define FIGUREFACTORY_H

#include <memory>

class QPointF;

namespace model::figures
{
    class AbstractFigure;
    struct FigureType;

    class FigureFactory
    {
    public:
        static std::shared_ptr<AbstractFigure> producePointerByRectangle(FigureType type,
                                                                                  const QPointF& point1, const QPointF& point2);
        static std::shared_ptr<AbstractFigure> produceByType(FigureType type);
    };
}

#endif // FIGUREFACTORY_H
