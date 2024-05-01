#include "viewmodel/paintviewlogic.h"

#include <QMouseEvent>
#include <QGraphicsScene>

#include "model/figuresenum.h"
#include "model/path.h"
#include "model/figurefactory.h"

#include "view/drawablefigure.h"
#include "view/paintview.h"

#include <algorithm>

using namespace view::drawable_figures;
using namespace view;

using namespace model::figures;
using namespace model::paint;


using namespace view_model::paint_view;

PaintViewLogic::PaintViewLogic():
    currentObject(nullptr)
{

}

void PaintViewLogic::setType(model::figures::FigureType figureType)
{
    type = figureType;
}

bool PaintViewLogic::currentObjectIsValid()
{
    return (bool)currentObject;
}

void PaintViewLogic::mousePressEvent(QMouseEvent* event)
{

}

void PaintViewLogic::drawFigures(QGraphicsScene* scene)
{
    if(scene == nullptr)
    {
        return;
    }
    scene->clear();
    if(currentObject)
    {
        currentObject->draw(scene);
    }
    std::for_each(figures.constBegin(), figures.constEnd(), [scene](auto&& figure){
        figure->draw(scene);
    });
    std::for_each(paths.constBegin(), paths.constEnd(), [scene](auto&& path){
        Path* pathPointer = dynamic_cast<Path*>(path->getFigure().get());
        pathPointer->update();
        path->draw(scene);
    });
}

void PaintViewLogic::createDrawableObject(view::PaintView* paintView,
                                           QMouseEvent* event)
{
    if(paintView == nullptr || event == nullptr)
    {
        return;
    }
    point = paintView->mapToScene(event->position().toPoint());
    currentObject.reset(new DrawableFigure(nullptr, type));
    if(type != FigureType::PATH)
    {
        currentObject->setFigure(FigureFactory::producePointerByRectangle(type, point, point));
        currentObject->setType(type);
    }
    else if(DrawableFigurePtr figure = figureContainCursor(paintView, event);
             (type == FigureType::PATH && figure != nullptr))
    {
        Path* path = new Path(figure->getFigure(), figure->getFigure());
        path->popBackConnectedFigure();
        currentObject->setFigure(std::shared_ptr<AbstractFigure>(path));
        currentObject->setType(type);
    }
}

void PaintViewLogic::updateFigures(view::PaintView* paintView, QGraphicsScene* scene, QMouseEvent* event)
{
    if(paintView == nullptr || scene == nullptr ||
        event == nullptr || !currentObjectIsValid())
    {
        return;
    }
    if(type != FigureType::PATH)
    {
        currentObject->setFigure(FigureFactory::producePointerByRectangle(type, point, paintView->mapToScene(event->position().toPoint())));
    }
    else if(!figures.isEmpty())
    {
        Path* path = dynamic_cast<Path*>(currentObject->getFigure().get());
        path->popBackPoint();
        path->pushBackPoint(paintView->mapToScene(event->position().toPoint()));
    }
    drawFigures(scene);
    paintView->viewport()->repaint();
}

void PaintViewLogic::addDrawableObject(view::PaintView* paintView, QGraphicsScene* scene,
                                       QMouseEvent* event)
{
    if(paintView == nullptr || scene == nullptr ||
        event == nullptr || !currentObjectIsValid())
    {
        return;
    }
    if(type != FigureType::PATH)
    {
        figures.push_front(currentObject);
    }
    else if(DrawableFigurePtr figure = figureContainCursor(paintView, event);
             (type == FigureType::PATH && figure != nullptr))
    {
        Path* path = dynamic_cast<Path*>(currentObject->getFigure().get());
        if(!path->containsFigure(figure->getFigure()))
        {
            path->pushBackConnectedFigure(figure->getFigure());
            paths.push_back(currentObject);
        }
    }
    currentObject = nullptr;
    drawFigures(scene);
    paintView->viewport()->repaint();
}

void PaintViewLogic::selectObject(view::PaintView* paintView, QMouseEvent* event)
{
    if(paintView == nullptr || event == nullptr)
    {
        return;
    }
    point = paintView->mapToScene(event->position().toPoint());
    currentObject = figureContainCursor(paintView, event);
}

void PaintViewLogic::releaseObject()
{
    currentObject = nullptr;
    point = QPointF(0.0f, 0.0f);
}

void PaintViewLogic::moveObject(PaintView* paintView, QGraphicsScene* scene, QMouseEvent* event)
{
    if(paintView == nullptr || scene == nullptr ||
        event == nullptr || !currentObjectIsValid())
    {
        return;
    }
    QPointF currentPoint = paintView->mapToScene(event->position().toPoint());
    QPointF delta = currentPoint - point;
    *currentObject->getFigure() += delta;
    drawFigures(scene);
    paintView->viewport()->repaint();
    point = currentPoint;
}


void PaintViewLogic::removeObject(PaintView* paintView,
                                  QGraphicsScene* scene,
                                  QMouseEvent* event)
{
    currentObject = figureContainCursor(paintView, event);
    paths.erase(std::remove_if(paths.begin(), paths.end(), [this](DrawableFigurePtr& figure){
                    Path* path = dynamic_cast<Path*>(figure->getFigure().get());
                    return path->containsFigure(currentObject->getFigure());
    }), paths.end());
    figures.erase(std::remove_if(figures.begin(), figures.end(), [&](DrawableFigurePtr& figure){
        return figure == currentObject;
    }), figures.end());
    currentObject = nullptr;
    drawFigures(scene);
    paintView->viewport()->repaint();
}

void PaintViewLogic::cancelCurrentObject(PaintView* paintView, QGraphicsScene* scene)
{
    if(paintView == nullptr || scene == nullptr)
    {
        return;
    }
    currentObject = nullptr;
    drawFigures(scene);
    paintView->viewport()->repaint();
    point = QPointF(0.0f, 0.0f);
}

DrawableFigurePtr PaintViewLogic::figureContainCursor(PaintView* paintView, QMouseEvent* event)
{
    if(paintView == nullptr || event == nullptr)
    {
        return nullptr;
    }
    auto result = std::find_if(figures.constBegin(), figures.constEnd(), [&](auto&& figure){
        return figure->getFigure()->containsPoint(paintView->mapToScene(event->position().toPoint()));
    });
    return (result != figures.cend()) ? *result : nullptr;
}

void PaintViewLogic::changeCursor(PaintView* paintView, QMouseEvent* event)
{
    if(paintView == nullptr || event == nullptr)
    {
        return;
    }
    if(figureContainCursor(paintView, event))
    {
        paintView->setCursor(Qt::PointingHandCursor);
    }
    else
    {
        paintView->setCursor(Qt::ArrowCursor);
    }
}

qint64 PaintViewLogic::indexOfFigures(const std::shared_ptr<model::figures::AbstractFigure>& figure)
{
    auto res = std::find_if(figures.begin(), figures.end(), [&figure](auto&& element){
        return element->getFigure() == figure;
    });
    return (res == figures.end()) ? -1: std::distance(figures.begin(), res);
}

void PaintViewLogic::serialize(QDataStream& stream)
{
    foreach (const DrawableFigurePtr& figure, figures) {
        stream << FigureType::toStringRepresentation(figure->getType());
        stream << figure->getFigure()->getVertices();
    }
    foreach (const DrawableFigurePtr& pathDrawable, paths) {
       const Path* path = dynamic_cast<const Path*>(pathDrawable->getFigure().get());
        stream << FigureType::toStringRepresentation(pathDrawable->getType());
        foreach (const auto& figure, path->getConnectedFigures()) {
            int index = indexOfFigures(figure);
            if(index != -1)
            {
                stream << index;
            }
        }
    }
}

void PaintViewLogic::deserialize(QDataStream& stream)
{
    while(!stream.atEnd())
    {
        QString figureTypeSerialized;
        stream >> figureTypeSerialized;
        FigureType figureType = FigureType::fromStringRepresentation(figureTypeSerialized);
        DrawableFigurePtr figure(new DrawableFigure(FigureFactory::produceByType(figureType),
                                                    figureType));
        if(figureType != FigureType::PATH)
        {
            stream >> figure->getFigure()->getVertices();
            figures.push_back(figure);
        }
        else
        {
            int indexFirstFigure, indexSecondFigure;
            stream >> indexFirstFigure >> indexSecondFigure;
            Path* path = dynamic_cast<Path*>(figure->getFigure().get());
            path->pushBackConnectedFigure(figures[indexFirstFigure]->getFigure());
            path->pushBackConnectedFigure(figures[indexSecondFigure]->getFigure());
            paths.push_back(figure);
        }
    }
}
