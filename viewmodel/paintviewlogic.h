#ifndef PAINT_SCENE_LOGIC_H
#define PAINT_SCENE_LOGIC_H

#include "model/figuresenum.h"
#include <QGraphicsView>
#include <QGraphicsScene>


namespace view
{
    class PaintView;
}


class QGraphicsScene;

class QMouseEvent;
class QKeyEvent;

class QWidget;

namespace model::figures
{
class AbstractFigure;
struct FigureType;
}

namespace model::paint
{
enum class PaintState;
}
namespace view::drawable_figures
{
    class DrawableFigure;
}


namespace view_model::paint_view
{
    using DrawableFigurePtr = std::shared_ptr<view::drawable_figures::DrawableFigure>;

    class PaintViewLogic
    {
    public:
        PaintViewLogic();

        void setType(model::figures::FigureType);

        bool currentObjectIsValid();

        void mousePressEvent(QMouseEvent*);

        void drawFigures(QGraphicsScene*);
        void createDrawableObject(view::PaintView*,
                               QMouseEvent*);
        void updateFigures(view::PaintView*, QGraphicsScene*, QMouseEvent*);
        void addDrawableObject(view::PaintView*, QGraphicsScene*,
                                QMouseEvent*);

        void moveObject(view::PaintView*, QGraphicsScene*, QMouseEvent*);
        void selectObject(view::PaintView*, QMouseEvent*);
        void releaseObject();

        void removeObject(view::PaintView*, QGraphicsScene*, QMouseEvent*);

        void cancelCurrentObject(view::PaintView*, QGraphicsScene*);

        DrawableFigurePtr figureContainCursor(view::PaintView* view, QMouseEvent*);
        void changeCursor(view::PaintView*, QMouseEvent*);

        qint64 indexOfFigures(const std::shared_ptr<model::figures::AbstractFigure>&);

        void serialize(QDataStream&);
        void deserialize(QDataStream&);
    private:
        QPointF point;
        model::figures::FigureType type;
        QList<DrawableFigurePtr> figures;
        QList<DrawableFigurePtr> paths;
        DrawableFigurePtr currentObject;
    };
}
#endif
