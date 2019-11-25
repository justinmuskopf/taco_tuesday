#ifndef TTORDERTREE_H
#define TTORDERTREE_H

#include <QTreeWidget>
#include "fullorder.h"

class FullOrder;

class TTOrderTree : public QTreeWidget
{
public:
    TTOrderTree(QWidget *parent = nullptr);
    void setOrders(QList<FullOrder *> orders);
};

#endif // TTORDERTREE_H
