#include "textedit.h"
#include "aboutdlg.h"

#include <QApplication>
#include <QAction>
#include <QClipboard>
#include <QColorDialog>
#include <QComboBox>
#include <QFile>
#include <QFileDialog>
#include <QFileInfo>
#include <QFontComboBox>
#include <QFontDatabase>
#include <QMenu>
#include <QMenuBar>
#include <QTextEdit>
#include <QTextCharFormat>
#include <QTextCodec>
#include <QStatusBar>
#include <QTextCursor>
#include <QTextDocumentWriter>
#include <QTextList>
#include <QToolBar>
#include <QCloseEvent>
#include <QMessageBox>
#include <QMimeData>
#include <QPrinter>
#include <QPrintDialog>
#include <QPrintPreviewDialog>

const QString rsrcPath = ":/myImages/images";

TextEdit::TextEdit(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle(tr("文字編輯器")); // 設置應用程式標題
    setMinimumSize(QSize(1024, 768));
    setWindowIcon(QIcon(rsrcPath + "/Qt_logo.png"));

    textEdit = new QTextEdit(this);
    connect(textEdit, &QTextEdit::currentCharFormatChanged, this, &TextEdit::currentCharFormatChanged);
    connect(textEdit, &QTextEdit::cursorPositionChanged, this, &TextEdit::cursorPositionChanged);
    setCentralWidget(textEdit);

//    setToolButtonStyle(Qt::ToolButtonFollowStyle);
    setupFileActions();
    setupEditActions();
    setupTextActions();
    setupHelpActions();
    statusBar()->showMessage(tr("就緒"));

    QFont textFont("Helvetica");
    textFont.setStyleHint(QFont::SansSerif);
    textEdit->setFont(textFont);
    fontChanged(textEdit->font());
    colorChanged(textEdit->textColor());
    alignmentChanged(textEdit->alignment());

    connect(textEdit->document(), &QTextDocument::modificationChanged,
            this, &QWidget::setWindowModified);
    connect(textEdit->document(), &QTextDocument::modificationChanged,
            actionSave, &QAction::setEnabled); // 根據文檔狀態設置“保存”按鈕的啟動狀態
    connect(textEdit->document(), &QTextDocument::undoAvailable,
            actionUndo, &QAction::setEnabled); //
    connect(textEdit->document(), &QTextDocument::redoAvailable,
            actionRedo, &QAction::setEnabled);

//    setWindowModified(textEdit->document()->isModified());
    actionSave->setEnabled(textEdit->document()->isModified());
    actionUndo->setEnabled(textEdit->document()->isUndoAvailable());
    actionRedo->setEnabled(textEdit->document()->isRedoAvailable());

    actionCut->setEnabled(false);
    connect(textEdit, &QTextEdit::copyAvailable, actionCut, &QAction::setEnabled);
    actionCopy->setEnabled(false);
    connect(textEdit, &QTextEdit::copyAvailable, actionCopy, &QAction::setEnabled);
    connect(QApplication::clipboard(), &QClipboard::dataChanged,
            this, &TextEdit::clipboardDataChanged);

    textEdit->setFocus(); // 將鍵盤輸入焦點賦予當前視窗的文本編輯方塊
    setCurrentFileName(QString());
}

TextEdit::~TextEdit()
{
}

void TextEdit::closeEvent(QCloseEvent *e)
{
    if (maybeSave())
        e->accept();
    else
        e->ignore();
}

void TextEdit::fileNew()
{
//    // 第一種方法
//    if (maybeSave()) {
//        textEdit->clear();
//        setCurrentFileName(QString());
//    }

    // 第二種方法
    TextEdit *newTextEdit = new TextEdit;
    newTextEdit->show();
}

void TextEdit::fileOpen()
{
    QFileDialog fileDialog(this, tr("打開文件..."));
    fileDialog.setAcceptMode(QFileDialog::AcceptOpen);
    fileDialog.setFileMode(QFileDialog::ExistingFile);
    fileDialog.setMimeTypeFilters(QStringList() << "text/html" << "text/plain");
    if (fileDialog.exec() != QDialog::Accepted)
        return;
    const QString fn = fileDialog.selectedFiles().first();
    if (load(fn))
        statusBar()->showMessage(tr("已打開 \"%1\"").arg(QDir::toNativeSeparators(fn)));
    else
        statusBar()->showMessage(tr("未能打開 \"%1\"").arg(QDir::toNativeSeparators(fn)));
}

bool TextEdit::fileSave()
{
    // 若未命名檔案名或檔案名者以 ':/' 開頭，則直接執行另存為操作
    if (fileName.isEmpty())
        return fileSaveAs();
    if (fileName.startsWith(QStringLiteral(":/")))
        return fileSaveAs();

    QTextDocumentWriter writer(fileName);
    bool success = writer.write(textEdit->document());
    // 在狀態列顯示是否保存成功的提示資訊
    if (success) {
        textEdit->document()->setModified(false);
        statusBar()->showMessage(tr("已寫入 \"%1\"")
                                 .arg(QDir::toNativeSeparators(fileName)));
    } else {
        statusBar()->showMessage(tr("未能寫入 \"%1\"")
                                 .arg(QDir::toNativeSeparators(fileName)));
    }
    return success;
}

bool TextEdit::fileSaveAs()
{
    QFileDialog fileDialog(this, tr("另存為...")); // 新建標準檔對話方塊
    fileDialog.setAcceptMode(QFileDialog::AcceptSave);
    QStringList mimeTypes;
    mimeTypes << "application/vnd.oasis.opendocument.text" << "text/html" << "text/plain";
    fileDialog.setMimeTypeFilters(mimeTypes); // 從 MIME 類型列表中設置檔對話方塊中使用的篩檢程式
    fileDialog.setDefaultSuffix("odt");       // 如果未指定其他尾碼，則將此尾碼添加到檔案名中
    if (fileDialog.exec() != QDialog::Accepted)
        return false;
    const QString fn = fileDialog.selectedFiles().first(); // 包含對話方塊中所選檔的絕對路徑的第一個字串
    setCurrentFileName(fn);
    return fileSave();
}

void TextEdit::filePrint()
{
    QPrinter printer(QPrinter::HighResolution); // 新建列印物件，並設置列印模式
    QPrintDialog *dlg = new QPrintDialog(&printer, this);
//    if (textEdit->textCursor().hasSelection())
//        dlg->addEnabledOption(QAbstractPrintDialog::PrintSelection);
//    dlg->setWindowTitle(tr("列印文檔"));
    if (dlg->exec() == QDialog::Accepted)
        textEdit->print(&printer);
    delete dlg;
}

void TextEdit::filePrintPreview()
{
    QPrinter printer(QPrinter::HighResolution);
    QPrintPreviewDialog preview(&printer, this); // 新建預覽列印對話方塊
    connect(&preview, &QPrintPreviewDialog::paintRequested, this, &TextEdit::printPreview);
    preview.exec(); // 執行預覽列印操作
}

void TextEdit::filePrintPdf()
{
    QFileDialog fileDialog(this, tr("輸出為 PDF"));
    fileDialog.setAcceptMode(QFileDialog::AcceptSave);
    fileDialog.setMimeTypeFilters(QStringList("application/pdf"));
    fileDialog.setDefaultSuffix("pdf");
    if (fileDialog.exec() != QDialog::Accepted)
        return;
    QString fileName = fileDialog.selectedFiles().first();
    QPrinter printer(QPrinter::HighResolution);
    printer.setOutputFormat(QPrinter::PdfFormat); // 指定輸出格式
    printer.setOutputFileName(fileName);
    textEdit->document()->print(&printer);
    statusBar()->showMessage(tr("輸出為 \"%1\"")
                             .arg(QDir::toNativeSeparators(fileName)));
}

void TextEdit::textBold()
{
    QTextCharFormat fmt;
    fmt.setFontWeight(actionTextBold->isChecked() ? QFont::Bold : QFont::Normal);
    mergeFormatOnWordOrSelection(fmt);
}

void TextEdit::textItalic()
{
    QTextCharFormat fmt;
    fmt.setFontItalic(actionTextItalic->isChecked());
    mergeFormatOnWordOrSelection(fmt);
}

void TextEdit::textUnderline()
{
    QTextCharFormat fmt;
    fmt.setFontUnderline(actionTextUnderline->isChecked());
    mergeFormatOnWordOrSelection(fmt);
}

void TextEdit::textAlign(QAction *a)
{
    if (a == actionAlignLeft)
        textEdit->setAlignment(Qt::AlignLeft | Qt::AlignAbsolute);
    else if (a == actionAlignCenter)
        textEdit->setAlignment(Qt::AlignHCenter);
    else if (a == actionAlignRight)
        textEdit->setAlignment(Qt::AlignRight | Qt::AlignAbsolute);
    else if (a == actionAlignJustify)
        textEdit->setAlignment(Qt::AlignJustify);
}

void TextEdit::textColor()
{
    QColor col = QColorDialog::getColor(textEdit->textColor(), this);
    if (!col.isValid())
        return;
    QTextCharFormat fmt;
    fmt.setForeground(col);
    mergeFormatOnWordOrSelection(fmt);
    colorChanged(col);
}

void TextEdit::textStyle(int styleIndex)
{
    QTextCursor cursor = textEdit->textCursor(); // 獲得文本編輯方塊的 QTextCursor 物件指標
    QTextListFormat::Style style = QTextListFormat::ListStyleUndefined;

    switch (styleIndex) { // 提供了 8 種文本排序的方式
    case 1:
        style = QTextListFormat::ListDisc;
        break;
    case 2:
        style = QTextListFormat::ListCircle;
        break;
    case 3:
        style = QTextListFormat::ListSquare;
        break;
    case 4:
        style = QTextListFormat::ListDecimal;
        break;
    case 5:
        style = QTextListFormat::ListLowerAlpha;
        break;
    case 6:
        style = QTextListFormat::ListUpperAlpha;
        break;
    case 7:
        style = QTextListFormat::ListLowerRoman;
        break;
    case 8:
        style = QTextListFormat::ListUpperRoman;
        break;
    default:
        break;
    }

    cursor.beginEditBlock(); // 設置縮進值

    QTextBlockFormat blockFmt = cursor.blockFormat();

    if (style == QTextListFormat::ListStyleUndefined) {
        blockFmt.setObjectIndex(-1);
        int headingLevel = styleIndex >= 9 ? styleIndex - 9 + 1 : 0; // H1 to H6, or Standard
        blockFmt.setHeadingLevel(headingLevel);
        cursor.setBlockFormat(blockFmt);

        int sizeAdjustment = headingLevel ? 4 - headingLevel : 0; // H1 to H6: +3 to -2
        QTextCharFormat fmt;
        fmt.setFontWeight(headingLevel ? QFont::Bold : QFont::Normal);
        fmt.setProperty(QTextFormat::FontSizeAdjustment, sizeAdjustment);
        cursor.select(QTextCursor::LineUnderCursor);
        cursor.mergeCharFormat(fmt);
        textEdit->mergeCurrentCharFormat(fmt);
    } else {
        QTextListFormat listFmt;
        if (cursor.currentList()) {
            listFmt = cursor.currentList()->format();
        } else {
            listFmt.setIndent(blockFmt.indent() + 1);
            blockFmt.setIndent(0);
            cursor.setBlockFormat(blockFmt);
        }
        listFmt.setStyle(style);
        cursor.createList(listFmt);
    }

    cursor.endEditBlock();
}

void TextEdit::textFamily(const QString &f)
{
    QTextCharFormat fmt;
    fmt.setFontFamily(f);
    mergeFormatOnWordOrSelection(fmt);
}

void TextEdit::textSize(const QString &p)
{
    qreal pointSize = p.toDouble();
    if (p.toFloat() > 0) {
        QTextCharFormat fmt;
        fmt.setFontPointSize(pointSize);
        mergeFormatOnWordOrSelection(fmt);
    }
}

void TextEdit::currentCharFormatChanged(const QTextCharFormat &format)
{
    fontChanged(format.font());
    colorChanged(format.foreground().color());
}

void TextEdit::cursorPositionChanged()
{
    alignmentChanged(textEdit->alignment());
    QTextList *list = textEdit->textCursor().currentList();
    if (list) {
        switch (list->format().style()) {
        case QTextListFormat::ListDisc:
            comboStyle->setCurrentIndex(1);
            break;
        case QTextListFormat::ListCircle:
            comboStyle->setCurrentIndex(2);
            break;
        case QTextListFormat::ListSquare:
            comboStyle->setCurrentIndex(3);
            break;
        case QTextListFormat::ListDecimal:
            comboStyle->setCurrentIndex(4);
            break;
        case QTextListFormat::ListLowerAlpha:
            comboStyle->setCurrentIndex(5);
            break;
        case QTextListFormat::ListUpperAlpha:
            comboStyle->setCurrentIndex(6);
            break;
        case QTextListFormat::ListLowerRoman:
            comboStyle->setCurrentIndex(7);
            break;
        case QTextListFormat::ListUpperRoman:
            comboStyle->setCurrentIndex(8);
            break;
        default:
            comboStyle->setCurrentIndex(-1);
            break;
        }
    } else {
        int headingLevel = textEdit->textCursor().blockFormat().headingLevel();
        comboStyle->setCurrentIndex(headingLevel ? headingLevel + 8 : 0);
    }
}

void TextEdit::clipboardDataChanged()
{
    if (const QMimeData *md = QApplication::clipboard()->mimeData())
        actionPaste->setEnabled(md->hasText());
}

void TextEdit::printPreview(QPrinter *printer)
{
    textEdit->print(printer);
}

void TextEdit::about()
{
    QString str = tr("該示例演示了 Qt 文本編輯功能的應用，\n"
                     "並提供了示例文檔供您試用。\n\n"
                     "想瞭解並獲取的更多，歡迎關注微信公\n"
                     "眾號：Qt 學習 (ID: Qt_Learning )。");

    // 1
//    QMessageBox::about(this, tr("關於"), str);

    // 2
//    QMessageBox customMsgBox;
//    customMsgBox.setWindowTitle(tr("自訂幫助對話方塊"));
//    customMsgBox.addButton(QMessageBox::Ok); // 設置自訂説明對話方塊的按鈕
//    customMsgBox.setText(str);               // 設置自訂説明對話方塊中顯示的內容
//    QPixmap pix(rsrcPath + "/Qt_logo.png");
//    customMsgBox.setIconPixmap(pix.scaled(QSize(128, 128))); // 設置自訂説明對話框圖標
//    customMsgBox.exec();                                     // 顯示此自訂説明對話方塊

    // 3
    AboutDlg *aboutDlg = new AboutDlg();
    aboutDlg->setModal(true);
    aboutDlg->show();
}

void TextEdit::setupFileActions()
{
    // 檔主菜單動作集
    actionNew = new QAction(QIcon(rsrcPath + "/filenew.png"),  tr("新建(&N)"), this);
    actionNew->setShortcut(tr("Ctrl+N"));
    actionNew->setToolTip(tr("新建"));
    actionNew->setStatusTip(tr("創建一個新文檔"));
    connect(actionNew, &QAction::triggered, this, &TextEdit::fileNew);

    actionOpen = new QAction(QIcon(rsrcPath + "/fileopen.png"), tr("打開(&O)..."), this);
    actionOpen->setShortcut(tr("Ctrl+O"));
    actionOpen->setToolTip(tr("打開"));
    actionOpen->setStatusTip(tr("打開已存在的文檔"));
    connect(actionOpen, &QAction::triggered, this, &TextEdit::fileOpen);

    actionSave = new QAction(QIcon(rsrcPath + "/filesave.png"), tr("保存(&S)"), this);
    actionSave->setShortcut(tr("Ctrl+S"));
    actionSave->setToolTip(tr("保存"));
    actionSave->setStatusTip(tr("將當前文檔存檔"));
    connect(actionSave, &QAction::triggered, this, &TextEdit::fileSave);

    actionSaveAs = new QAction(tr("另存為(&A)..."), this);
    actionSaveAs->setStatusTip(tr("以一個新名字保存文檔"));
    connect(actionSaveAs, &QAction::triggered, this, &TextEdit::fileSaveAs);

    actionPrint = new QAction(QIcon(rsrcPath + "/fileprint.png"), tr("列印(&P)..."), this);
    actionPrint->setShortcut(tr("Ctrl+P"));
    actionPrint->setToolTip(tr("列印"));
    actionPrint->setStatusTip(tr("列印文檔"));
    connect(actionPrint, &QAction::triggered, this, &TextEdit::filePrint);

    actionPrintPreview = new QAction(tr("預覽列印..."), this);
    actionPrintPreview->setStatusTip(tr("預覽列印效果"));
    connect(actionPrintPreview, &QAction::triggered, this, &TextEdit::filePrintPreview);

    actionExportPDF = new QAction(QIcon(rsrcPath + "/exportpdf.png"), tr("輸出為 PDF(&E)..."), this);
    actionExportPDF->setShortcut(tr("Ctrl+D"));
    actionExportPDF->setToolTip(tr("輸出為 PDF"));
    actionExportPDF->setStatusTip(tr("將文檔匯出為 PDF 格式"));
    connect(actionExportPDF, &QAction::triggered, this, &TextEdit::filePrintPdf);

    actionQuit = new QAction(tr("退出(&Q)"), this);
    actionQuit->setShortcut(tr("Ctrl+Q"));
    actionQuit->setStatusTip(tr("退出應用程式"));
    connect(actionQuit, &QAction::triggered, this, &QWidget::close);

    // 檔主菜單
    QMenu *menu = menuBar()->addMenu(tr("文件(&F)"));
    menu->addAction(actionNew);
    menu->addAction(actionOpen);
    menu->addSeparator();
    menu->addAction(actionSave);
    menu->addAction(actionSaveAs);
    menu->addSeparator();
    menu->addAction(actionPrint);
    menu->addAction(actionPrintPreview);
    menu->addAction(actionExportPDF);
    menu->addSeparator();
    menu->addAction(actionQuit);

    // 文件工具條
    QToolBar *fileToolbar = addToolBar(tr("文件"));
    fileToolbar->addAction(actionNew);
    fileToolbar->addAction(actionOpen);
    fileToolbar->addAction(actionSave);
    fileToolbar->addSeparator();
    fileToolbar->addAction(actionPrint);
    fileToolbar->addAction(actionExportPDF);
}

void TextEdit::setupEditActions()
{
    // 編輯主功能表動作集
    actionUndo = new QAction(QIcon(rsrcPath + "/editundo.png"), tr("撤銷(&U)"), this);
    actionUndo->setShortcut(tr("Ctrl+Z"));
    actionUndo->setToolTip(tr("撤銷"));
    actionUndo->setStatusTip(tr("撤銷當前操作"));
    connect(actionUndo, &QAction::triggered, textEdit, &QTextEdit::undo);

    actionRedo = new QAction(QIcon(rsrcPath + "/editredo.png"), tr("重做(&R)"), this);
    actionRedo->setShortcut(tr("Ctrl+Y"));
    actionRedo->setToolTip(tr("重做"));
    actionRedo->setStatusTip(tr("恢復之前操作"));
    connect(actionRedo, &QAction::triggered, textEdit, &QTextEdit::redo);

    actionCut = new QAction(QIcon(rsrcPath + "/editcut.png"), tr("剪切(&T)"), this);
    actionCut->setShortcut(tr("Ctrl+X"));
    actionCut->setToolTip(tr("剪切"));
    actionCut->setStatusTip(tr("從文檔中剪切選中內容並將其放入剪貼板"));
    connect(actionCut, &QAction::triggered, textEdit, &QTextEdit::cut);

    actionCopy = new QAction(QIcon(rsrcPath + "/editcopy.png"), tr("複製(&C)"), this);
    actionCopy->setShortcut(tr("Ctrl+C"));
    actionCopy->setToolTip(tr("複製"));
    actionCopy->setStatusTip(tr("複製文檔中選中內容並將其放入剪貼板"));
    connect(actionCopy, &QAction::triggered, textEdit, &QTextEdit::copy);

    actionPaste = new QAction(QIcon(rsrcPath + "/editpaste.png"), tr("粘貼(&P)"), this);
    actionPaste->setShortcut(tr("Ctrl+V"));
    actionPaste->setToolTip(tr("粘貼"));
    actionPaste->setStatusTip(tr("將剪貼板的內容粘貼到文檔"));
    connect(actionPaste, &QAction::triggered, textEdit, &QTextEdit::paste);

    // 編輯主功能表
    QMenu *menu = menuBar()->addMenu(tr("編輯(&E)"));
    menu->addAction(actionUndo);
    menu->addAction(actionRedo);
    menu->addSeparator();
    menu->addAction(actionCut);
    menu->addAction(actionCopy);
    menu->addAction(actionPaste);

    // 編輯工具條
    QToolBar *editToolbar = addToolBar(tr("編輯"));
    editToolbar->addAction(actionUndo);
    editToolbar->addAction(actionRedo);
    editToolbar->addSeparator();
    editToolbar->addAction(actionCut);
    editToolbar->addAction(actionCopy);
    editToolbar->addAction(actionPaste);

    // 新建剪貼板 mimeData 物件，並根據剪貼板中是否存在文本設置粘貼按鈕的啟動狀態
    if (const QMimeData *md = QApplication::clipboard()->mimeData())
        actionPaste->setEnabled(md->hasText());
}

void TextEdit::setupTextActions()
{
    // 格式主菜單動作集
    actionTextBold = new QAction(QIcon(rsrcPath + "/textbold.png"), tr("加粗(&B)"), this);
    actionTextBold->setShortcut(tr("Ctrl+B"));
    actionTextBold->setToolTip(tr("加粗"));
    actionTextBold->setStatusTip(tr("將所選文字加粗"));
    QFont bold;                         // 定義加粗字體
    bold.setBold(true);                 // 啟動字體加粗
    actionTextBold->setFont(bold);      // 將加粗功能賦給加粗動作
    actionTextBold->setCheckable(true); // 設置為可以選中
    connect(actionTextBold, &QAction::triggered, this, &TextEdit::textBold);

    actionTextItalic = new QAction(QIcon(rsrcPath + "/textitalic.png"), tr("傾斜(&I)"), this);
    actionTextItalic->setShortcut(tr("Ctrl+I"));
    actionTextItalic->setToolTip(tr("傾斜"));
    actionTextItalic->setStatusTip(tr("將所選文字傾斜"));
    QFont italic;                         // 定義傾斜字體
    italic.setItalic(true);               // 啟動字體傾斜
    actionTextItalic->setFont(italic);    // 將傾斜功能賦給傾斜動作
    actionTextItalic->setCheckable(true); // 設置為可以選中
    connect(actionTextItalic, &QAction::triggered, this, &TextEdit::textItalic);

    actionTextUnderline = new QAction(QIcon(rsrcPath + "/textunder.png"), tr("下畫線(&U)"), this);
    actionTextUnderline->setShortcut(tr("Ctrl+U"));
    actionTextUnderline->setToolTip(tr("下畫線"));
    actionTextUnderline->setStatusTip(tr("為所選文字添加下畫線"));
    QFont underline;                         // 定義字體下畫線
    underline.setUnderline(true);            // 啟動字體下畫線
    actionTextUnderline->setFont(underline); // 將下畫線功能賦給下畫線動作
    actionTextUnderline->setCheckable(true); // 設置為可以選中
    connect(actionTextUnderline, &QAction::triggered, this, &TextEdit::textUnderline);

    actionAlignLeft = new QAction(QIcon(rsrcPath + "/textleft.png"), tr("左對齊(&L)"), this);
    actionAlignLeft->setShortcut(tr("Ctrl+L"));
    actionAlignLeft->setToolTip(tr("左對齊"));
    actionAlignLeft->setStatusTip(tr("將文字左對齊"));
    actionAlignLeft->setCheckable(true);

    actionAlignCenter = new QAction(QIcon(rsrcPath + "/textcenter.png"), tr("居中(&E)"), this);
    actionAlignCenter->setShortcut(tr("Ctrl+E"));
    actionAlignCenter->setToolTip(tr("居中"));
    actionAlignCenter->setStatusTip(tr("將文字居中對齊"));
    actionAlignCenter->setCheckable(true);

    actionAlignRight = new QAction(QIcon(rsrcPath + "/textright.png"), tr("右對齊(&R)"), this);
    actionAlignRight->setShortcut(tr("Ctrl+R"));
    actionAlignRight->setToolTip(tr("右對齊"));
    actionAlignRight->setStatusTip(tr("將文字右對齊"));
    actionAlignRight->setCheckable(true);

    actionAlignJustify = new QAction(QIcon(rsrcPath + "/textjustify.png"), tr("兩端對齊(&J)"), this);
    actionAlignJustify->setShortcut(tr("Ctrl+J"));
    actionAlignJustify->setToolTip(tr("兩端對齊"));
    actionAlignJustify->setStatusTip(tr("將文字兩端對齊"));
    actionAlignJustify->setCheckable(true);

    // 確保 alignLeft 始終位於 alignRight 的左側
    QActionGroup *alignGroup = new QActionGroup(this);
    connect(alignGroup, &QActionGroup::triggered, this, &TextEdit::textAlign);

    if (QApplication::isLeftToRight()) {
        alignGroup->addAction(actionAlignLeft);
        alignGroup->addAction(actionAlignCenter);
        alignGroup->addAction(actionAlignRight);
    } else {
        alignGroup->addAction(actionAlignRight);
        alignGroup->addAction(actionAlignCenter);
        alignGroup->addAction(actionAlignLeft);
    }
    alignGroup->addAction(actionAlignJustify);

    QPixmap pix(16, 16);
    pix.fill(Qt::black);
    actionTextColor = new QAction(pix, tr("顏色(&C)..."), this);
    actionTextColor->setToolTip(tr("顏色"));
    actionTextColor->setStatusTip(tr("設置文字顏色"));
    connect(actionTextColor, &QAction::triggered, this, &TextEdit::textColor);

    // 格式主菜單
    QMenu *menu = menuBar()->addMenu(tr("格式(&F)"));
    QMenu *fontMenu = menu->addMenu(tr("字體(&T)"));
    fontMenu->addAction(actionTextBold);
    fontMenu->addAction(actionTextItalic);
    fontMenu->addAction(actionTextUnderline);
    QMenu *alignMenu = menu->addMenu(tr("段落(&P)"));
    alignMenu->addActions(alignGroup->actions());
    menu->addSeparator();
    menu->addAction(actionTextColor);

    // 格式工具條
    QToolBar *formatToolbar = addToolBar(tr("格式"));
    formatToolbar->addAction(actionTextBold);
    formatToolbar->addAction(actionTextItalic);
    formatToolbar->addAction(actionTextUnderline);
    formatToolbar->addSeparator();
    formatToolbar->addActions(alignGroup->actions());
    formatToolbar->addSeparator();
    formatToolbar->addAction(actionTextColor);

    /********************************************************************************/

    QToolBar *comboToolbar = addToolBar(tr("下拉式列示方塊"));
    comboToolbar->setAllowedAreas(Qt::TopToolBarArea | Qt::BottomToolBarArea);
    addToolBarBreak(Qt::TopToolBarArea); // 使工具條在頂部區域分多行顯示
    addToolBar(comboToolbar);

    comboStyle = new QComboBox(comboToolbar);
    comboToolbar->addWidget(comboStyle); // 將下拉式列示方塊添加至工具條
    comboStyle->addItem(tr("標準"));
    comboStyle->addItem(tr("專案符號 (●)"));
    comboStyle->addItem(tr("專案符號 (○)"));
    comboStyle->addItem(tr("專案符號 (■)"));
    comboStyle->addItem(tr("項目編號 (1.2.3.)"));
    comboStyle->addItem(tr("項目編號 (a.b.c.)"));
    comboStyle->addItem(tr("項目編號 (A.B.C.)"));
    comboStyle->addItem(tr("項目編號 (i.ii.iii.)"));
    comboStyle->addItem(tr("項目編號 (I.II.III.)"));
    comboStyle->addItem(tr("一級標題"));
    comboStyle->addItem(tr("二級標題"));
    comboStyle->addItem(tr("三級標題"));
    comboStyle->addItem(tr("四級標題"));
    comboStyle->addItem(tr("五級標題"));
    comboStyle->addItem(tr("六級標題"));
    comboStyle->setStatusTip(tr("添加專案符號（編號）或設置段落等級"));
    connect(comboStyle, QOverload<int>::of(&QComboBox::activated), this, &TextEdit::textStyle);

    comboFont = new QFontComboBox(comboToolbar);
    comboToolbar->addWidget(comboFont);  // 將下拉式列示方塊添加至工具條
    comboFont->setStatusTip(tr("更改字體"));
    connect(comboFont, QOverload<const QString &>::of(&QComboBox::activated), this, &TextEdit::textFamily);

    comboSize = new QComboBox(comboToolbar);
    comboToolbar->addWidget(comboSize); // 將下拉式列示方塊添加至工具條
    comboSize->setStatusTip(tr("更改字型大小"));
    comboSize->setEditable(true);       // 將字型大小下拉式列示方塊設置為可編輯

    const QList<int> standardSizes = QFontDatabase::standardSizes();
    foreach (int size, standardSizes)
        comboSize->addItem(QString::number(size));
    comboSize->setCurrentIndex(standardSizes.indexOf(QApplication::font().pointSize()));

    connect(comboSize, QOverload<const QString &>::of(&QComboBox::activated), this, &TextEdit::textSize);
}

void TextEdit::setupHelpActions()
{
    actionAbout = new QAction(tr("關於(&A)..."), this);
    actionAbout->setStatusTip(tr("關於\"文字編輯器\""));
    connect(actionAbout, &QAction::triggered, this, &TextEdit::about);

    actionQtAbout = new QAction(tr("關於 Qt(&Q)..."), this);
    actionQtAbout->setStatusTip(tr("關於 \"Qt\""));
    connect(actionQtAbout, &QAction::triggered, qApp, &QApplication::aboutQt);

    QMenu *helpMenu = menuBar()->addMenu(tr("幫助(&H)"));
    helpMenu->addAction(actionAbout);
    helpMenu->addAction(actionQtAbout);
}

void TextEdit::setCurrentFileName(const QString &fileName)
{
    this->fileName = fileName;
    textEdit->document()->setModified(false); // 設置文檔是否修改過,(一般用於關閉時提示保存)

    QString shownName; // 標題條顯示的文檔名
    if (fileName.isEmpty())
        shownName = "未命名.txt";
    else
        shownName = QFileInfo(fileName).fileName();
    // 設置視窗標題，當文檔被修改後使用星號 '*' 標記
    setWindowTitle(tr("%1[*] - %2").arg(shownName, tr("文字編輯器")));
    setWindowModified(false); // 預設標題中不顯示星號*
}

bool TextEdit::maybeSave()
{
    if (!textEdit->document()->isModified())
        return true;
    // 保存提醒訊息方塊
    const QMessageBox::StandardButton ret =
        QMessageBox::warning(this, tr("文字編輯器"),
                             tr("文檔已被修改，是否將其保存？"),
                             QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
    // 根據對話方塊中的選擇判斷是否保存檔
    if (ret == QMessageBox::Save)
        return fileSave();
    else if (ret == QMessageBox::Cancel)
        return false;
    return true;
}

bool TextEdit::load(const QString &f)
{
    if (!QFile::exists(f))
        return false;
    QFile file(f);
    if (!file.open(QFile::ReadOnly))
        return false;

    QByteArray data = file.readAll();
    QTextCodec *codec = Qt::codecForHtml(data);
    QString str = codec->toUnicode(data);
    if (Qt::mightBeRichText(str)) {
        textEdit->setHtml(str); // 以 html 格式打開文本資料
    } else {
        str = QString::fromLocal8Bit(data);
        textEdit->setPlainText(str); // 以純文字形式打開文本資料
    }

    setCurrentFileName(f);
    return true;
}

void TextEdit::mergeFormatOnWordOrSelection(const QTextCharFormat &format)
{
    QTextCursor cursor = textEdit->textCursor();
    if (!cursor.hasSelection())
        cursor.select(QTextCursor::WordUnderCursor);
    cursor.mergeCharFormat(format);
    textEdit->mergeCurrentCharFormat(format);
}

void TextEdit::fontChanged(const QFont &f)
{
    comboFont->setCurrentIndex(comboFont->findText(QFontInfo(f).family()));
    comboSize->setCurrentIndex(comboSize->findText(QString::number(f.pointSize())));
    actionTextBold->setChecked(f.bold());
    actionTextItalic->setChecked(f.italic());
    actionTextUnderline->setChecked(f.underline());
}

void TextEdit::colorChanged(const QColor &c)
{
    QPixmap pix(16, 16);
    pix.fill(c);
    actionTextColor->setIcon(pix);
}

void TextEdit::alignmentChanged(Qt::Alignment a)
{
    if (a & Qt::AlignLeft)
        actionAlignLeft->setChecked(true);
    else if (a & Qt::AlignHCenter)
        actionAlignCenter->setChecked(true);
    else if (a & Qt::AlignRight)
        actionAlignRight->setChecked(true);
    else if (a & Qt::AlignJustify)
        actionAlignJustify->setChecked(true);
}

