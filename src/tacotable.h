#ifndef TACOTABLE_H
#define TACOTABLE_H

#include "taco.h"

#include <QTableWidget>

typedef QPair<QTableWidgetItem *, QTableWidgetItem *> TTableRow;

class TacoTable : public QTableWidget
{
public:
    TacoTable(QWidget *parent = nullptr);
    ~TacoTable();

    void addTaco(Taco *taco);
    void setTacos(QList<Taco *> tacos);
private:
    enum {
        NAME,
        PRICE
    };

    bool hasTaco(Taco *taco);
    QMap<QString, TTableRow> tacos;
};

#endif // TACOTABLE_H
