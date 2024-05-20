
/**
 * @file customQTextEdit.h
 * @brief Header file for the CustomQTextEdit class.
 * 
 * This file contains the definition of the CustomQTextEdit class, which is a custom subclass of QTextEdit, meant to allow movement between input fields using a tab press.
 * 
 * @author Rokas Baliutavičius
 */

#ifndef CUSTOMQTEXTEDIT_H
#define CUSTOMQTEXTEDIT_H

#include <QTextEdit>
#include <QPushButton>

/**
 * @brief Constructor for the CustomQTextEdit class.
*/
class CustomQTextEdit : public QTextEdit
{
    Q_OBJECT

public:
    /**
     * @brief Constructs a CustomQTextEdit object.
     * 
     * @param parent The parent widget.
     */
    explicit CustomQTextEdit(QWidget *parent = nullptr);

protected:
    /**
     * @brief Overrides the keyPressEvent() function to handle key events.
     * 
     * @param event The key event.
     */
    void keyPressEvent(QKeyEvent *event) override;
};

#endif // CUSTOM_WIDGETS_H
