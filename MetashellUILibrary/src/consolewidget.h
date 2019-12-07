#ifndef CONSOLEWIDGET_H
#define CONSOLEWIDGET_H

#include <QWidget>
#include <QScrollArea>
#include <QTimer>
#include <memory>
#include <QClipboard>

class ConsoleWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ConsoleWidget(QWidget *parent = 0);
    void                            setScrollBar(QScrollArea* p_area);
    void                            addAsInput(QString p_text);
    void                            addText(QString p_text);
    void                            addComment(QString p_text);
    void                            addError(QString p_text);
    void                            codeCompletionArrived(QStringList p_list);
    void                            promptArrived(QString p_prompt);
protected:
    bool                            event(QEvent *p_event);
    void                            keyPressEvent(QKeyEvent *p_event);
    void                            mousePressEvent(QMouseEvent *p_event);
    void                            mouseMoveEvent(QMouseEvent *p_event);
    void                            paintEvent(QPaintEvent *p_event);
    void                            resizeEvent(QResizeEvent *p_event);
private:
    enum LineType
    {
        Normal, Comment, Error
    };

    struct Line
    {
        QString         content;
        LineType        type;
    };

    struct Selection
    {
        int fromRow, fromChar;
        int toRow, toChar;
        int startingRow, startingChar;
    };

    struct TextPart
    {
        TextPart() {}
        TextPart(QString p_text, QColor p_color) : text(p_text), color(p_color) {}

        QString text;
        QColor color;
    };

    QVector<Line>                   m_content;
    QVector<QString>                m_history;
    QVector<QString>                m_future;
    QString                         m_prompt;
    QString                         m_lineEdit;
    int                             m_linePos;
    QScrollArea*                    m_scrollbar;
    QClipboard*                     m_clipBoard;
    LineType                        m_lastLineType;
    std::shared_ptr<QTimer>         m_promptTimer;
    bool                            m_paintCursor;
    bool                            m_showInputLine;
    float                           m_charHeight;
    float                           m_charWidth;
    bool                            m_pressedAnythingSinceLastTab;
    bool                            m_rebuildDisplayedText;
    bool                            m_scrollDown;
    QVector<QVector<TextPart>>      m_displayedText;
    int                             m_contentLines;
    Selection                       m_selection;


    void                            appendToHistory(QString p_text);
    QString                         joinLineText(QVector<TextPart> p_vector);
    int                             lineLength(QVector<TextPart> p_vector);
    void                            rebuildDisplayedText();
    void                            rebuildPromptText();
    void                            scrollDown();
signals:
    void                            sendCommand(QString p_command);
    void                            sendCodeCompletion(QString p_command);
private slots:
    void                            promptTimerTicked();
};

#endif // CONSOLEWIDGET_H
