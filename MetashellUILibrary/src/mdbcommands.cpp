#include "mdbcommands.h"
#include "ui_mdbcommands.h"
#include <QDialog>
#include <QDialogButtonBox>
#include <QFormLayout>
#include <QLabel>
#include <QLineEdit>

MDBCommands::MDBCommands(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MDBCommands)
{
    ui->setupUi(this);

    connect(ui->pb_backtrace, SIGNAL(clicked()), this, SLOT(backtracePressed()));
    connect(ui->pb_break, SIGNAL(clicked()), this, SLOT(breakPressed()));
    connect(ui->pb_continue, SIGNAL(clicked()), this, SLOT(continuePressed()));
    connect(ui->pb_evaluate, SIGNAL(clicked()), this, SLOT(evaluatePressed()));
    connect(ui->pb_finish, SIGNAL(clicked()), this, SLOT(finishPressed()));
    connect(ui->pb_forwardtrace, SIGNAL(clicked()), this, SLOT(forwardTracePressed()));
    connect(ui->pb_frame, SIGNAL(clicked()), this, SLOT(framePressed()));
    connect(ui->pb_help, SIGNAL(clicked()), this, SLOT(helpPressed()));
    connect(ui->pb_next, SIGNAL(clicked()), this, SLOT(nextPressed()));
    connect(ui->pb_quit, SIGNAL(clicked()), this, SLOT(quitPressed()));
    connect(ui->pb_rbreak, SIGNAL(clicked()), this, SLOT(rBreakPressed()));
    connect(ui->pb_step, SIGNAL(clicked()), this, SLOT(stepPressed()));
}

MDBCommands::~MDBCommands()
{
    delete ui;
}

QString MDBCommands::askForParameter(const QString &p_parameterName)
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

void MDBCommands::backtracePressed()
{
    sendCommand("bt");
}

void MDBCommands::breakPressed()
{
    sendCommand("break list");
}

void MDBCommands::continuePressed()
{
    sendCommand("continue");
}

void MDBCommands::evaluatePressed()
{
    QString p_parameter = askForParameter("Command to evaluate:");
    if(p_parameter.trimmed() != "")
        sendCommand("evaluate " + p_parameter);
}

void MDBCommands::finishPressed()
{
    sendCommand("finish");
}

void MDBCommands::forwardTracePressed()
{
    sendCommand("ft");
}

void MDBCommands::framePressed()
{
    sendCommand("frame");
}

void MDBCommands::helpPressed()
{
    sendCommand("help");
}

void MDBCommands::nextPressed()
{
    sendCommand("next");
}

void MDBCommands::quitPressed()
{
    sendCommand("quit");
}

void MDBCommands::rBreakPressed()
{
    QString p_parameter = askForParameter("Breakpoint regex:");
    if(p_parameter.trimmed() != "")
        sendCommand("rbreak " + p_parameter);
}

void MDBCommands::stepPressed()
{
    sendCommand("step");
}
