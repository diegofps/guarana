#include "settingsform.h"
#include "ui_settingsform.h"

SettingsForm::SettingsForm(Context & context, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SettingsForm),
    _context(context)
{
    ui->setupUi(this);
}

SettingsForm::~SettingsForm()
{
    delete ui;
}
