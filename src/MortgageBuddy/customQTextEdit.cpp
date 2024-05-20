#include "customQTextEdit.h"
#include <QKeyEvent>


CustomQTextEdit::CustomQTextEdit(QWidget *parent)
    : QTextEdit(parent)
{
}


/**
 * @brief Fix, adding the ability to use tab to move between input fields.
 * 
 * @author Rokas Baliutavičius
*/
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
