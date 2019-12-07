#include "treewidget.h"
#include "ui_treewidget.h"

TreeWidget::TreeWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TreeWidget)
{
    ui->setupUi(this);

    m_piechartWidget = std::make_shared<PiechartWidget>();

    ui->gl_chart->addWidget(m_piechartWidget.get());

    connect(ui->cb_onlyDirect, SIGNAL(toggled(bool)), this, SLOT(checkboxChecked()));
    connect(ui->tw_tree->selectionModel(), SIGNAL(currentChanged(QModelIndex,QModelIndex)), this, SLOT(selectionChanged(QModelIndex)));
}

TreeWidget::~TreeWidget()
{
    delete ui;
}

void TreeWidget::arrayArrived(JsonArray p_array)
{
    m_array = p_array;

    ui->tw_tree->clear();

    QTreeWidgetItem *t_root = new QTreeWidgetItem();
    t_root->setText(0, "Root");
    t_root->setData(0, Qt::UserRole, -1);
    ui->tw_tree->addTopLevelItem(t_root);

    QTreeWidgetItem *t_parent;
    QTreeWidgetItem *t_last;
    int t_depth = 0;
    int t_count = 0;
    for(JsonData it : p_array)
    {
        QTreeWidgetItem *t_item = new QTreeWidgetItem();
        t_item->setText(0, it.name);
        t_item->setData(0, Qt::UserRole, t_count++);
        if(it.depth == 0 || it.depth == -1)
        {
            t_root->addChild(t_item);
            t_parent = t_item;
            t_depth = it.depth;
        }
        else
        {
            if(t_depth == it.depth)
            {
                if(t_parent != nullptr)
                    t_parent->addChild(t_item);
                else
                    t_root->addChild(t_item);
            }
            else if(it.depth > t_depth)
            {
                t_parent = t_last;
                t_depth = it.depth;
                if(t_parent != nullptr)
                    t_parent->addChild(t_item);
                else
                    t_root->addChild(t_item);
            }
            else if(it.depth < t_depth)
            {
                while(it.depth != t_depth)
                {
                    t_last = t_last->parent();
                    t_depth--;
                }
                t_parent = t_last->parent();
                if(t_parent != nullptr)
                    t_parent->addChild(t_item);
                else
                    t_root->addChild(t_item);
            }
        }
        t_last = t_item;
    }
}

JsonArray TreeWidget::getChildren(int p_index)
{
    if(p_index == -1)
        return m_array;

    JsonArray t_return;

    if(p_index >= 0 && p_index < m_array.size())
    {
        int t_neededLevel = m_array[p_index].depth + 1;
        for(int i = p_index + 1; i < m_array.size(); i++)
        {
            JsonData &t_current = m_array[i];
            if(t_current.depth >= t_neededLevel)
                t_return.push_back(t_current);
            else if(t_current.depth < t_neededLevel)
                break;
        }
    }

    return t_return;
}

JsonArray TreeWidget::getDirectChildren(int p_index)
{
    JsonArray t_return;
    int t_neededLevel = 0;
    int t_from = 0;

    if(p_index >= 0 && p_index < m_array.size())
    {
        t_neededLevel = m_array[p_index].depth + 1;
        t_from = p_index + 1;
    }

    for(int i = t_from; i < m_array.size(); i++)
    {
        JsonData &t_current = m_array[i];
        if(t_current.depth == t_neededLevel || (p_index == -1 && t_current.type != "call_graph" && t_current.depth == -1))
            t_return.push_back(t_current);
        else if(t_current.depth < t_neededLevel)
            break;
    }

    return t_return;
}

void TreeWidget::checkboxChecked()
{
    selectionChanged(ui->tw_tree->currentIndex());
}

void TreeWidget::selectionChanged(QModelIndex p_new)
{
    int t_index = p_new.data(Qt::UserRole).isValid() ? p_new.data(Qt::UserRole).toInt() : -1;
    if(ui->cb_onlyDirect->isChecked())
    {
        m_piechartWidget->setData(getDirectChildren(t_index));
    }
    else
    {
        m_piechartWidget->setData(getChildren(t_index));
    }

    ui->lbl_type->setText("");
    ui->lbl_name->setText("");
    ui->lbl_kind->setText("");
    ui->lbl_timetaken->setText("");
    ui->lbl_timetakenratio->setText("");
    if(t_index >= 0 && t_index <= m_array.size())
    {
        JsonData &t_data = m_array[t_index];
        ui->lbl_type->setText(t_data.type);
        ui->lbl_name->setText(t_data.name);
        ui->lbl_kind->setText(t_data.kind);
        if(t_data.timeTaken != -1)
            ui->lbl_timetaken->setText(QString::number(t_data.timeTaken, 'f', 6));
        if(t_data.timeTakenRatio != -1)
            ui->lbl_timetakenratio->setText(QString::number(t_data.timeTakenRatio, 'f', 6));
    }
}
