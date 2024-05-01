#ifndef PAINTTOOLBAR_H
#define PAINTTOOLBAR_H

#include <QWidget>

#include "model/figuresenum.h"

namespace Ui
{
    class PaintToolBar;
}

namespace model::figures
{
    struct FigureType;
}

namespace view
{
    class PaintToolBar : public QWidget
    {
        Q_OBJECT

    public:
        explicit PaintToolBar(QWidget *parent = nullptr);
        ~PaintToolBar();
    public slots:
        void figureButton_clicked();
        void on_moveButton_clicked();
        void on_deleteButton_clicked();

        void on_saveButton_clicked();
        void on_loadButton_clicked();
    signals:
        void figureButtonClicked(model::figures::FigureType);
        void moveButtonClicked();
        void deleteButtonClicked();
        void loadButtonClicked();
        void saveButtonClicked();
    private:
        Ui::PaintToolBar *ui;
    };
}
#endif // PAINTTOOLBAR_H
