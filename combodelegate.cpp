#include "combodelegate.h"
#include <QComboBox>
#include <QAbstractItemModel>
#include <QStyleOptionComboBox>
#include <QPainter>
#include <QApplication>
ComboDelegate::ComboDelegate(QWidget *parent)
    : QStyledItemDelegate(parent)
    ,m_baseModel(nullptr)
    ,m_modelColumn(0)
{

}

QWidget *ComboDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    Q_UNUSED(option)
    QComboBox* comboEditor =new QComboBox(parent);
    if(m_baseModel){
        comboEditor->setModel(m_baseModel);
        comboEditor->setModelColumn(m_modelColumn);
    }
    emit editorCreated(index);
    return comboEditor;
}

void ComboDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QStyleOptionComboBox opt;
    opt.palette=option.palette;
    opt.rect = option.rect;
    opt.state = QStyle::State_Active | QStyle::State_Enabled;
    opt.editable = false;
    opt.frame = false;
    opt.subControls = QStyle::SC_All;
    if (index.isValid()) {
        opt.currentText = index.data().toString();
        opt.currentIcon = index.data(Qt::DecorationRole).value<QIcon>();
    }
    opt.iconSize = option.decorationSize;
    QApplication::style()->drawComplexControl(QStyle::CC_ComboBox, &opt,painter);
    QApplication::style()->drawControl(QStyle::CE_ComboBoxLabel, &opt,painter);
}

void ComboDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    QComboBox* comboEditor = qobject_cast<QComboBox*>(editor);
    Q_ASSERT(comboEditor);
    if(!index.isValid())
        comboEditor->setCurrentIndex(-1);
    else if (index.model()->data(index, Qt::EditRole).isNull())
        comboEditor->setCurrentIndex(-1);
    else
        comboEditor->setCurrentText(index.model()->data(index, Qt::EditRole).toString());
}

void ComboDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    QComboBox* comboEditor = qobject_cast<QComboBox*>(editor);
    Q_ASSERT(comboEditor);
    const int affectedRoles[] = {Qt::EditRole,Qt::UserRole,Qt::DecorationRole};
    if (comboEditor->currentIndex() < 0) {
        for(int roleToClear : affectedRoles)
            model->setData(index, QVariant(), roleToClear);
    }
    else {
        for(int roleToSet : affectedRoles)
            model->setData(index, comboEditor->model()->index(comboEditor->currentIndex(),m_modelColumn).data(roleToSet), roleToSet);
    }
}

void ComboDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    Q_UNUSED(index)
    editor->setGeometry(option.rect);
}

QAbstractItemModel *ComboDelegate::baseModel() const
{
    return m_baseModel;
}

void ComboDelegate::setBaseModel(QAbstractItemModel *baseModel)
{
    m_baseModel = baseModel;
    setModelColumn(m_modelColumn);
}

int ComboDelegate::modelColumn() const
{
    return m_modelColumn;
}

void ComboDelegate::setModelColumn(int modelColumn)
{
    if(m_baseModel)
        modelColumn = qMin(modelColumn,m_baseModel->columnCount());
    m_modelColumn = qMax(0,modelColumn);
}

QSize ComboDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex & index) const
{
    Q_UNUSED(index)
    int MaxWid = 0;
    if(m_baseModel){
        for (int i = 0; i < m_baseModel->rowCount(); ++i) {
            if (option.fontMetrics.width(m_baseModel->index(i, m_modelColumn).data().toString())>MaxWid)
                MaxWid = option.fontMetrics.width(m_baseModel->index(i, m_modelColumn).data().toString());
        }
    }
    return qApp->style()->sizeFromContents(
        QStyle::CT_ComboBox,
        &option,
        QSize(MaxWid, option.fontMetrics.height())
        );
}
