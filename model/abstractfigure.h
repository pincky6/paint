#ifndef ABSTRACTFIGURE_H
#define ABSTRACTFIGURE_H

#include <QVector>
#include <QPointF>
#include <QDataStream>

namespace model::figures
{
    class AbstractFigure
    {
    public:
        AbstractFigure();
        virtual ~AbstractFigure();

        QVector<QPointF>& getVertices();
        const QVector<QPointF>& getVertices() const;

        AbstractFigure &operator+=(const QPointF&);

        virtual bool containsPoint(const QPointF& point);
        virtual QPointF getCenter();
        friend QDataStream& operator<<(QDataStream& out, const AbstractFigure& figure)
        {
            out << figure.vertices.size();
            foreach (const QPointF& vertex, figure.vertices) {
                out << vertex;
            }
            return out;
        }
        friend QDataStream& operator>>(QDataStream& in, AbstractFigure& figure)
        {
            quint64 size;
            in >> size;
            for (quint64 i = 0; i < size; i++)
            {
                QPointF point;
                in >> point;
                figure.vertices.push_back(point);
            }
            return in;
        }
    protected:
        QVector<QPointF> vertices;
    };
}

#endif
