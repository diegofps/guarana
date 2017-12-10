#ifndef THRASHFORM_H
#define THRASHFORM_H

#include <QWidget>

#include <widgetmodels/filetablemodel.hpp>
#include <widgetmodels/ptrlistmodel.hpp>

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

    void configureGarbageList();

private slots:

    void showContextMenu(const QPoint &pos);

    void eraseAll();

    void recoverAll();

    void recoverSelected();

    void eraseSelected();

    void updateList();

private:

    Ui::ThrashForm *ui;

    Context & _context;

    FileTableModel _modelHolder;

};

#endif // THRASHFORM_H
