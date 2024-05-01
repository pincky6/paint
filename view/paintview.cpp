#include "paintview.h"

#include <QWidget>

#include <QPainter>
#include <QPen>
#include <QRadialGradient>

#include <QMouseEvent>
#include <QKeyEvent>

#include "model/paintstate.h"

using namespace view::drawable_figures;
using namespace view;

using namespace model::figures;
using namespace model::paint;

PaintView::PaintView(QWidget *parent):
    QGraphicsView(parent), state(PaintState::NOTHING)
{
    scene = new QGraphicsScene();
    scene->setSceneRect(0, 0, width(), height());
    setMouseTracking(true);
    this->setScene(scene);
}

void PaintView::mousePressEvent(QMouseEvent *event)
{
    qDebug() << "PRESS";
    if(event->button() == Qt::RightButton && logic.currentObjectIsValid())
    {
        logic.cancelCurrentObject(this, scene);
        return;
    }
    switch(state)
    {
    case PaintState::DRAW:
        logic.createDrawableObject(this, event);
        break;
    case PaintState::MOVE:
        logic.changeCursor(this, event);
        logic.selectObject(this, event);
        break;
    case PaintState::DELETE:
        logic.removeObject(this, scene, event);
        break;
    default:
        return;
    }

}

void PaintView::mouseMoveEvent(QMouseEvent *event)
{
    qDebug() << "MOVE";
    switch(state)
    {
    case PaintState::DRAW:
        logic.updateFigures(this, scene, event);
        break;
    case PaintState::MOVE:
        logic.changeCursor(this, event);
        logic.moveObject(this, scene, event);
        break;
    default:
        return;
    }
}

void PaintView::mouseReleaseEvent(QMouseEvent *event)
{
    Q_UNUSED(event)
    switch(state)
    {
    case PaintState::DRAW:
        logic.addDrawableObject(this, scene, event);
        break;
    case PaintState::MOVE:
        logic.releaseObject();
        break;
    default:
        return;
    }
}

void PaintView::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Escape){
        logic.cancelCurrentObject(this, scene);
    }
}

void PaintView::serialize(QDataStream &stream)
{
    logic.serialize(stream);
}

void PaintView::deserialize(QDataStream &stream)
{
    logic.deserialize(stream);
    logic.drawFigures(scene);
    this->viewport()->update();
}

void PaintView::changeFigure(model::figures::FigureType choosedType)
{
    state = PaintState::DRAW;
    logic.setType(choosedType);
}

void PaintView::switchMoveState()
{
    state = PaintState::MOVE;
}

void PaintView::switchDeleteState()
{
    state = PaintState::DELETE;
}
