#include "uniqueproxymodel.h"

UniqueProxyModel::UniqueProxyModel(QObject *parent)
    :QSortFilterProxyModel(parent)
{
}

bool UniqueProxyModel::filterAcceptsRow(int source_row, const QModelIndex &source_parent) const
{
    if(!QSortFilterProxyModel::filterAcceptsRow(source_row,source_parent))
        return false;
    const QVariant currentdata = sourceModel()->index(source_row,filterKeyColumn(),source_parent).data();
    for(int i=0;i<source_row;++i){
        if(sourceModel()->index(i,filterKeyColumn(),source_parent).data()==currentdata)
            return false;
    }
    return true;
}
