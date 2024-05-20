
/**
 * @file customQTextEdit.cpp
 * @brief Implementation file for the CustomQTextEdit class.
 * 
 * This file contains the implementation of the CustomQTextEdit class, which is a custom subclass of QTextEdit, meant to allow movement between input fields using a tab press.
 * 
 * @author Rokas Baliutavičius
 */

#include "customQTextEdit.h"
#include <QKeyEvent>

/**
 * @brief Constructor for the CustomQTextEdit class.
*/
CustomQTextEdit::CustomQTextEdit(QWidget *parent)
    : QTextEdit(parent)
{
}


/**
 * @brief Overrides the keyPressEvent function to handle the Tab key press event.
 * 
 * This function is called when a key press event occurs. If the Tab key is pressed, it ignores the event and
 * focuses on the next child widget, allowing the user to move between input fields using the Tab key.
 * If any other key is pressed, it calls the base class's keyPressEvent function to handle the event.
 * 
 * @param event The key press event.
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
