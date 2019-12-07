#include "metashelluioptionspage.h"
#include <coreplugin/icore.h>

MetashellUIQtPlugin::Internal::MetashellUIOptionsPage::MetashellUIOptionsPage(QObject *parent)
{
    setId(Core::Id("MetashellUI.OptionsPage"));
    setDisplayName(tr("MetashellUI"));
    setCategory("I.C++");
}

QWidget *MetashellUIQtPlugin::Internal::MetashellUIOptionsPage::widget()
{
    m_widget = new OptionsWidget();
    m_widget->setupPath(Core::ICore::instance()->settings()->value("metashellExecutable", "metashell").toString());
    return m_widget;
}

void MetashellUIQtPlugin::Internal::MetashellUIOptionsPage::apply()
{
    if(m_widget)
    {
        Core::ICore::instance()->settings()->setValue("metashellExecutable", m_widget->getPath());
    }
}

void MetashellUIQtPlugin::Internal::MetashellUIOptionsPage::finish()
{
    m_widget = nullptr;
}
