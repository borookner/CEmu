/* Inspired from a code in the Qt Examples - BSD License */

#ifndef LUAEDITOR_H
#define LUAEDITOR_H

#include <QtWidgets/QPlainTextEdit>
#include <QtCore/QObject>
#include <QtGui/QSyntaxHighlighter>
#include <QtGui/QTextCharFormat>

QT_BEGIN_NAMESPACE
    class QPaintEvent;
    class QResizeEvent;
    class QSize;
    class QWidget;
    class QTextDocument;
QT_END_NAMESPACE


class LuaHighlighter : public QSyntaxHighlighter
{
    Q_OBJECT

public:
    LuaHighlighter(QTextDocument *parent = 0);

protected:
    void highlightBlock(const QString &text) Q_DECL_OVERRIDE;

private:
    struct HighlightingRule
    {
        QRegExp pattern;
        QTextCharFormat format;
    };
    QVector<HighlightingRule> highlightingRules;

    QRegExp commentStartExpression;
    QRegExp commentEndExpression;

    QTextCharFormat keywordFormat;
    QTextCharFormat numberFormat;
    QTextCharFormat builtinFormat;
    QTextCharFormat literalFormat;
    QTextCharFormat cemuGlobalsFormat;
    QTextCharFormat singleLineCommentFormat;
    QTextCharFormat multiLineCommentFormat;
    QTextCharFormat quotationFormat;
    QTextCharFormat functionFormat;
};


class LuaEditor : public QPlainTextEdit
{
    Q_OBJECT

public:
    LuaEditor(QWidget *parent = 0);

    void lineNumberAreaPaintEvent(QPaintEvent *event);
    int lineNumberAreaWidth();

protected:
    void resizeEvent(QResizeEvent *event) Q_DECL_OVERRIDE;

private slots:
    void updateLineNumberAreaWidth(int newBlockCount);
    void highlightCurrentLine();
    void updateLineNumberArea(const QRect &, int);

private:
    QWidget *lineNumberArea;
    LuaHighlighter *highlighter;
};


class LuaLineNumberArea : public QWidget
{
public:
    LuaLineNumberArea(LuaEditor *editor) : QWidget(editor) {
        luaEditor = editor;
    }

    QSize sizeHint() const Q_DECL_OVERRIDE {
        return QSize(luaEditor->lineNumberAreaWidth(), 0);
    }

protected:
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE {
        luaEditor->lineNumberAreaPaintEvent(event);
    }

private:
    LuaEditor *luaEditor;
};

#endif
