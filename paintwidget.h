#ifndef PAINTWIDGET_H
#define PAINTWIDGET_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class PaintWidget; }
QT_END_NAMESPACE

class PaintWidget : public QWidget
{
    Q_OBJECT

public:
    PaintWidget(QWidget *parent = nullptr);
    ~PaintWidget();

private slots:
    void saveButton_clicked();
    void loadButton_clicked();

private:
    Ui::PaintWidget *ui;
};
#endif // PAINTWIDGET_H
