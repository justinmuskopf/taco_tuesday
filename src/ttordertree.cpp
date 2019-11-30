#include "ttordertree.h"
#include "fullorder.h"

TTOrderTree::TTOrderTree(QWidget *parent) : QTreeWidget(parent)
{

}

void TTOrderTree::setOrders(QList<FullOrder *> orders)
{
    foreach(FullOrder *order, orders)
    {
        qDebug() << "Full Order: " << order->getId();
    }
}
