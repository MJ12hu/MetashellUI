#ifndef PIECHARTCAPTIONS_H
#define PIECHARTCAPTIONS_H

#include <QWidget>

class PiechartCaptions : public QWidget
{
    Q_OBJECT
public:
    explicit PiechartCaptions(QWidget *parent = 0);
    ~PiechartCaptions();
    void                                addCaption(QColor p_color, QString p_caption);
    void                                clearCaptions();
protected:
    void                                paintEvent(QPaintEvent *p_event);
private:
    QVector<QPair<QColor, QString>>     m_captions;
signals:

public slots:

};

#endif // PIECHARTCAPTIONS_H
