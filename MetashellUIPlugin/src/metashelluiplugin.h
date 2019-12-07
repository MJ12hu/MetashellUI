#ifndef METASHELLUIPLUGIN_H
#define METASHELLUIPLUGIN_H

#include "metashelluiplugin_global.h"

#include <extensionsystem/iplugin.h>
#include <projectexplorer/project.h>
#include <projectexplorer/buildconfiguration.h>
#include <projectexplorer/buildstep.h>
#include <memory>

#include "metashelloutputwindow.h"
#include <thrift/protocol/TJSONProtocol.h>
#include <thrift/transport/TSocket.h>
#include <thrift/transport/TTransportUtils.h>
#include <thrift/transport/THttpClient.h>
#include "metashelluioptionspage.h"

namespace MetashellUIQtPlugin {
namespace Internal {

class MetashellUIPlugin : public ExtensionSystem::IPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.qt-project.Qt.QtCreatorPlugin" FILE "MetashellUIPlugin.json")

public:
    MetashellUIPlugin();
    ~MetashellUIPlugin();

    bool                                        initialize(const QStringList &arguments, QString *errorString);
    void                                        extensionsInitialized();
    ShutdownFlag                                aboutToShutdown();
private:
    std::shared_ptr<MetashellUIOptionsPage>     m_optionsPage;
    MetashellUIOutputWindow*                    m_window;
private slots:
};

} // namespace Internal
} // namespace CodeCheckerPlugin

#endif // METASHELLUIPLUGIN_H
