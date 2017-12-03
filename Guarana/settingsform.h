#ifndef SETTINGSFORM_H
#define SETTINGSFORM_H

#include <QWidget>

#include "helpers/context.hpp"

namespace Ui {
class SettingsForm;
}

class SettingsForm : public QWidget
{

    Q_OBJECT

public:

    explicit SettingsForm(Context & context, QWidget *parent = 0);

    ~SettingsForm();

private:

    Ui::SettingsForm *ui;

    Context & _context;

};

#endif // SETTINGSFORM_H
