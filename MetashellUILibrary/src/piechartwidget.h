#ifndef PIECHARTWIDGET_H
#define PIECHARTWIDGET_H

#include <QWidget>
#include <QScrollArea>
#include <QGridLayout>
#include <memory>
#include <DataTypes/jsondata.hpp>
#include <piechartcaptions.h>

class PiechartWidget : public QWidget
{
    Q_OBJECT
public:
    explicit PiechartWidget(QWidget *parent = 0);
    ~PiechartWidget();
    void                                    setData(JsonArray p_array);
protected:
    void                                    paintEvent(QPaintEvent *p_event);

private:
    JsonArray                               m_data;
    std::shared_ptr<PiechartCaptions>       m_piechartCaptions;
    std::shared_ptr<QScrollArea>            m_scrollArea;
    std::shared_ptr<QGridLayout>            m_gridLayout;
signals:

public slots:

};

#endif // PIECHARTWIDGET_H
