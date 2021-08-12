#ifndef TEXTEDIT_H
#define TEXTEDIT_H

#include <QMainWindow>

class QAction;
class QComboBox;
class QFontComboBox;
class QTextEdit;
class QTextCharFormat;
class QPrinter;

class TextEdit : public QMainWindow
{
    Q_OBJECT

public:
    TextEdit(QWidget *parent = nullptr);
    ~TextEdit();

protected:
    void closeEvent(QCloseEvent *e) override;

private slots:
    void fileNew();
    void fileOpen();
    bool fileSave();
    bool fileSaveAs();
    void filePrint();
    void filePrintPreview();
    void filePrintPdf();

    void textBold();
    void textItalic();
    void textUnderline();
    void textAlign(QAction *a);
    void textColor();
    void textStyle(int styleIndex);
    void textFamily(const QString &f);
    void textSize(const QString &p);

    void currentCharFormatChanged(const QTextCharFormat &format);
    void cursorPositionChanged();
    void clipboardDataChanged();
    void printPreview(QPrinter *printer);
    void about();

private:
    void setupFileActions(); // 文件主菜单的实现函数
    void setupEditActions(); // 编辑主菜单的实现函数
    void setupTextActions(); // 格式主菜单的实现函数
    void setupHelpActions(); // 帮助主菜单的实现函数

    void setCurrentFileName(const QString &fileName);
                                 // 设置当前文件标题
    bool maybeSave();            // 关闭程序时的保存提醒
    bool load(const QString &f); // 文档加载函数

    void mergeFormatOnWordOrSelection(const QTextCharFormat &format);
    void fontChanged(const QFont &f);
    void colorChanged(const QColor &c);
    void alignmentChanged(Qt::Alignment a);

    QAction *actionNew;       // 文件菜单栏功能项
    QAction *actionOpen;
    QAction *actionSave;
    QAction *actionSaveAs;
    QAction *actionPrint;
    QAction *actionPrintPreview;
    QAction *actionExportPDF;
    QAction *actionQuit;

    QAction *actionUndo;      // 编辑菜单栏功能项
    QAction *actionRedo;
    QAction *actionCut;
    QAction *actionCopy;
    QAction *actionPaste;

    QAction *actionTextBold;  // 格式菜单栏功能项
    QAction *actionTextItalic;
    QAction *actionTextUnderline;
    QAction *actionAlignLeft;
    QAction *actionAlignCenter;
    QAction *actionAlignRight;
    QAction *actionAlignJustify;
    QAction *actionTextColor;

    QAction *actionAbout;     // 帮助菜单栏功能项
    QAction *actionQtAbout;

    QComboBox *comboStyle;    // 标题组合框
    QFontComboBox *comboFont; // 字体组合框
    QComboBox *comboSize;     // 字号组合框

    QString fileName;         // 当前文件标题名
    QTextEdit *textEdit;
};
#endif // TEXTEDIT_H
