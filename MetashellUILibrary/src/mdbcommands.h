#ifndef MDBCOMMANDS_H
#define MDBCOMMANDS_H

#include <QWidget>

namespace Ui {
class MDBCommands;
}

class MDBCommands : public QWidget
{
    Q_OBJECT

public:
    explicit MDBCommands(QWidget *parent = 0);
    ~MDBCommands();

private:
    Ui::MDBCommands *ui;

    QString                 askForParameter(const QString &p_parameterName);
signals:
    void                    sendCommand(QString p_command);
private slots:
    void                    backtracePressed();
    void                    breakPressed();
    void                    continuePressed();
    void                    evaluatePressed();
    void                    finishPressed();
    void                    forwardTracePressed();
    void                    framePressed();
    void                    helpPressed();
    void                    nextPressed();
    void                    quitPressed();
    void                    rBreakPressed();
    void                    stepPressed();
};

#endif // MDBCOMMANDS_H
