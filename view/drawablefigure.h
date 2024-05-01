#ifndef DRAWABLEFIGURE_H
#define DRAWABLEFIGURE_H

#include "idrawable.h"

#include "model/abstractfigure.h"

#include <model/figuresenum.h>

class QPainter;

namespace view::drawable_figures
{

    class DrawableFigure: public IDrawable
    {
    public:
        DrawableFigure(model::figures::AbstractFigure*, model::figures::FigureType);
        DrawableFigure(std::shared_ptr<model::figures::AbstractFigure>, model::figures::FigureType);
        void draw(QGraphicsScene*) override;

        std::shared_ptr<model::figures::AbstractFigure>& getFigure();
        model::figures::FigureType getType();

        void setFigure(std::shared_ptr<model::figures::AbstractFigure>);
        void setType(model::figures::FigureType);

    private:
        std::shared_ptr<model::figures::AbstractFigure> figure;
        model::figures::FigureType figureType;
    };
}

#endif
