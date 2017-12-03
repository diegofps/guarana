#include "thrashform.h"
#include "ui_thrashform.h"

ThrashForm::ThrashForm(Context & context, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ThrashForm),
    _context(context)
{
    ui->setupUi(this);
}

ThrashForm::~ThrashForm()
{
    delete ui;
}
