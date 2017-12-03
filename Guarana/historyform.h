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

    Context & _context;

};

#endif // HISTORYFORM_H
