#ifndef CONFIGREADER_H
#define CONFIGREADER_H

#include <QObject>

class ConfigReader : public QObject
{
    Q_OBJECT
public:
    static ConfigReader* instance();

    explicit ConfigReader(QObject *parent = 0);
    void    readConfig(QString p_directory);
    void    saveConfig(QString p_directory);

    QString executablePath;
private:
    static ConfigReader* m_privateInstance;
signals:

public slots:

};

#endif // CONFIGREADER_H
