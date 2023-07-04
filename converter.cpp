#include "converter.h"
#include "./ui_converter.h"

Converter::Converter(QWidget *parent)
    : QMainWindow(parent, Qt::FramelessWindowHint|Qt::X11BypassWindowManagerHint)
    , ui(new Ui::Converter)
{
    ui->setupUi(this);
    setAttribute(Qt::WA_TranslucentBackground);
    setWindowTitle("");
    setMouseTracking(true);

    qt_logo.load(":/img/res/qtlogo_black_transparent.png");

    ui->cboxOutputFormat->setView(new QListView());

    QLineEdit *edit1 = ui->leInputFile, *edit2 = ui->leOutputFile;
    //QIcon clearIcon = QApplication::style()->standardIcon(QStyle::SP_DialogResetButton);
    QIcon clearIcon(":/img/res/clear-button.png");
    auto clearAction1 = new QAction(this), clearAction2 = new QAction(this);
    clearAction1->setToolTip(tr("清除当前文本框内容")); clearAction2->setToolTip(tr("清除当前文本框内容"));
    clearAction1->setIcon(clearIcon); clearAction2->setIcon(clearIcon);
    edit1->addAction(clearAction1, QLineEdit::TrailingPosition); edit2->addAction(clearAction2, QLineEdit::TrailingPosition);
    QObject::connect(clearAction1, &QAction::triggered, edit1, [edit1]{ edit1->setText(""); });
    QObject::connect(clearAction2, &QAction::triggered, edit2, [edit2]{ edit2->setText(""); });

    connect(ui->wndCloseButton, &QPushButton::clicked, this, &Converter::close);

    qtm1 = new QTimer(this);

    connect(qtm1, &QTimer::timeout, this, [=]{
        static int c = 0;
        if(c<=100) ui->pgBarProgress->setValue(c++);
        else qtm1->stop();
    });
    qtm1->start(100);
}

Converter::~Converter()
{
    delete ui;
}

void Converter::paintEvent(QPaintEvent *event) {
    QMainWindow::paintEvent(event);

    QPainter painter(this);
    painter.drawPixmap(97, 2, 21, 21, qt_logo);
}

QPointF Converter::lastpos(0,0);
void Converter::mousePressEvent(QMouseEvent * event) {
    if(event->button() == Qt::LeftButton && event->position().y()<22) {
        wnd_isDragging = true;
        lastpos = event->globalPosition();
    }
}

void Converter::mouseMoveEvent(QMouseEvent * event) {
    if(wnd_isDragging) {
        int dx = event->globalPosition().x() - lastpos.x();
        int dy = event->globalPosition().y() - lastpos.y();
        lastpos = event->globalPosition();
        this->move(this->x() + dx, this->y() + dy);
    }
}

void Converter::mouseReleaseEvent(QMouseEvent * event) {
    if(wnd_isDragging) {
        int dx = event->globalPosition().x() - lastpos.x();
        int dy = event->globalPosition().y() - lastpos.y();
        this->move(this->x() + dx, this->y() + dy);
        wnd_isDragging = false;
    }
}
