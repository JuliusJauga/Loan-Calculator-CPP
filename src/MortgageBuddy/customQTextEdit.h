#ifndef CUSTOMQTEXTEDIT_H
#define CUSTOMQTEXTEDIT_H

#include <QTextEdit>
#include <QPushButton>

class CustomQTextEdit : public QTextEdit
{
    Q_OBJECT

public:
    explicit CustomQTextEdit(QWidget *parent = nullptr);

protected:
    void keyPressEvent(QKeyEvent *event) override;
};

#endif // CUSTOM_WIDGETS_H
