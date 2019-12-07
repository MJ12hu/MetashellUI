#include "pragmawidget.h"
#include "ui_pragmawidget.h"
#include <QDialog>
#include <QDialogButtonBox>
#include <QFormLayout>
#include <QLabel>
#include <QLineEdit>

PragmaWidget::PragmaWidget(bool p_isPlugin, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PragmaWidget),
    m_isPlugin(p_isPlugin)
{
    ui->setupUi(this);

    connect(ui->btn_env, SIGNAL(clicked()), this, SLOT(envPressed()));
    connect(ui->btn_help, SIGNAL(clicked()), this, SLOT(helpPressed()));
    connect(ui->btn_mdb, SIGNAL(clicked()), this, SLOT(mdbPressed()));
    connect(ui->btn_quit, SIGNAL(clicked()), this, SLOT(quitPressed()));
    connect(ui->btn_reloadenv, SIGNAL(clicked()), this, SLOT(reloadEnvPressed()));
    connect(ui->btn_resetenv, SIGNAL(clicked()), this, SLOT(resetEnvPressed()));
    if(m_isPlugin)
        ui->btn_quit->setText(tr("Restart metashell"));
}

PragmaWidget::~PragmaWidget()
{
    delete ui;
}

QString PragmaWidget::askForParameter(const QString &p_parameterName)
{
    QDialog t_dialog(this);
    QFormLayout t_layout(&t_dialog);
    QLineEdit t_lineEdit;
    t_layout.addRow(p_parameterName, &t_lineEdit);
    QDialogButtonBox t_box(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, Qt::Horizontal);
    t_layout.addWidget(&t_box);
    connect(&t_box, SIGNAL(accepted()), &t_dialog, SLOT(accept()));
    connect(&t_box, SIGNAL(rejected()), &t_dialog, SLOT(reject()));
    if(t_dialog.exec() == QDialog::Accepted)
        return t_lineEdit.text();
    else
        return "";
}

void PragmaWidget::helpPressed()
{
    sendCommand("#msh help");
}

void PragmaWidget::mdbPressed()
{
    QString p_parameter = askForParameter("Command to evaluate:");
    if(p_parameter.trimmed() != "")
        sendCommand("#msh mdb -profile " + p_parameter);
}

void PragmaWidget::envPressed()
{
    sendCommand("#msh environment");
}

void PragmaWidget::quitPressed()
{
    if(m_isPlugin)
        restartMetashell();
    else
        sendCommand("#msh quit");
}

void PragmaWidget::reloadEnvPressed()
{
    sendCommand("#msh environment reload");
}

void PragmaWidget::resetEnvPressed()
{
    sendCommand("#msh environment reset");
}
