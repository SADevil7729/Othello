#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#define max_x 8
#define max_y 8
#define windowsize_x 1200
#define windowsize_y 750

#include <QMainWindow>
#include <QPainter>
#include <QWheelEvent>
#include <QTime>
#include <stdio.h>
#include <math.h>

namespace Ui
{
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    int count_value(int board[][max_y+1]);
    int judge_value(int t, int flag,int space);
    int is_catch(int board[][max_y+1],int player, int x, int y);
    void _catch(int board[][max_y+1], int player, int x, int y);
    //void clear_list(void);
    int ai_place(int func_board[][max_y+1], int player, int layer, int *alpha, int *beta, int is_first_node, int max_layer);
protected:
    void paintEvent(QPaintEvent *e);
    void wheelEvent(QWheelEvent *e);
    void mousePressEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
