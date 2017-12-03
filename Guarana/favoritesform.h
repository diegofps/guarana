#ifndef FAVORITESFORM_H
#define FAVORITESFORM_H

#include <QWidget>

#include "helpers/context.hpp"

namespace Ui {
class FavoritesForm;
}

class FavoritesForm : public QWidget
{

    Q_OBJECT

public:

    explicit FavoritesForm(Context & context, QWidget *parent = 0);

    ~FavoritesForm();

private:

    Ui::FavoritesForm *ui;

    Context & _context;

};

#endif // FAVORITESFORM_H
