#ifndef OPTIONSWIDGET_H
#define OPTIONSWIDGET_H

#include <QWidget>

namespace Ui {
class OptionsWidget;
}

class OptionsWidget : public QWidget
{
    Q_OBJECT

public:
    explicit OptionsWidget(QWidget *parent = nullptr);
    ~OptionsWidget();

    void                setupPath(const QString &p_path);
    QString             getPath();
private:
    Ui::OptionsWidget*  ui;
private slots:
    void                onSearchFilePath();
};

#endif // OPTIONSWIDGET_H
