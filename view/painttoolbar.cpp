#include "painttoolbar.h"
#include "ui_painttoolbar.h"

using namespace view;
using namespace model::figures;

PaintToolBar::PaintToolBar(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PaintToolBar)
{
    ui->setupUi(this);
}

PaintToolBar::~PaintToolBar()
{
    delete ui;
}

void PaintToolBar::figureButton_clicked()
{
    QPushButton* button = (QPushButton*)sender();
    emit figureButtonClicked(FigureType::fromStringRepresentation(button->text()));
}

void PaintToolBar::on_moveButton_clicked()
{
   emit moveButtonClicked();
}


void PaintToolBar::on_deleteButton_clicked()
{
    emit deleteButtonClicked();
}


void PaintToolBar::on_saveButton_clicked()
{
    emit saveButtonClicked();
}


void PaintToolBar::on_loadButton_clicked()
{

    emit loadButtonClicked();
}

