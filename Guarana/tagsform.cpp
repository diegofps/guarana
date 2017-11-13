#include "tagsform.h"
#include "ui_tagsform.h"

TagsForm::TagsForm(Context & context, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TagsForm)
{
    ui->setupUi(this);
}

TagsForm::~TagsForm()
{
    delete ui;
}
