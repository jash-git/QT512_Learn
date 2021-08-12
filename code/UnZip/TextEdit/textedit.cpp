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
    setWindowTitle(tr("文本编辑器")); // 设置应用程序标题
    setMinimumSize(QSize(600, 400));
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
    statusBar()->showMessage(tr("就绪"));

    QFont textFont("Helvetica");
    textFont.setStyleHint(QFont::SansSerif);
    textEdit->setFont(textFont);
    fontChanged(textEdit->font());
    colorChanged(textEdit->textColor());
    alignmentChanged(textEdit->alignment());

    connect(textEdit->document(), &QTextDocument::modificationChanged,
            this, &QWidget::setWindowModified);
    connect(textEdit->document(), &QTextDocument::modificationChanged,
            actionSave, &QAction::setEnabled); // 根据文档状态设置“保存”按钮的激活状态
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

    textEdit->setFocus(); // 将键盘输入焦点赋予当前窗口的文本编辑框
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
//    // 第一种方法
//    if (maybeSave()) {
//        textEdit->clear();
//        setCurrentFileName(QString());
//    }

    // 第二种方法
    TextEdit *newTextEdit = new TextEdit;
    newTextEdit->show();
}

void TextEdit::fileOpen()
{
    QFileDialog fileDialog(this, tr("打开文件..."));
    fileDialog.setAcceptMode(QFileDialog::AcceptOpen);
    fileDialog.setFileMode(QFileDialog::ExistingFile);
    fileDialog.setMimeTypeFilters(QStringList() << "text/html" << "text/plain");
    if (fileDialog.exec() != QDialog::Accepted)
        return;
    const QString fn = fileDialog.selectedFiles().first();
    if (load(fn))
        statusBar()->showMessage(tr("已打开 \"%1\"").arg(QDir::toNativeSeparators(fn)));
    else
        statusBar()->showMessage(tr("未能打开 \"%1\"").arg(QDir::toNativeSeparators(fn)));
}

bool TextEdit::fileSave()
{
    // 若未命名文件名或文件名者以 ':/' 开头，则直接执行另存为操作
    if (fileName.isEmpty())
        return fileSaveAs();
    if (fileName.startsWith(QStringLiteral(":/")))
        return fileSaveAs();

    QTextDocumentWriter writer(fileName);
    bool success = writer.write(textEdit->document());
    // 在状态栏显示是否保存成功的提示信息
    if (success) {
        textEdit->document()->setModified(false);
        statusBar()->showMessage(tr("已写入 \"%1\"")
                                 .arg(QDir::toNativeSeparators(fileName)));
    } else {
        statusBar()->showMessage(tr("未能写入 \"%1\"")
                                 .arg(QDir::toNativeSeparators(fileName)));
    }
    return success;
}

bool TextEdit::fileSaveAs()
{
    QFileDialog fileDialog(this, tr("另存为...")); // 新建标准文件对话框
    fileDialog.setAcceptMode(QFileDialog::AcceptSave);
    QStringList mimeTypes;
    mimeTypes << "application/vnd.oasis.opendocument.text" << "text/html" << "text/plain";
    fileDialog.setMimeTypeFilters(mimeTypes); // 从 MIME 类型列表中设置文件对话框中使用的过滤器
    fileDialog.setDefaultSuffix("odt");       // 如果未指定其他后缀，则将此后缀添加到文件名中
    if (fileDialog.exec() != QDialog::Accepted)
        return false;
    const QString fn = fileDialog.selectedFiles().first(); // 包含对话框中所选文件的绝对路径的第一个字符串
    setCurrentFileName(fn);
    return fileSave();
}

void TextEdit::filePrint()
{
    QPrinter printer(QPrinter::HighResolution); // 新建打印对象，并设置打印模式
    QPrintDialog *dlg = new QPrintDialog(&printer, this);
//    if (textEdit->textCursor().hasSelection())
//        dlg->addEnabledOption(QAbstractPrintDialog::PrintSelection);
//    dlg->setWindowTitle(tr("打印文档"));
    if (dlg->exec() == QDialog::Accepted)
        textEdit->print(&printer);
    delete dlg;
}

void TextEdit::filePrintPreview()
{
    QPrinter printer(QPrinter::HighResolution);
    QPrintPreviewDialog preview(&printer, this); // 新建打印预览对话框
    connect(&preview, &QPrintPreviewDialog::paintRequested, this, &TextEdit::printPreview);
    preview.exec(); // 执行打印预览操作
}

void TextEdit::filePrintPdf()
{
    QFileDialog fileDialog(this, tr("输出为 PDF"));
    fileDialog.setAcceptMode(QFileDialog::AcceptSave);
    fileDialog.setMimeTypeFilters(QStringList("application/pdf"));
    fileDialog.setDefaultSuffix("pdf");
    if (fileDialog.exec() != QDialog::Accepted)
        return;
    QString fileName = fileDialog.selectedFiles().first();
    QPrinter printer(QPrinter::HighResolution);
    printer.setOutputFormat(QPrinter::PdfFormat); // 指定输出格式
    printer.setOutputFileName(fileName);
    textEdit->document()->print(&printer);
    statusBar()->showMessage(tr("输出为 \"%1\"")
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
    QTextCursor cursor = textEdit->textCursor(); // 获得文本编辑框的 QTextCursor 对象指针
    QTextListFormat::Style style = QTextListFormat::ListStyleUndefined;

    switch (styleIndex) { // 提供了 8 种文本排序的方式
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

    cursor.beginEditBlock(); // 设置缩进值

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
    QString str = tr("该示例演示了 Qt 文本编辑功能的应用，\n"
                     "并提供了示例文档供您试用。\n\n"
                     "想了解并获取的更多，欢迎关注微信公\n"
                     "众号：Qt 学习 (ID: Qt_Learning )。");

    // 1
//    QMessageBox::about(this, tr("关于"), str);

    // 2
//    QMessageBox customMsgBox;
//    customMsgBox.setWindowTitle(tr("自定义帮助对话框"));
//    customMsgBox.addButton(QMessageBox::Ok); // 设置自定义帮助对话框的按钮
//    customMsgBox.setText(str);               // 设置自定义帮助对话框中显示的内容
//    QPixmap pix(rsrcPath + "/Qt_logo.png");
//    customMsgBox.setIconPixmap(pix.scaled(QSize(128, 128))); // 设置自定义帮助对话框图标
//    customMsgBox.exec();                                     // 显示此自定义帮助对话框

    // 3
    AboutDlg *aboutDlg = new AboutDlg();
    aboutDlg->show();
}

void TextEdit::setupFileActions()
{
    // 文件主菜单动作集
    actionNew = new QAction(QIcon(rsrcPath + "/filenew.png"),  tr("新建(&N)"), this);
    actionNew->setShortcut(tr("Ctrl+N"));
    actionNew->setToolTip(tr("新建"));
    actionNew->setStatusTip(tr("创建一个新文档"));
    connect(actionNew, &QAction::triggered, this, &TextEdit::fileNew);

    actionOpen = new QAction(QIcon(rsrcPath + "/fileopen.png"), tr("打开(&O)..."), this);
    actionOpen->setShortcut(tr("Ctrl+O"));
    actionOpen->setToolTip(tr("打开"));
    actionOpen->setStatusTip(tr("打开已存在的文档"));
    connect(actionOpen, &QAction::triggered, this, &TextEdit::fileOpen);

    actionSave = new QAction(QIcon(rsrcPath + "/filesave.png"), tr("保存(&S)"), this);
    actionSave->setShortcut(tr("Ctrl+S"));
    actionSave->setToolTip(tr("保存"));
    actionSave->setStatusTip(tr("将当前文档存盘"));
    connect(actionSave, &QAction::triggered, this, &TextEdit::fileSave);

    actionSaveAs = new QAction(tr("另存为(&A)..."), this);
    actionSaveAs->setStatusTip(tr("以一个新名字保存文档"));
    connect(actionSaveAs, &QAction::triggered, this, &TextEdit::fileSaveAs);

    actionPrint = new QAction(QIcon(rsrcPath + "/fileprint.png"), tr("打印(&P)..."), this);
    actionPrint->setShortcut(tr("Ctrl+P"));
    actionPrint->setToolTip(tr("打印"));
    actionPrint->setStatusTip(tr("打印文档"));
    connect(actionPrint, &QAction::triggered, this, &TextEdit::filePrint);

    actionPrintPreview = new QAction(tr("打印预览..."), this);
    actionPrintPreview->setStatusTip(tr("预览打印效果"));
    connect(actionPrintPreview, &QAction::triggered, this, &TextEdit::filePrintPreview);

    actionExportPDF = new QAction(QIcon(rsrcPath + "/exportpdf.png"), tr("输出为 PDF(&E)..."), this);
    actionExportPDF->setShortcut(tr("Ctrl+D"));
    actionExportPDF->setToolTip(tr("输出为 PDF"));
    actionExportPDF->setStatusTip(tr("将文档导出为 PDF 格式"));
    connect(actionExportPDF, &QAction::triggered, this, &TextEdit::filePrintPdf);

    actionQuit = new QAction(tr("退出(&Q)"), this);
    actionQuit->setShortcut(tr("Ctrl+Q"));
    actionQuit->setStatusTip(tr("退出应用程序"));
    connect(actionQuit, &QAction::triggered, this, &QWidget::close);

    // 文件主菜单
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

    // 文件工具条
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
    // 编辑主菜单动作集
    actionUndo = new QAction(QIcon(rsrcPath + "/editundo.png"), tr("撤销(&U)"), this);
    actionUndo->setShortcut(tr("Ctrl+Z"));
    actionUndo->setToolTip(tr("撤销"));
    actionUndo->setStatusTip(tr("撤销当前操作"));
    connect(actionUndo, &QAction::triggered, textEdit, &QTextEdit::undo);

    actionRedo = new QAction(QIcon(rsrcPath + "/editredo.png"), tr("重做(&R)"), this);
    actionRedo->setShortcut(tr("Ctrl+Y"));
    actionRedo->setToolTip(tr("重做"));
    actionRedo->setStatusTip(tr("恢复之前操作"));
    connect(actionRedo, &QAction::triggered, textEdit, &QTextEdit::redo);

    actionCut = new QAction(QIcon(rsrcPath + "/editcut.png"), tr("剪切(&T)"), this);
    actionCut->setShortcut(tr("Ctrl+X"));
    actionCut->setToolTip(tr("剪切"));
    actionCut->setStatusTip(tr("从文档中剪切选中内容并将其放入剪贴板"));
    connect(actionCut, &QAction::triggered, textEdit, &QTextEdit::cut);

    actionCopy = new QAction(QIcon(rsrcPath + "/editcopy.png"), tr("复制(&C)"), this);
    actionCopy->setShortcut(tr("Ctrl+C"));
    actionCopy->setToolTip(tr("复制"));
    actionCopy->setStatusTip(tr("复制文档中选中内容并将其放入剪贴板"));
    connect(actionCopy, &QAction::triggered, textEdit, &QTextEdit::copy);

    actionPaste = new QAction(QIcon(rsrcPath + "/editpaste.png"), tr("粘贴(&P)"), this);
    actionPaste->setShortcut(tr("Ctrl+V"));
    actionPaste->setToolTip(tr("粘贴"));
    actionPaste->setStatusTip(tr("将剪贴板的内容粘贴到文档"));
    connect(actionPaste, &QAction::triggered, textEdit, &QTextEdit::paste);

    // 编辑主菜单
    QMenu *menu = menuBar()->addMenu(tr("编辑(&E)"));
    menu->addAction(actionUndo);
    menu->addAction(actionRedo);
    menu->addSeparator();
    menu->addAction(actionCut);
    menu->addAction(actionCopy);
    menu->addAction(actionPaste);

    // 编辑工具条
    QToolBar *editToolbar = addToolBar(tr("编辑"));
    editToolbar->addAction(actionUndo);
    editToolbar->addAction(actionRedo);
    editToolbar->addSeparator();
    editToolbar->addAction(actionCut);
    editToolbar->addAction(actionCopy);
    editToolbar->addAction(actionPaste);

    // 新建剪贴板 mimeData 对象，并根据剪贴板中是否存在文本设置粘贴按钮的激活状态
    if (const QMimeData *md = QApplication::clipboard()->mimeData())
        actionPaste->setEnabled(md->hasText());
}

void TextEdit::setupTextActions()
{
    // 格式主菜单动作集
    actionTextBold = new QAction(QIcon(rsrcPath + "/textbold.png"), tr("加粗(&B)"), this);
    actionTextBold->setShortcut(tr("Ctrl+B"));
    actionTextBold->setToolTip(tr("加粗"));
    actionTextBold->setStatusTip(tr("将所选文字加粗"));
    QFont bold;                         // 定义加粗字体
    bold.setBold(true);                 // 激活字体加粗
    actionTextBold->setFont(bold);      // 将加粗功能赋给加粗动作
    actionTextBold->setCheckable(true); // 设置为可以选中
    connect(actionTextBold, &QAction::triggered, this, &TextEdit::textBold);

    actionTextItalic = new QAction(QIcon(rsrcPath + "/textitalic.png"), tr("倾斜(&I)"), this);
    actionTextItalic->setShortcut(tr("Ctrl+I"));
    actionTextItalic->setToolTip(tr("倾斜"));
    actionTextItalic->setStatusTip(tr("将所选文字倾斜"));
    QFont italic;                         // 定义倾斜字体
    italic.setItalic(true);               // 激活字体倾斜
    actionTextItalic->setFont(italic);    // 将倾斜功能赋给倾斜动作
    actionTextItalic->setCheckable(true); // 设置为可以选中
    connect(actionTextItalic, &QAction::triggered, this, &TextEdit::textItalic);

    actionTextUnderline = new QAction(QIcon(rsrcPath + "/textunder.png"), tr("下画线(&U)"), this);
    actionTextUnderline->setShortcut(tr("Ctrl+U"));
    actionTextUnderline->setToolTip(tr("下画线"));
    actionTextUnderline->setStatusTip(tr("为所选文字添加下画线"));
    QFont underline;                         // 定义字体下画线
    underline.setUnderline(true);            // 激活字体下画线
    actionTextUnderline->setFont(underline); // 将下画线功能赋给下画线动作
    actionTextUnderline->setCheckable(true); // 设置为可以选中
    connect(actionTextUnderline, &QAction::triggered, this, &TextEdit::textUnderline);

    actionAlignLeft = new QAction(QIcon(rsrcPath + "/textleft.png"), tr("左对齐(&L)"), this);
    actionAlignLeft->setShortcut(tr("Ctrl+L"));
    actionAlignLeft->setToolTip(tr("左对齐"));
    actionAlignLeft->setStatusTip(tr("将文字左对齐"));
    actionAlignLeft->setCheckable(true);

    actionAlignCenter = new QAction(QIcon(rsrcPath + "/textcenter.png"), tr("居中(&E)"), this);
    actionAlignCenter->setShortcut(tr("Ctrl+E"));
    actionAlignCenter->setToolTip(tr("居中"));
    actionAlignCenter->setStatusTip(tr("将文字居中对齐"));
    actionAlignCenter->setCheckable(true);

    actionAlignRight = new QAction(QIcon(rsrcPath + "/textright.png"), tr("右对齐(&R)"), this);
    actionAlignRight->setShortcut(tr("Ctrl+R"));
    actionAlignRight->setToolTip(tr("右对齐"));
    actionAlignRight->setStatusTip(tr("将文字右对齐"));
    actionAlignRight->setCheckable(true);

    actionAlignJustify = new QAction(QIcon(rsrcPath + "/textjustify.png"), tr("两端对齐(&J)"), this);
    actionAlignJustify->setShortcut(tr("Ctrl+J"));
    actionAlignJustify->setToolTip(tr("两端对齐"));
    actionAlignJustify->setStatusTip(tr("将文字两端对齐"));
    actionAlignJustify->setCheckable(true);

    // 确保 alignLeft 始终位于 alignRight 的左侧
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
    actionTextColor = new QAction(pix, tr("颜色(&C)..."), this);
    actionTextColor->setToolTip(tr("颜色"));
    actionTextColor->setStatusTip(tr("设置文字颜色"));
    connect(actionTextColor, &QAction::triggered, this, &TextEdit::textColor);

    // 格式主菜单
    QMenu *menu = menuBar()->addMenu(tr("格式(&F)"));
    QMenu *fontMenu = menu->addMenu(tr("字体(&T)"));
    fontMenu->addAction(actionTextBold);
    fontMenu->addAction(actionTextItalic);
    fontMenu->addAction(actionTextUnderline);
    QMenu *alignMenu = menu->addMenu(tr("段落(&P)"));
    alignMenu->addActions(alignGroup->actions());
    menu->addSeparator();
    menu->addAction(actionTextColor);

    // 格式工具条
    QToolBar *formatToolbar = addToolBar(tr("格式"));
    formatToolbar->addAction(actionTextBold);
    formatToolbar->addAction(actionTextItalic);
    formatToolbar->addAction(actionTextUnderline);
    formatToolbar->addSeparator();
    formatToolbar->addActions(alignGroup->actions());
    formatToolbar->addSeparator();
    formatToolbar->addAction(actionTextColor);

    /********************************************************************************/

    QToolBar *comboToolbar = addToolBar(tr("组合框"));
    comboToolbar->setAllowedAreas(Qt::TopToolBarArea | Qt::BottomToolBarArea);
    addToolBarBreak(Qt::TopToolBarArea); // 使工具条在顶部区域分多行显示
    addToolBar(comboToolbar);

    comboStyle = new QComboBox(comboToolbar);
    comboToolbar->addWidget(comboStyle); // 将组合框添加至工具条
    comboStyle->addItem(tr("标准"));
    comboStyle->addItem(tr("项目符号 (●)"));
    comboStyle->addItem(tr("项目符号 (○)"));
    comboStyle->addItem(tr("项目符号 (■)"));
    comboStyle->addItem(tr("项目编号 (1.2.3.)"));
    comboStyle->addItem(tr("项目编号 (a.b.c.)"));
    comboStyle->addItem(tr("项目编号 (A.B.C.)"));
    comboStyle->addItem(tr("项目编号 (i.ii.iii.)"));
    comboStyle->addItem(tr("项目编号 (I.II.III.)"));
    comboStyle->addItem(tr("一级标题"));
    comboStyle->addItem(tr("二级标题"));
    comboStyle->addItem(tr("三级标题"));
    comboStyle->addItem(tr("四级标题"));
    comboStyle->addItem(tr("五级标题"));
    comboStyle->addItem(tr("六级标题"));
    comboStyle->setStatusTip(tr("添加项目符号（编号）或设置段落等级"));
    connect(comboStyle, QOverload<int>::of(&QComboBox::activated), this, &TextEdit::textStyle);

    comboFont = new QFontComboBox(comboToolbar);
    comboToolbar->addWidget(comboFont);  // 将组合框添加至工具条
    comboFont->setStatusTip(tr("更改字体"));
    connect(comboFont, QOverload<const QString &>::of(&QComboBox::activated), this, &TextEdit::textFamily);

    comboSize = new QComboBox(comboToolbar);
    comboToolbar->addWidget(comboSize); // 将组合框添加至工具条
    comboSize->setStatusTip(tr("更改字号"));
    comboSize->setEditable(true);       // 将字号组合框设置为可编辑

    const QList<int> standardSizes = QFontDatabase::standardSizes();
    foreach (int size, standardSizes)
        comboSize->addItem(QString::number(size));
    comboSize->setCurrentIndex(standardSizes.indexOf(QApplication::font().pointSize()));

    connect(comboSize, QOverload<const QString &>::of(&QComboBox::activated), this, &TextEdit::textSize);
}

void TextEdit::setupHelpActions()
{
    actionAbout = new QAction(tr("关于(&A)..."), this);
    actionAbout->setStatusTip(tr("关于\"文本编辑器\""));
    connect(actionAbout, &QAction::triggered, this, &TextEdit::about);

    actionQtAbout = new QAction(tr("关于 Qt(&Q)..."), this);
    actionQtAbout->setStatusTip(tr("关于 \"Qt\""));
    connect(actionQtAbout, &QAction::triggered, qApp, &QApplication::aboutQt);

    QMenu *helpMenu = menuBar()->addMenu(tr("帮助(&H)"));
    helpMenu->addAction(actionAbout);
    helpMenu->addAction(actionQtAbout);
}

void TextEdit::setCurrentFileName(const QString &fileName)
{
    this->fileName = fileName;
    textEdit->document()->setModified(false); // 设置文档是否修改过,(一般用于关闭时提示保存)

    QString shownName; // 标题条显示的文档名
    if (fileName.isEmpty())
        shownName = "未命名.txt";
    else
        shownName = QFileInfo(fileName).fileName();
    // 设置窗口标题，当文档被修改后使用星号 '*' 标记
    setWindowTitle(tr("%1[*] - %2").arg(shownName, tr("文本编辑器")));
    setWindowModified(false); // 默认标题中不显示星号*
}

bool TextEdit::maybeSave()
{
    if (!textEdit->document()->isModified())
        return true;
    // 保存提醒消息框
    const QMessageBox::StandardButton ret =
        QMessageBox::warning(this, tr("文本编辑器"),
                             tr("文档已被修改，是否将其保存？"),
                             QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
    // 根据对话框中的选择判断是否保存文件
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
        textEdit->setHtml(str); // 以 html 格式打开文本数据
    } else {
        str = QString::fromLocal8Bit(data);
        textEdit->setPlainText(str); // 以纯文本形式打开文本数据
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

