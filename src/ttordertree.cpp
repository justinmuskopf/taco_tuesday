#include "ttordertree.h"
#include "fullorder.h"

TTOrderTree::TTOrderTree(QWidget *parent) : QTreeWidget(parent)
{

}

void TTOrderTree::setOrders(QList<FullOrder *> orders)
{
    foreach(FullOrder *order, orders)
    {
        qDebug() << order->price(1.50);
    }
}
