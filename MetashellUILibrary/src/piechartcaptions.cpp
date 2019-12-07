#include "piechartcaptions.h"
#include <QPainter>

PiechartCaptions::PiechartCaptions(QWidget *parent) :
    QWidget(parent)
{
    setFixedHeight(25);
    setFixedWidth(1);
}

PiechartCaptions::~PiechartCaptions()
{

}

void PiechartCaptions::addCaption(QColor p_color, QString p_caption)
{
    m_captions.push_back(QPair<QColor, QString>(p_color, p_caption));
}

void PiechartCaptions::clearCaptions()
{
    m_captions.clear();
}

void PiechartCaptions::paintEvent(QPaintEvent *p_event)
{
    QPainter t_painter(this);
    QFont t_font("Monospace");
    t_font.setPointSize(9);

    QFontMetricsF t_fontMetrics(t_font);

    t_painter.setFont(t_font);

    int t_pos = 0;
    for(QPair<QColor, QString> it : m_captions)
    {
        t_painter.setBrush(it.first);
        t_painter.drawRect(t_pos, 5, 15, 15);
        t_pos += 20;

        float t_width = t_fontMetrics.width(it.second);
        t_painter.drawText(QRect(t_pos, 5, t_width, 15), it.second);
        t_pos += t_width + 5;
    }
    if(width() != t_pos)
        setFixedWidth(t_pos ? t_pos : 1);
}
