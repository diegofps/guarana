#ifndef TAGSFORM_H
#define TAGSFORM_H

#include <QWidget>

#include "helpers/context.hpp"

namespace Ui {
class TagsForm;
}

class TagsForm : public QWidget
{

    Q_OBJECT

public:

    explicit TagsForm(Context & context, QWidget *parent = 0);

    ~TagsForm();

private:
    Ui::TagsForm *ui;
};

#endif // TAGSFORM_H
