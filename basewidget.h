#ifndef BASEWIDGET_H
#define BASEWIDGET_H

#include <QWidget>
class ComboDelegate;
class QTableView;
class QAbstractItemModel;
class QSortFilterProxyModel;
class BaseWidget : public QWidget
{
    Q_OBJECT
public:
    explicit BaseWidget(QWidget *parent = nullptr);
    virtual ~BaseWidget()=default;
private:
    enum MainModelColumns{
        mmcName
        ,mmcCity
        ,mmcHotel

        ,mmColCount
    };
    enum HotelModelColumns{
        hmcCity
        ,hmcHotel

        ,hmColCount

    };

    ComboDelegate* m_cityDelegate;
    ComboDelegate* m_hotelDelegate;
    QTableView* m_mainView;
    QAbstractItemModel* m_mainModel;
    QAbstractItemModel* m_combosModel;
    QSortFilterProxyModel* m_hotelFilter;
    void createConnections();
    void insertDummyData();
private slots:
    void filterHotels(const QModelIndex& idx);
};

#endif // BASEWIDGET_H
