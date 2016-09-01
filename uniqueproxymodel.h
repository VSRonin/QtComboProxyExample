#ifndef UNIQUEPROXYMODEL_H
#define UNIQUEPROXYMODEL_H

#include <QSortFilterProxyModel>
class UniqueProxyModel : public QSortFilterProxyModel
{
public:
    explicit UniqueProxyModel(QObject* parent=nullptr);
    virtual ~UniqueProxyModel()=default;
protected:
    virtual bool filterAcceptsRow(int source_row, const QModelIndex &source_parent) const override;
};

#endif // UNIQUEPROXYMODEL_H
