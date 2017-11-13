#ifndef THRASHFORM_H
#define THRASHFORM_H

#include <QWidget>

#include "helpers/context.hpp"

namespace Ui {
class ThrashForm;
}

class ThrashForm : public QWidget
{
    Q_OBJECT

public:

    explicit ThrashForm(Context & context, QWidget *parent = 0);

    ~ThrashForm();

private:
    Ui::ThrashForm *ui;
};

#endif // THRASHFORM_H
