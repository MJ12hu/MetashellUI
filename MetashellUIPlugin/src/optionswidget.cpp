#include "optionswidget.h"
#include "ui_optionswidget.h"
#include <QFileDialog>

OptionsWidget::OptionsWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::OptionsWidget)
{
    ui->setupUi(this);
    connect(ui->btnSelectPath, &QPushButton::clicked, this, &OptionsWidget::onSearchFilePath);
}

OptionsWidget::~OptionsWidget()
{
    delete ui;
}

void OptionsWidget::setupPath(const QString &p_path)
{
    ui->leMetashellpath->setText(p_path);
}

QString OptionsWidget::getPath()
{
    return ui->leMetashellpath->text();
}

void OptionsWidget::onSearchFilePath()
{
    QString t_executable = QFileDialog::getOpenFileName(0, "Metashell execuatble");
    if(t_executable != "")
        setupPath(t_executable);
}
