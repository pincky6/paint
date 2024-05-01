#ifndef FIGURESENUM_H
#define FIGURESENUM_H

#include <QString>

namespace model::figures
{
    struct FigureType
    {
        enum Value
        {
            RECTANGLE,
            TRIANGLE,
            ELLIPSE,
            PATH,
            FIGURE
        };
        FigureType() = default;

        constexpr FigureType(Value figureType): value(figureType){}

        constexpr bool operator==(FigureType a) const
        {
            return value == a.value;
        }
        constexpr bool operator!=(FigureType a) const
        {
            return value != a.value;
        }
        constexpr bool operator==(Value a) const
        {
            return value == a;
        }
        constexpr bool operator!=(Value a) const
        {
            return value != a;
        }
        constexpr operator Value() const
        {
            return value;
        }

        static QString toStringRepresentation(FigureType figureType)
        {
            switch(figureType.value)
            {
            case Value::RECTANGLE:
                return "RECTANGLE";
            case Value::TRIANGLE:
                return "TRIANGLE";
            case Value::ELLIPSE:
                return "ELLIPSE";
            case Value::PATH:
                return "PATH";
            default:
                return "FIGURE";
            }
        }
        static FigureType fromStringRepresentation(const QString& stringValue)
        {
            Value value = Value::FIGURE;
            if(stringValue == "RECTANGLE" || stringValue == QString("Прямоугольник"))
            {
                value = Value::RECTANGLE;
            }
            else if(stringValue == "TRIANGLE" || stringValue == QString("Треугольник"))
            {
                value = Value::TRIANGLE;
            }
            else if(stringValue == "ELLIPSE" || stringValue == QString("Эллипс"))
            {
                value = Value::ELLIPSE;
            }
            else if(stringValue == "PATH" || stringValue == QString("Связь"))
            {
                value = Value::PATH;
            }
            return FigureType(value);
        }
    private:
        Value value;
    };
}
#endif // FIGURESENUM_H
