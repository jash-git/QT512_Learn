#include "aboutdlg.h"
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>

AboutDlg::AboutDlg(QWidget* parent)
    : QDialog(parent)
{
    setWindowTitle(tr("自定义帮助对话框"));
    setWindowIcon(QIcon("://myImages/images/Qt_logo.png"));

    QVBoxLayout *layout1 = new QVBoxLayout;
    QLabel *iconLabel = new QLabel;
    QPixmap pix1("://myImages/images/Qt_logo.png");
    iconLabel->setPixmap(pix1.scaled(QSize(128, 128)));
    QLabel *idLabel = new QLabel(tr("ID: Qt_Learning"));
    QLabel *qrLabel = new QLabel;
    QPixmap pix2("://myImages/images/Qt_QR.jpg");
    qrLabel->setPixmap(pix2.scaled(QSize(128, 128)));
    QLabel *label1 = new QLabel(tr("扫描二维码关注"));
    layout1->addWidget(iconLabel, 0, Qt::AlignHCenter);
    layout1->addWidget(idLabel, 0, Qt::AlignHCenter);
    layout1->addSpacing(20);
    layout1->addWidget(qrLabel, 0, Qt::AlignHCenter);
    layout1->addWidget(label1, 0, Qt::AlignHCenter);

    QLabel *labels[7];
    QString names[7];
    names[0] = "<a style='color:green;' href=\"https://mp.weixin.qq.com/s/HyemCP79yZqjLF5WSagCrQ\">界面设计";
    names[1] = "<a style='color:green;' href=\"https://mp.weixin.qq.com/s/frPJymEyV5tRpqlgjfcbDQ\">文件操作功能（上）";
    names[2] = "<a style='color:green;' href=\"https://mp.weixin.qq.com/s/tIjz2l-xZOAgfTJwQUxQTg\">文件操作功能（下）";
    names[3] = "<a style='color:green;' href=\"https://mp.weixin.qq.com/s/V4Hm31LLwusG278XolBm6w\">文本编辑功能";
    names[4] = "<a style='color:green;' href=\"https://mp.weixin.qq.com/s/h_sMAqNpF9nPbZob5crTgg\">文档排版美化功能（上）";
    names[5] = "<a style='color:green;' href=\"https://mp.weixin.qq.com/s/-ye99b9vdaiomCjYZBeqXg\">文档排版美化功能（下）";
    names[6] = "<a style='color:green;' href=\"https://mp.weixin.qq.com/s/zXnKW3d7t04ABIrV1gr0cg\">“帮助”功能实现";

    QVBoxLayout *layout2 = new QVBoxLayout;
    QString str = tr("该示例演示了 Qt 文本编辑功能的应用，\n"
                     "并提供了示例文档供您试用。\n\n"
                     "想了解并获取的更多，欢迎关注微信公\n"
                     "众号：Qt 学习 (ID: Qt_Learning)。");
    QLabel *aboutLabel = new QLabel(str);
    QLabel *label2 = new QLabel(tr("【文本编辑器】系列："));
    layout2->addWidget(aboutLabel);
    layout2->addStretch();
    layout2->addWidget(label2);
    for (int i = 0; i < 7; i++) {
        labels[i] = new QLabel;
        labels[i]->setOpenExternalLinks(true);
        labels[i]->setText(names[i]);
        layout2->addWidget(labels[i]);
    }
    layout2->addStretch();

    QHBoxLayout *layout3 = new QHBoxLayout;
    layout3->addLayout(layout1);
    layout3->addSpacing(30);
    layout3->addLayout(layout2);

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    QPushButton *button = new QPushButton(tr("Ok"));
    QHBoxLayout *layout4 = new QHBoxLayout;
    layout4->addStretch();
    layout4->addWidget(button);
    connect(button, SIGNAL(clicked()), this, SLOT(accept()));
    mainLayout->setMargin(20);
    mainLayout->addLayout(layout3);
    mainLayout->addLayout(layout4);
}
