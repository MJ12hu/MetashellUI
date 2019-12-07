#ifndef TREEWIDGET_H
#define TREEWIDGET_H

#include <QWidget>
#include <DataTypes/jsondata.hpp>
#include <QModelIndex>
#include <memory>
#include <piechartwidget.h>

namespace Ui {
class TreeWidget;
}

class TreeWidget : public QWidget
{
    Q_OBJECT

public:
    explicit TreeWidget(QWidget *parent = 0);
    ~TreeWidget();

    void                                arrayArrived(JsonArray p_array);
private:
    Ui::TreeWidget *ui;
    JsonArray                           m_array;
    std::shared_ptr<PiechartWidget>     m_piechartWidget;

    JsonArray                           getChildren(int p_index);
    JsonArray                           getDirectChildren(int p_index);
private slots:
    void                                checkboxChecked();
    void                                selectionChanged(QModelIndex p_new);
};

#endif // TREEWIDGET_H
