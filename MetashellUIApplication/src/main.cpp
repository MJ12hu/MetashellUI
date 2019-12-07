#include "metashellmainwindow.h"
#include <QApplication>
#include <QDir>
#include <QMessageBox>
#include "configreader.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QString t_executable;
    ConfigReader::instance()->readConfig(a.applicationDirPath());

    t_executable = ConfigReader::instance()->executablePath;
    if(t_executable == "")
    {
        QMessageBox::warning(0, "Could not find Metashell", "The Metashell's location is unknown.");
        return 1;
    }

    ConfigReader::instance()->saveConfig(a.applicationDirPath());

    MetashellMainWindow w(false);
    w.setExecutable(t_executable);
    w.startInterpreter();
    w.show();

    return a.exec();
}
