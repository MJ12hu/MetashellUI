#include "piechartwidget.h"
#include <QPainter>

#define RANDOMCOLORSEED 1234

PiechartWidget::PiechartWidget(QWidget *parent) :
    QWidget(parent)
{
    m_gridLayout = std::make_shared<QGridLayout>(this);

    m_scrollArea = std::make_shared<QScrollArea>();
    m_scrollArea->setFixedHeight(50);
    m_scrollArea->setMinimumWidth(100);
    //m_scrollArea->setFixedWidth(300);
    m_scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_gridLayout->addWidget(m_scrollArea.get(), 1, 1, Qt::AlignBottom);

    m_piechartCaptions = std::make_shared<PiechartCaptions>(m_scrollArea.get());
    m_scrollArea->setWidget(m_piechartCaptions.get());
    m_scrollArea->setWidgetResizable(true);
}

PiechartWidget::~PiechartWidget()
{
    if(m_piechartCaptions != nullptr)
        m_piechartCaptions.reset();
}

void PiechartWidget::setData(JsonArray p_array)
{
    m_data = p_array;
    std::sort(m_data.begin(), m_data.end());
    std::reverse(m_data.begin(), m_data.end());

    m_piechartCaptions->clearCaptions();

    qsrand(RANDOMCOLORSEED);
    QColor t_color;
    for(JsonData it : m_data)
    {
        t_color = QColor(qrand() % 256, qrand() % 256, qrand() % 256);
        m_piechartCaptions->addCaption(t_color, it.name);
    }
    m_piechartCaptions->repaint();
    //m_scrollArea->repaint();
    repaint();
}

void PiechartWidget::paintEvent(QPaintEvent *p_event)
{
    QPainter t_painter(this);
    int t_scrollbarheight = m_scrollArea->height() + 25;
    int t_min = (width() < height() - t_scrollbarheight ? width() : height() - t_scrollbarheight);

    QRectF t_rect((width() - t_min) / 2, (height() - t_scrollbarheight - t_min) / 2, t_min, t_min);

    double t_sum = 0;
    for(JsonData it : m_data)
    {
        double t_toadd = it.timeTaken;
        if(t_toadd <= 0)
            t_toadd = 0.00001;
        t_sum += t_toadd;
    }

    double t_currentangle = 0;

    QColor t_color;

    qsrand(RANDOMCOLORSEED);
    for(JsonData it : m_data)
    {
        double t_current = it.timeTaken;
        if(t_current <= 0)
            t_current = 0.00001;
        t_color = QColor(qrand() % 256, qrand() % 256, qrand() % 256);
        t_painter.setBrush(t_color);
        t_painter.drawPie(t_rect, t_currentangle / t_sum * 360 * 16, t_current / t_sum * 360 * 16);
        t_currentangle += t_current;
    }
    QWidget::paintEvent(p_event);
}
