#ifndef CODECHECKEROUTPUTWINDOW_H
#define CODECHECKEROUTPUTWINDOW_H

#include <coreplugin/ioutputpane.h>
#include "metashellmainwindow.h"

namespace MetashellUIQtPlugin {
namespace Internal {

class MetashellUIOutputWindow : public Core::IOutputPane
{
    Q_OBJECT
public:
    MetashellUIOutputWindow();

    QWidget *outputWidget(QWidget *p_parent);

    QList<QWidget *>        toolBarWidgets() const override;
    QString                 displayName() const override;
    int                     priorityInStatusBar() const override;
    void                    clearContents() override;
    void                    visibilityChanged(bool visible) override;
    bool                    canFocus() const override;
    bool                    hasFocus() const override;
    void                    setFocus() override;

    bool                    canNext() const override;
    bool                    canPrevious() const override;
    void                    goToNext() override;
    void                    goToPrev() override;
    bool                    canNavigate() const override;

private:
    MetashellMainWindow*    m_outputWidget;
    QScrollArea*            m_scrollArea;
public slots:
    void                    executablePathChanged();
};
}
}

#endif // CODECHECKEROUTPUTWINDOW_H
