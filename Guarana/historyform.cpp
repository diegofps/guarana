#include "historyform.h"
#include "ui_historyform.h"

HistoryForm::HistoryForm(Context & context, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HistoryForm),
    _context(context)
{
    ui->setupUi(this);
}

HistoryForm::~HistoryForm()
{
    delete ui;
}
