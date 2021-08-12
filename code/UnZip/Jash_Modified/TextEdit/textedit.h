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
    void setupFileActions(); // 檔主功能表的實現函數
    void setupEditActions(); // 編輯主功能表的實現函數
    void setupTextActions(); // 格式主功能表的實現函數
    void setupHelpActions(); // 説明主功能表的實現函數

    void setCurrentFileName(const QString &fileName);
                                 // 設置當前文件標題
    bool maybeSave();            // 關閉程式時的保存提醒
    bool load(const QString &f); // 文檔載入函數

    void mergeFormatOnWordOrSelection(const QTextCharFormat &format);
    void fontChanged(const QFont &f);
    void colorChanged(const QColor &c);
    void alignmentChanged(Qt::Alignment a);

    QAction *actionNew;       // 檔功能表列功能項
    QAction *actionOpen;
    QAction *actionSave;
    QAction *actionSaveAs;
    QAction *actionPrint;
    QAction *actionPrintPreview;
    QAction *actionExportPDF;
    QAction *actionQuit;

    QAction *actionUndo;      // 編輯功能表列功能項
    QAction *actionRedo;
    QAction *actionCut;
    QAction *actionCopy;
    QAction *actionPaste;

    QAction *actionTextBold;  // 格式功能表列功能項
    QAction *actionTextItalic;
    QAction *actionTextUnderline;
    QAction *actionAlignLeft;
    QAction *actionAlignCenter;
    QAction *actionAlignRight;
    QAction *actionAlignJustify;
    QAction *actionTextColor;

    QAction *actionAbout;     // 幫助功能表列功能項
    QAction *actionQtAbout;

    QComboBox *comboStyle;    // 標題下拉式列示方塊
    QFontComboBox *comboFont; // 字體下拉式列示方塊
    QComboBox *comboSize;     // 字型大小下拉式列示方塊

    QString fileName;         // 當前文件標題名
    QTextEdit *textEdit;
};
#endif // TEXTEDIT_H
