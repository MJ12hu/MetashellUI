#ifndef PRAGMAWIDGET_H
#define PRAGMAWIDGET_H

#include <QWidget>

namespace Ui {
class PragmaWidget;
}

class PragmaWidget : public QWidget
{
    Q_OBJECT

public:
    explicit PragmaWidget(bool p_isPlugin, QWidget *parent = 0);
    ~PragmaWidget();

    QString                 askForParameter(const QString &p_parameterName);
private:
    Ui::PragmaWidget *ui;
    bool                    m_isPlugin;
signals:
    void                    sendCommand(QString p_command);
    void                    restartMetashell();
private slots:
    void                    helpPressed();
    void                    mdbPressed();
    void                    envPressed();
    void                    quitPressed();
    void                    reloadEnvPressed();
    void                    resetEnvPressed();
};

#endif // PRAGMAWIDGET_H
