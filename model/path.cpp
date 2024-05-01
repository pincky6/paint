#include "path.h"

using namespace model::figures;

Path::Path(): Path(QPointF(0.0f, 0.0f),
                   QPointF(1.0f, 1.0f))
{}

Path::Path(const QPointF& point1,
           const QPointF& point2): Line(point1, point2)
{}

Path::Path(std::shared_ptr<AbstractFigure>& figure1,
           std::shared_ptr<AbstractFigure>& figure2):
    Line(figure1->getCenter(), figure2->getCenter())
{
    connectedFigures.push_back(figure1);
    connectedFigures.push_back(figure2);
}

QVector<std::shared_ptr<AbstractFigure>>& Path::getConnectedFigures()
{
    return connectedFigures;
}

const QVector<std::shared_ptr<AbstractFigure>>& Path::getConnectedFigures() const
{
    return connectedFigures;
}

void Path::popBackPoint()
{
    if(vertices.isEmpty())
    {
        return;
    }
    vertices.pop_back();
}

void Path::pushBackPoint(const QPointF& point)
{
    if(MAX_CONNECTED_FIGURES_COUNT < vertices.size())
    {
        return;
    }
    vertices.push_back(point);
}

void Path::popBackConnectedFigure()
{
    if(connectedFigures.isEmpty())
    {
        return;
    }
    connectedFigures.pop_back();
}

void Path::pushBackConnectedFigure(std::shared_ptr<AbstractFigure>& figure)
{
    if(MAX_CONNECTED_FIGURES_COUNT < connectedFigures.size())
    {
        return;
    }
    connectedFigures.push_back(figure);
    update();
}

bool Path::isEmpty() const
{
    return connectedFigures.isEmpty();
}

bool Path::isValid() const
{
    return std::any_of(connectedFigures.begin(), connectedFigures.end(), [](auto&& element){
        return (bool)element;
    });
}

bool Path::containsFigure(std::shared_ptr<AbstractFigure> searchFigure)
{
    auto res = std::find_if(connectedFigures.begin(), connectedFigures.end(), [&searchFigure](auto&& figure){
        return searchFigure.get() == figure.get();
    });
    return (res == connectedFigures.end()) ? false : true;
}

void Path::update()
{
    for(int i = 0; i < connectedFigures.size(); i++)
    {
        vertices[i] = connectedFigures[i]->getCenter();
    }
}
