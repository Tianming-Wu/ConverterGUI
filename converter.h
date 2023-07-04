#ifndef CONVERTER_H
#define CONVERTER_H

#include <QMainWindow>
#include <QPainter>
#include <QEvent>
#include <QMouseEvent>
#include <QListView>
#include <QTimer>
#include <QProcess>

QT_BEGIN_NAMESPACE
namespace Ui { class Converter; }
QT_END_NAMESPACE

class Converter : public QMainWindow
{
    Q_OBJECT

public:
    Converter(QWidget *parent = nullptr);
    ~Converter();

protected:
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent * event);
    void mouseMoveEvent(QMouseEvent * event);
    void mouseReleaseEvent(QMouseEvent * event);

private:
    Ui::Converter *ui;
    QPixmap qt_logo;

    static QPointF lastpos;
    bool wnd_isDragging;

    QTimer *qtm1;
};
#endif // CONVERTER_H
