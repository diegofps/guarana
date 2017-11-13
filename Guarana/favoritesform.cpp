#include "favoritesform.h"
#include "ui_favoritesform.h"

FavoritesForm::FavoritesForm(Context & context, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FavoritesForm)
{
    ui->setupUi(this);
}

FavoritesForm::~FavoritesForm()
{
    delete ui;
}
