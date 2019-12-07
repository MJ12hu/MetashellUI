#ifndef METASHELLMAINWINDOW_H
#define METASHELLMAINWINDOW_H

#include <QMainWindow>
#include "metashellinterpreter.h"

#include "consolewidget.h"
#include "mdbcommands.h"
#include "pragmawidget.h"
#include "treewidget.h"

namespace Ui {
class MetashellMainWindow;
}

class MetashellMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MetashellMainWindow(bool p_isPlugin, QWidget *parent = 0);
    ~MetashellMainWindow();
    void setExecutable(QString p_path);
    void startInterpreter();
private:

    Ui::MetashellMainWindow*                    ui;
    std::shared_ptr<MetashellInterpreter>       m_interpeter;
    std::shared_ptr<ConsoleWidget>              m_cw;
    std::shared_ptr<MDBCommands>                m_mw;
    std::shared_ptr<PragmaWidget>               m_pw;
    std::shared_ptr<TreeWidget>                 m_tw;
    bool                                        m_currentButtonWidget; //false = PragmaWidget, true = MDBCommands
private slots:
    void                                        sendButtonCommand(QString p_command);
    void                                        sendCommand(QString p_command);
    void                                        sendCodeCompletion(QString p_cc);
    void                                        backTraceArrived(JsonArray p_backtrace);
    void                                        callGraphArrived(JsonArray p_callGraph);
    void                                        codeCompletionArrived(QStringList p_results);
    void                                        commentArrived(QString p_comment);
    void                                        cppCodeArrived(QString p_cppCode);
    void                                        errorArrived(QString p_error);
    void                                        fileNameListArrived(QStringList p_list);
    void                                        fileNameSetArrived(QStringList p_set);
    void                                        frameArrived(JsonData p_frame);
    void                                        promptArrived(QString p_prompt);
    void                                        rawTextArrived(QString p_rawText);
    void                                        typeArrived(QString p_type);
    void                                        restartMetashell();
};

#endif // METASHELLMAINWINDOW_H
