#ifndef PAINTSTATE_H
#define PAINTSTATE_H

namespace model::paint
{
    enum class PaintState
    {
        DRAW,
        MOVE,
        DELETE,
        NOTHING
    };
}

#endif // PAINTSTATE_H
