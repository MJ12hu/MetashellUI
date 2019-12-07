#ifndef METASHELLUIOPTIONSPAGE_H
#define METASHELLUIOPTIONSPAGE_H

#include <coreplugin/dialogs/ioptionspage.h>
#include "optionswidget.h"

namespace MetashellUIQtPlugin {
namespace Internal {
class MetashellUIOptionsPage : public Core::IOptionsPage
{
    Q_OBJECT
public:
    explicit MetashellUIOptionsPage(QObject *parent = nullptr);

    QWidget*        widget();
    void            apply(void);
    void            finish();
private:
    OptionsWidget*  m_widget;
signals:
    void            changeExecutablePath();
public slots:
};
}
}
#endif // METASHELLUIOPTIONSPAGE_H
