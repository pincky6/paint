#ifndef PATH_H
#define PATH_H

#include "line.h"

namespace model::figures
{
    class Path : public model::figures::Line
    {
        static constexpr int MAX_CONNECTED_FIGURES_COUNT = 2;
    public:
        Path();
        Path(const QPointF&, const QPointF&);
        Path(std::shared_ptr<AbstractFigure>&, std::shared_ptr<AbstractFigure>&);

        QVector<std::shared_ptr<AbstractFigure>>& getConnectedFigures();
        const QVector<std::shared_ptr<AbstractFigure>>& getConnectedFigures() const;

        void popBackPoint();
        void pushBackPoint(const QPointF&);

        void popBackConnectedFigure();
        void pushBackConnectedFigure(std::shared_ptr<AbstractFigure>&);

        bool isEmpty() const;
        bool isValid() const;
        bool containsFigure(std::shared_ptr<AbstractFigure>);

        void update();
    private:
        QVector<std::shared_ptr<AbstractFigure>> connectedFigures;
    };
}
#endif // PATH_H
