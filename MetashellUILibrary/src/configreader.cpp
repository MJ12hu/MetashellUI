#include "configreader.h"
#include <QSettings>
#include <QFile>
#include <QFileDialog>
#include <QMessageBox>

ConfigReader* ConfigReader::m_privateInstance = nullptr;

ConfigReader* ConfigReader::instance()
{
    if(m_privateInstance == nullptr)
        m_privateInstance = new ConfigReader();
    return m_privateInstance;
}

ConfigReader::ConfigReader(QObject *parent) :
    QObject(parent)
{
}

void ConfigReader::readConfig(QString p_directory)
{
    p_directory.replace('/', QDir::separator());
    QSettings t_settings(p_directory + QDir::separator() + "MetashellUI.ini", QSettings::IniFormat);
    executablePath = t_settings.value("executablePath").toString();

    if(executablePath == "" || !QFile(executablePath).exists())
    {
        QMessageBox::information(0, "Could not find Metashell", "The Metashell's location is unknown, please locate it.");
        QString t_executable = QFileDialog::getOpenFileName(0, "Metashell execuatble", p_directory);
        if(t_executable != "")
            executablePath = t_executable;
    }
}

void ConfigReader::saveConfig(QString p_directory)
{
    p_directory.replace('/', QDir::separator());
    QSettings t_settings(p_directory + QDir::separator() + "MetashellUI.ini", QSettings::IniFormat);
    t_settings.setValue("executablePath", executablePath);
    t_settings.sync();
}
