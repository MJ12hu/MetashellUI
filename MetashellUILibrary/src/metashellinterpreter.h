#ifndef METASHELLINTERPRETER_H
#define METASHELLINTERPRETER_H

#include <QObject>
#include <QVector>
#include <QProcess>
#include <memory>

#include "DataTypes/jsondata.hpp"

class MetashellInterpreter : public QObject
{
    Q_OBJECT
public:
    explicit MetashellInterpreter(bool p_isPlugin, QObject *parent = 0);
    ~MetashellInterpreter();

    void                                setExecutable(const QString p_path);
    void                                start();
    void                                sendCommand(QString p_command);
    void                                sendCodeCompletion(QString p_cc);
private:
    void                                processJson(QByteArray &p_input);
    std::shared_ptr<QProcess>           m_metashell;
    QByteArray                          m_buffer;
    QString                             m_executable;
    bool                                m_isPlugin;
    bool                                m_restartImmediately;
signals:
    void                                backTraceArrived(JsonArray p_backtrace);
    void                                callGraphArrived(JsonArray p_callGraph);
    void                                codeCompletionArrived(QStringList p_results);
    void                                commentArrived(QString p_comment);
    void                                cppCodeArrived(QString p_cppCode);
    void                                errorArrived(QString p_error);
    void                                fileNameListArrived(QStringList p_list);
    void                                fileNameSetArrived(QStringList p_set);
    void                                frameArrived(JsonData p_frame);
    void                                promptArrived(QString p_prompt);
    void                                rawTextArrived(QString p_rawText);
    void                                typeArrived(QString p_type);
private slots:
    void                                jsonArrived();
    void                                metashellQuit();
};

#endif // METASHELLINTERPRETER_H
