#include "thrashform.h"
#include "ui_thrashform.h"

ThrashForm::ThrashForm(Context & context, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ThrashForm)
{
    ui->setupUi(this);
}

ThrashForm::~ThrashForm()
{
    delete ui;
}
