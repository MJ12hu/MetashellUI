#include "metashellmainwindow.h"
#include "ui_metashellmainwindow.h"
#include <QKeyEvent>

MetashellMainWindow::MetashellMainWindow(bool p_isPlugin, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MetashellMainWindow)
{
    ui->setupUi(this);
    m_interpeter = std::make_shared<MetashellInterpreter>(p_isPlugin);
    m_currentButtonWidget = false;

    m_cw = std::make_shared<ConsoleWidget>();
    ui->consoleScrollBar->setWidget(m_cw.get());
    m_cw->setScrollBar(ui->consoleScrollBar);

    m_tw = std::make_shared<TreeWidget>();
    ui->gl_chart->addWidget(m_tw.get());

    m_pw = std::make_shared<PragmaWidget>(p_isPlugin);
    ui->gl_buttonpanel->addWidget(m_pw.get());
    connect(m_pw.get(), SIGNAL(sendCommand(QString)), this, SLOT(sendButtonCommand(QString)));
    connect(m_pw.get(), SIGNAL(restartMetashell()), this, SLOT(restartMetashell()));

    connect(m_cw.get(), SIGNAL(sendCommand(QString)), this, SLOT(sendCommand(QString)));
    connect(m_cw.get(), SIGNAL(sendCodeCompletion(QString)), this, SLOT(sendCodeCompletion(QString)));
    ui->splitter->setSizes(QList<int>({999999, 1}));

    connect(m_interpeter.get(), SIGNAL(backTraceArrived(JsonArray)), this, SLOT(backTraceArrived(JsonArray)));
    connect(m_interpeter.get(), SIGNAL(callGraphArrived(JsonArray)), this, SLOT(callGraphArrived(JsonArray)));
    connect(m_interpeter.get(), SIGNAL(codeCompletionArrived(QStringList)), this, SLOT(codeCompletionArrived(QStringList)));
    connect(m_interpeter.get(), SIGNAL(commentArrived(QString)), this, SLOT(commentArrived(QString)));
    connect(m_interpeter.get(), SIGNAL(cppCodeArrived(QString)), this, SLOT(cppCodeArrived(QString)));
    connect(m_interpeter.get(), SIGNAL(errorArrived(QString)), this, SLOT(errorArrived(QString)));
    connect(m_interpeter.get(), SIGNAL(fileNameListArrived(QStringList)), this, SLOT(fileNameListArrived(QStringList)));
    connect(m_interpeter.get(), SIGNAL(fileNameSetArrived(QStringList)), this, SLOT(fileNameSetArrived(QStringList)));
    connect(m_interpeter.get(), SIGNAL(frameArrived(JsonData)), this, SLOT(frameArrived(JsonData)));
    connect(m_interpeter.get(), SIGNAL(promptArrived(QString)), this, SLOT(promptArrived(QString)));
    connect(m_interpeter.get(), SIGNAL(rawTextArrived(QString)), this, SLOT(rawTextArrived(QString)));
    connect(m_interpeter.get(), SIGNAL(typeArrived(QString)), this, SLOT(typeArrived(QString)));
}

MetashellMainWindow::~MetashellMainWindow()
{
    delete ui;
}

void MetashellMainWindow::setExecutable(QString p_path)
{
    m_interpeter->setExecutable(p_path);
}

void MetashellMainWindow::startInterpreter()
{
    m_interpeter->start();
}

void MetashellMainWindow::sendButtonCommand(QString p_command)
{
    m_cw->addAsInput(p_command);
    m_interpeter->sendCommand(p_command);
}

void MetashellMainWindow::sendCodeCompletion(QString p_cc)
{
    m_interpeter->sendCodeCompletion(p_cc);
}


void MetashellMainWindow::sendCommand(QString p_command)
{
    m_interpeter->sendCommand(p_command);
}

void MetashellMainWindow::backTraceArrived(JsonArray p_backtrace)
{
    int t_row = 0;
    for(JsonData it : p_backtrace)
    {
        QString t_append = "#" + QString::number(t_row) + " " + it.name + " at " + it.sourceFileName + ":" + QString::number(it.sourceRow) + ":" + QString::number(it.sourceColumn) +
                " (" + it.kind + " from " + it.instantiationFileName + ":" + QString::number(it.instantiationRow) + ":" + QString::number(it.instantiationColumn) + ")";
        m_cw->addText(t_append);
        t_row++;
    }
    m_tw->arrayArrived(p_backtrace);
}

void MetashellMainWindow::callGraphArrived(JsonArray p_callGraph)
{
    for(JsonData it : p_callGraph)
    {
        QString t_append;
        for(int i = 0; i < it.depth; i++)
            t_append.append("|");
        if(it.timeTaken != -1)
            t_append += "[" + QString::number(it.timeTaken, 'f', 2) + " sec] ";
        t_append += it.name + "(" + it.kind + ")";
        m_cw->addText(t_append);
    }
    m_tw->arrayArrived(p_callGraph);
}

void MetashellMainWindow::codeCompletionArrived(QStringList p_results)
{
    m_cw->codeCompletionArrived(p_results);
}

void MetashellMainWindow::commentArrived(QString p_comment)
{
    m_cw->addComment(p_comment);
}

void MetashellMainWindow::cppCodeArrived(QString p_cppCode)
{
    m_cw->addText(p_cppCode);
}

void MetashellMainWindow::errorArrived(QString p_error)
{
    m_cw->addError(p_error);
}

void MetashellMainWindow::fileNameListArrived(QStringList p_list)
{
    m_cw->addText(p_list.join(' '));
}

void MetashellMainWindow::fileNameSetArrived(QStringList p_set)
{
    m_cw->addText(p_set.join(' '));
}

void MetashellMainWindow::frameArrived(JsonData p_frame)
{
    QString t_append = p_frame.name + " at " + p_frame.sourceFileName + ":" + QString::number(p_frame.sourceRow) + QString::number(p_frame.sourceColumn);
    if(p_frame.kind != "")
    {
        t_append += " (" + p_frame.kind + " from " + p_frame.instantiationFileName + ":" + QString::number(p_frame.instantiationRow) + ":" + QString::number(p_frame.instantiationColumn) + ")";
    }
    m_cw->addText(t_append);
}

void MetashellMainWindow::promptArrived(QString p_prompt)
{
    if(p_prompt == "(mdb)" && !m_currentButtonWidget)
    {
        ui->gl_buttonpanel->removeWidget(m_pw.get());
        m_pw.reset();
        if(!m_mw)
        {
            m_mw = std::make_shared<MDBCommands>();
            connect(m_mw.get(), SIGNAL(sendCommand(QString)), this, SLOT(sendButtonCommand(QString)));
        }
        ui->gl_buttonpanel->addWidget(m_mw.get());
        m_currentButtonWidget = true;
    }
    else if(p_prompt != "(mdb)" && m_currentButtonWidget)
    {
        ui->gl_buttonpanel->removeWidget(m_mw.get());
        /*m_mw.reset();
        m_pw = std::make_shared<PragmaWidget>();
        connect(m_pw.get(), SIGNAL(sendCommand(QString)), this, SLOT(sendButtonCommand(QString)));*/
        ui->gl_buttonpanel->addWidget(m_pw.get());
        m_currentButtonWidget = false;
    }
    m_cw->promptArrived(p_prompt);
}

void MetashellMainWindow::rawTextArrived(QString p_rawText)
{
    m_cw->addText(p_rawText);
}

void MetashellMainWindow::typeArrived(QString p_type)
{
    m_cw->addText(p_type);
}

void MetashellMainWindow::restartMetashell()
{
    m_interpeter->start();
}
