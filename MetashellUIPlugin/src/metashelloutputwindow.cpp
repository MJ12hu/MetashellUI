#include "metashelloutputwindow.h"
#include <coreplugin/icore.h>

MetashellUIQtPlugin::Internal::MetashellUIOutputWindow::MetashellUIOutputWindow()
{

}

QWidget *MetashellUIQtPlugin::Internal::MetashellUIOutputWindow::outputWidget(QWidget *p_parent)
{
    m_scrollArea = new QScrollArea(p_parent);

    m_outputWidget = new MetashellMainWindow(true, m_scrollArea);
    m_scrollArea->setWidgetResizable(true);
    m_scrollArea->setWidget(m_outputWidget);
    m_outputWidget->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    m_outputWidget->setExecutable(Core::ICore::instance()->settings()->value("metashellExecutable", "metashell").toString());
    m_outputWidget->startInterpreter();
    return m_scrollArea;
}

QList<QWidget *> MetashellUIQtPlugin::Internal::MetashellUIOutputWindow::toolBarWidgets() const
{
    return QList<QWidget*>();
}

QString MetashellUIQtPlugin::Internal::MetashellUIOutputWindow::displayName() const
{
    return tr("Metashell");
}

int MetashellUIQtPlugin::Internal::MetashellUIOutputWindow::priorityInStatusBar() const
{
    return 7;
}

void MetashellUIQtPlugin::Internal::MetashellUIOutputWindow::clearContents()
{

}

void MetashellUIQtPlugin::Internal::MetashellUIOutputWindow::visibilityChanged(bool visible)
{

}

bool MetashellUIQtPlugin::Internal::MetashellUIOutputWindow::canFocus() const
{
    return false;
}

bool MetashellUIQtPlugin::Internal::MetashellUIOutputWindow::hasFocus() const
{
    return false;
}

void MetashellUIQtPlugin::Internal::MetashellUIOutputWindow::setFocus()
{

}

bool MetashellUIQtPlugin::Internal::MetashellUIOutputWindow::canNext() const
{
    return false;
}

bool MetashellUIQtPlugin::Internal::MetashellUIOutputWindow::canPrevious() const
{
    return false;
}

void MetashellUIQtPlugin::Internal::MetashellUIOutputWindow::goToNext()
{

}

void MetashellUIQtPlugin::Internal::MetashellUIOutputWindow::goToPrev()
{

}

bool MetashellUIQtPlugin::Internal::MetashellUIOutputWindow::canNavigate() const
{
    return false;
}

void MetashellUIQtPlugin::Internal::MetashellUIOutputWindow::executablePathChanged()
{
    m_outputWidget->setExecutable(Core::ICore::instance()->settings()->value("metashellExecutable", "metashell").toString());
}
