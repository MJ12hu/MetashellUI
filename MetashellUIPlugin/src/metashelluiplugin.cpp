#include "metashelluiplugin.h"
#include "metashelluipluginconstants.h"

#include <coreplugin/icore.h>
#include <coreplugin/icontext.h>
#include <extensionsystem/pluginmanager.h>

#include <QtPlugin>

using namespace MetashellUIQtPlugin::Internal;

MetashellUIPlugin::MetashellUIPlugin()
{
    // Create your members
}

MetashellUIPlugin::~MetashellUIPlugin()
{
    // Unregister objects from the plugin manager's object pool
    // Delete members
}

bool MetashellUIPlugin::initialize(const QStringList &arguments, QString *errorString)
{
    // Register objects in the plugin manager's object pool
    // Load settings
    // Add actions to menus
    // Connect to other plugins' signals
    // In the initialize function, a plugin can be sure that the plugins it
    // depends on have initialized their members.

    Q_UNUSED(arguments)
    Q_UNUSED(errorString)

    m_window = new MetashellUIOutputWindow();
    ExtensionSystem::PluginManager::addObject(m_window);
    m_optionsPage = std::make_shared<MetashellUIOptionsPage>();
    connect(m_optionsPage.get(), &MetashellUIOptionsPage::changeExecutablePath, m_window, &MetashellUIOutputWindow::executablePathChanged);

    return true;
}

void MetashellUIPlugin::extensionsInitialized()
{
    // Retrieve objects from the plugin manager's object pool
    // In the extensionsInitialized function, a plugin can be sure that all
    // plugins that depend on it are completely initialized.
}

ExtensionSystem::IPlugin::ShutdownFlag MetashellUIPlugin::aboutToShutdown()
{
    ExtensionSystem::PluginManager::removeObject(m_window);
    delete m_window;
    // Save settings
    // Disconnect from signals that are not needed during shutdown
    // Hide UI (if you add UI that is not in the main window directly)
    return SynchronousShutdown;
}
