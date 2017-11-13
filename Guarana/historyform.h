#ifndef HISTORYFORM_H
#define HISTORYFORM_H

#include <QWidget>

#include "helpers/context.hpp"

namespace Ui {
class HistoryForm;
}

class HistoryForm : public QWidget
{

    Q_OBJECT

public:
    explicit HistoryForm(Context & context, QWidget *parent = 0);
    ~HistoryForm();

private:
    Ui::HistoryForm *ui;
};

#endif // HISTORYFORM_H
