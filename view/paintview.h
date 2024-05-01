#ifndef PAINTVIEW_H
#define PAINTVIEW_H


#include "model/figuresenum.h"
#include <viewmodel/paintviewlogic.h>
#include <QGraphicsView>
#include <QGraphicsScene>

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

namespace view
{

    using DrawableFigurePtr = std::shared_ptr<drawable_figures::DrawableFigure>;

    class PaintView: public QGraphicsView
    {
        Q_OBJECT
    public:
        PaintView(QWidget* parent = nullptr);

        void mousePressEvent(QMouseEvent*) override;
        void mouseMoveEvent(QMouseEvent*) override;
        void mouseReleaseEvent(QMouseEvent*) override;

        void keyPressEvent(QKeyEvent*) override;

        void serialize(QDataStream& stream);
        void deserialize(QDataStream& stream);

    public slots:
        void changeFigure(model::figures::FigureType);
        void switchMoveState();
        void switchDeleteState();
    private:
        QGraphicsScene* scene;
        model::paint::PaintState state;

        view_model::paint_view::PaintViewLogic logic;
    };
}
#endif
