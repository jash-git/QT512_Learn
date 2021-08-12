#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QGroupBox>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QTextEdit>
#include <QDialogButtonBox>
#include <QMenuBar>
#include <QMenu>
#include <QAction>

class Dialog : public QDialog
{
    Q_OBJECT

public:
    Dialog(QWidget *parent = nullptr);
    ~Dialog();

private:
    void createMenu();
    void createHorizontalGroupBox();
    void createGridGroupBox();
    void createFormGroupBox();

    QGroupBox *horizontalGroupBox;
    QPushButton *buttons[4];
    QGroupBox *gridGroupBox;
    QLabel *labels[3];
    QLineEdit *lineEdits[3];
    QTextEdit *smallEditor;
    QGroupBox *formGroupBox;
    QTextEdit *bigEditor;

    QDialogButtonBox *buttonBox;
    QMenuBar *menuBar;
    QMenu *fileMenu;
    QAction *exitAction;
};
#endif // DIALOG_H
