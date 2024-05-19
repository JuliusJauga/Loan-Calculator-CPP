#include "customQTextEdit.h"
#include <QKeyEvent>

// Implementation for CustomQTextEdit
CustomQTextEdit::CustomQTextEdit(QWidget *parent)
    : QTextEdit(parent)
{
}

void CustomQTextEdit::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Tab)
    {
        event->ignore();
        focusNextChild();
    }
    else
    {
        QTextEdit::keyPressEvent(event);
    }
}
