#include "basewidget.h"
#include "combodelegate.h"
#include <QStandardItemModel>
#include <QTableView>
#include <QSortFilterProxyModel>
#include <QVBoxLayout>
#include <QHeaderView>
#include <QRegularExpression>
#include <uniqueproxymodel.h>
BaseWidget::BaseWidget(QWidget *parent)
    : QWidget(parent)
{
    m_mainModel=new QStandardItemModel(this);
    m_mainModel->insertColumns(0,mmColCount);
    m_mainModel->setHeaderData(mmcName,Qt::Horizontal,tr("Name"));
    m_mainModel->setHeaderData(mmcCity,Qt::Horizontal,tr("City"));
    m_mainModel->setHeaderData(mmcHotel,Qt::Horizontal,tr("Hotel"));

    m_combosModel= new QStandardItemModel(this);
    m_combosModel->insertColumns(0,hmColCount);
    m_combosModel->setHeaderData(hmcCity,Qt::Horizontal,tr("City"));
    m_combosModel->setHeaderData(hmcHotel,Qt::Horizontal,tr("Hotel"));

    m_hotelFilter=new QSortFilterProxyModel(this);
    m_hotelFilter->setFilterKeyColumn(hmcCity);
    m_hotelFilter->setSourceModel(m_combosModel);

    UniqueProxyModel *cityFilter=new UniqueProxyModel(this);
    cityFilter->setFilterKeyColumn(hmcCity);
    cityFilter->setSourceModel(m_combosModel);

    m_cityDelegate=new ComboDelegate(this);
    m_cityDelegate->setBaseModel(cityFilter);
    m_cityDelegate->setModelColumn(hmcCity);

    m_hotelDelegate=new ComboDelegate(this);
    m_hotelDelegate->setBaseModel(m_hotelFilter);
    m_hotelDelegate->setModelColumn(hmcHotel);


    m_mainView=new QTableView(this);
    m_mainView->setModel(m_mainModel);
    m_mainView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    m_mainView->horizontalHeader()->setStretchLastSection(true);
    m_mainView->setSortingEnabled(false);
    m_mainView->setItemDelegateForColumn(mmcCity,m_cityDelegate);
    m_mainView->setItemDelegateForColumn(mmcHotel,m_hotelDelegate);
    m_mainView->setSelectionBehavior(QAbstractItemView::SelectItems);
    m_mainView->setSelectionMode(QAbstractItemView::SingleSelection);
    m_mainView->setEditTriggers(QAbstractItemView::AllEditTriggers);


    QVBoxLayout* mainLay=new QVBoxLayout(this);
    mainLay->addWidget(m_mainView);

    insertDummyData(); //Populate the models with some data
    createConnections();
}

void BaseWidget::createConnections()
{
    connect(m_hotelDelegate,&ComboDelegate::editorCreated,this,&BaseWidget::filterHotels);
}

void BaseWidget::insertDummyData()
{
    m_mainModel->insertRows(0,5);

    m_combosModel->insertRows(0,6);
    m_combosModel->setData(m_combosModel->index(0,hmcCity),"London");
    m_combosModel->setData(m_combosModel->index(0,hmcHotel),"Prince");

    m_combosModel->setData(m_combosModel->index(1,hmcCity),"London");
    m_combosModel->setData(m_combosModel->index(1,hmcHotel),"Queen");

    m_combosModel->setData(m_combosModel->index(2,hmcCity),"Paris");
    m_combosModel->setData(m_combosModel->index(2,hmcHotel),"Galerie");

    m_combosModel->setData(m_combosModel->index(3,hmcCity),"Rome");
    m_combosModel->setData(m_combosModel->index(3,hmcHotel),"Colosseum");

    m_combosModel->setData(m_combosModel->index(4,hmcCity),"Rome");
    m_combosModel->setData(m_combosModel->index(4,hmcHotel),"Imperial");

    m_combosModel->setData(m_combosModel->index(5,hmcCity),"New York");
    m_combosModel->setData(m_combosModel->index(5,hmcHotel),"Plaza");
}
#include <QDebug>
void BaseWidget::filterHotels(const QModelIndex &idx)
{
    if(idx.isValid()){
        const QString hotelCity=m_mainModel->index(idx.row(),mmcCity).data().toString().trimmed();
        qDebug()<< idx.row() << " - " << hotelCity;
        if(!hotelCity.isEmpty()){
            m_hotelFilter->setFilterRegExp(".*" + QRegularExpression::escape(hotelCity)  + ".*");
            return;
        }
    }
    m_hotelFilter->setFilterRegExp("(?!x)x");
}
