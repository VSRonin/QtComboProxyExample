#ifndef COMBODELEGATE_H
#define COMBODELEGATE_H

#include <QStyledItemDelegate>
class QAbstractItemModel;
class ComboDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    explicit ComboDelegate(QWidget *parent = nullptr);
    virtual ~ComboDelegate()=default;
    virtual QWidget* createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
    virtual void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
    virtual void setEditorData(QWidget *editor, const QModelIndex &index) const override;
    virtual void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const override;
    virtual QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const override;
    virtual void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
    QAbstractItemModel* baseModel() const;
    void setBaseModel(QAbstractItemModel *baseModel);
    int modelColumn() const;
    void setModelColumn(int modelColumn);

private:
    QAbstractItemModel* m_baseModel;
    int m_modelColumn;
signals:
    void editorCreated(const QModelIndex &index) const;
};

#endif // COMBODELEGATE_H
