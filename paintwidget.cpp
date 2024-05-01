#include "paintwidget.h"
#include "ui_paintwidget.h"

#include "view/painttoolbar.h"
#include "view/paintview.h"

#include <QFileDialog>
#include <QMessageBox>

PaintWidget::PaintWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::PaintWidget)
{
    ui->setupUi(this);
    connect(ui->toolbar, &view::PaintToolBar::figureButtonClicked,
            ui->paintArea, &view::PaintView::changeFigure);
    connect(ui->toolbar, &view::PaintToolBar::moveButtonClicked,
            ui->paintArea, &view::PaintView::switchMoveState);
    connect(ui->toolbar, &view::PaintToolBar::deleteButtonClicked,
            ui->paintArea, &view::PaintView::switchDeleteState);

    connect(ui->toolbar, &view::PaintToolBar::saveButtonClicked,
            this, &PaintWidget::saveButton_clicked);
    connect(ui->toolbar, &view::PaintToolBar::loadButtonClicked,
            this, &PaintWidget::loadButton_clicked);
}

PaintWidget::~PaintWidget()
{
    delete ui;
}

void PaintWidget::saveButton_clicked()
{
    QString selectedFile = QFileDialog::getSaveFileName(this, "Сохранение", QDir::toNativeSeparators("D:/"), "All Files(*);;Text Files(*.txt)");
    QFile file(selectedFile);
    if(!file.open(QFile::WriteOnly))
    {
        QMessageBox::warning(this, "Ошибка", "Не получилось открыть файл");
        return;
    }
    QDataStream stream(&file);
    stream << width() << height();
    ui->paintArea->serialize(stream);
}

void PaintWidget::loadButton_clicked()
{
    QString selectedFile = QFileDialog::getOpenFileName(this, "Загрузка", QDir::toNativeSeparators("D:/"), "All Files(*);;Text Files(*.txt)");
    QFile file(selectedFile);
    if(!file.open(QFile::ReadOnly))
    {
        QMessageBox::warning(this, "Ошибка", "Не получилось открыть файл");
        return;
    }
    QDataStream stream(&file);
    int width = 0, height = 0;
    stream >> width >> height;
    resize(width, height);
    ui->paintArea->deserialize(stream);
}


