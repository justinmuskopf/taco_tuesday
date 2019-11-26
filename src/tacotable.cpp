#include "tacotable.h"
#include "tacotuesdayapihandler.h"

#include <QDebug>
#include <QHeaderView>

TacoTable::TacoTable(QWidget *parent) : QTableWidget(parent)
{
    connect(TacoTuesdayApiHandler::Instance(), &TacoTuesdayApiHandler::on_finished_getting_tacos, [=](QList<Taco *> tacos){
        setTacos(tacos);
    });
}

bool TacoTable::hasTaco(Taco *taco)
{
    return tacos.contains(taco->getType());
}

void TacoTable::addTaco(Taco *taco)
{
    qDebug() << "Adding taco.." << taco->getName() << taco->getType();
    if (hasTaco(taco))
    {
        TTableRow row = tacos[taco->getType()];
        row.second->setText(QString::number(taco->getPrice()));
    }
    else
    {
        int rowNum = rowCount();
        insertRow(rowNum);

        TTableRow row(new QTableWidgetItem(taco->getName()), new QTableWidgetItem(QString::number(taco->getPrice())));
        setItem(rowNum, NAME, row.first);
        setItem(rowNum, PRICE, row.second);

        tacos[taco->getType()] = row;
    }
}

void TacoTable::setTacos(QList<Taco *> tacos)
{
    clear();
    foreach (Taco *taco, tacos)
    {
        addTaco(taco);
    }

    QHeaderView *header = horizontalHeader();
    header->setSectionResizeMode(QHeaderView::Stretch);
    header->setVisible(true);
    setHorizontalHeaderLabels(QStringList({"Taco", "Price ($)"}));

    verticalHeader()->setVisible(true);
}

TacoTable::~TacoTable()
{
    foreach (TTableRow row, tacos.values())
    {
        if (row.first)
        {
            delete row.first;
        }

        if (row.second)
        {
            delete row.second;
        }
    }
}
