#include "drawablefigure.h"

#include <QPainter>

#include <QGraphicsScene>

using namespace view::drawable_figures;
using namespace model::figures;

DrawableFigure::DrawableFigure(AbstractFigure* abstractFigure,
                               FigureType type):
    figure(abstractFigure),
    figureType(type)
{}

DrawableFigure::DrawableFigure(std::shared_ptr<model::figures::AbstractFigure> abstractFigure,
                               model::figures::FigureType type):
    figure(abstractFigure),
    figureType(type)
{

}

void DrawableFigure::draw(QGraphicsScene* scene)
{
    if(figure.get() == nullptr) return;
    if(figure->getVertices().size() == 0) return;

    const QVector<QPointF>& vertices = figure->getVertices();
    std::size_t size = figure->getVertices().size();

    for(std::size_t i = 0; i <= size; i++)
    {
        scene->addLine(QLineF(vertices[i % size], vertices[(i + 1) % size]));
    }
}

std::shared_ptr<AbstractFigure>& DrawableFigure::getFigure()
{
    return figure;
}

FigureType DrawableFigure::getType()
{
    return figureType;
}

void DrawableFigure::setFigure(std::shared_ptr<AbstractFigure> newFigure)
{
    figure = newFigure;
}

void DrawableFigure::setType(FigureType newFigureType)
{
    figureType = newFigureType;
}
