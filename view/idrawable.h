#ifndef IDRAWABLE_H
#define IDRAWABLE_H

class QGraphicsScene;

namespace view::drawable_figures
{
    class IDrawable
    {
    public:
        virtual void draw(QGraphicsScene*) = 0;
        virtual ~IDrawable(){}
    };
}

#endif
