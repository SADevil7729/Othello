#include "mainwindow.h"
#include "ui_mainwindow.h"


int zoom = 45;

int alpha_count=0;
int beta_count=0;
int zoom_center_x = 0;
int zoom_center_y = 0;
int zoom_revise_x = 0;
int zoom_revise_y = 0;
int mouse_click_x=0;
int mouse_click_y=0;
int flag1,flag2,flag3,flag4;
int ai_x;
int ai_y;
int board[max_x+1][max_y+1];
int total_chess=0;
int condition=1;
int left_chess=0;
QTime time;
MainWindow::MainWindow(QWidget *parent) :QMainWindow(parent),ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    int i,j;
    for(i=1; i<=max_x; i++)
    {
        for(j=1; j<=max_y; j++)
        {
            board[i][j]=0;
        }
    }
    this->setFixedSize(windowsize_x,windowsize_y);
    board[4][4]=1;
    board[4][5]=2;
    board[5][4]=2;
    board[5][5]=1;
    /*

    int v_max_x=0,v_min_x=0, v_max_y=0, v_min_y=0;
    chess_center(&v_max_x,&v_min_x,&v_max_y,&v_min_y);
    printf("max_x:%d min_x:%d max_y:%d min_y:%d\n",v_max_x,v_min_x,v_max_y,v_min_y);
    fflush(stdout);*/
}
MainWindow::~MainWindow()
{
    delete ui;
}
int MainWindow::is_catch(int board[][max_y+1], int player, int x, int y)
{
    if(x<1||x>max_x||y<1||y>max_y||board[x][y]!=0)
    {
        return 0;
    }
    int i,j;
    //7
    if(x>=3&&y>=3&&board[x-1][y-1]!=0&&board[x-1][y-1]!=player)
    {
        i=x-2;
        j=y-2;
        while(1)
        {
            if(board[i][j]==player)
            {
                printf("part 7\n");
                fflush(stdout);
                return 1;
            }
            else if(board[i][j]==0)
            {
                break;
            }
            i--;
            j--;
            if(i<1&&j<1)
            {
                break;
            }
        }
    }

    //8
    if(y>=3&&board[x][y-1]!=0&&board[x][y-1]!=player)
    {
        i=x;
        j=y-2;
        while(1)
        {
            if(board[i][j]==player)
            {
                printf("part 8\n");
                fflush(stdout);
                return 1;
            }
            else if(board[i][j]==0)
            {
                break;
            }
            j--;
            if(j<1)
            {
                break;
            }
        }
    }

    //4
    if(x>=3&&board[x-1][y]!=0&&board[x-1][y]!=player)
    {
        i=x-2;
        j=y;
        while(1)
        {
            if(board[i][j]==player)
            {
                printf("part 4\n");
                fflush(stdout);
                return 1;
            }
            else if(board[i][j]==0)
            {
                break;
            }
            i--;
            if(i<1)
            {
                break;
            }
        }
    }
    //3
    if(x<=max_x-2&&y<=max_y-2&&board[x+1][y+1]!=0&&board[x+1][y+1]!=player)
    {
        i=x+2;
        j=y+2;
        while(1)
        {
            if(board[i][j]==player)
            {
                printf("part 3\n");
                fflush(stdout);
                return 1;
            }
            else if(board[i][j]==0)
            {
                break;
            }
            i++;
            j++;
            if(i>max_x&&j>max_y)
            {
                break;
            }
        }
    }
    //6
    if(x<=max_x-2&&board[x+1][y]!=0&&board[x+1][y]!=player)
    {
        i=x+2;
        j=y;
        while(1)
        {
            if(board[i][j]==player)
            {
                printf("part 6\n");
                fflush(stdout);
                return 1;
            }
            else if(board[i][j]==0)
            {
                break;
            }
            i++;
            if(i>max_x)
            {
                break;
            }
        }
    }
    //2
    if(y<=max_y-2&&board[x][y+1]!=0&&board[x][y+1]!=player)
    {
        i=x;
        j=y+2;
        while(1)
        {
            if(board[i][j]==player)
            {
                printf("part 2\n");
                fflush(stdout);
                return 1;
            }
            else if(board[i][j]==0)
            {
                break;
            }
            j++;
            if(j>max_y)
            {
                break;
            }
        }
    }
    //1
    if(x>=3&&y<=max_y-2&&board[x-1][y+1]!=0&&board[x-1][y+1]!=player)
    {
        i=x-2;
        j=y+2;
        while(1)
        {
            if(board[i][j]==player)
            {
                printf("part 1\n");
                fflush(stdout);
                return 1;
            }
            else if(board[i][j]==0)
            {
                break;
            }
            i--;
            j++;
            if(i<1&&j>max_y)
            {
                break;
            }
        }
    }
    //9
    if(x<=max_x-2&&y>=3&&board[x+1][y-1]!=0&&board[x+1][y-1]!=player)
    {
        i=x+2;
        j=y-2;
        while(1)
        {
            if(board[i][j]==player)
            {
                printf("part 9\n");
                fflush(stdout);
                return 1;
            }
            else if(board[i][j]==0)
            {
                break;
            }
            i++;
            j--;
            if(i>max_x&&j<1)
            {
                break;
            }
        }
    }
    return 0;
}
void MainWindow::_catch(int board[][max_y+1], int player, int x, int y)
{
    int i,j;
    //7
    if(x>=3&&y>=3&&board[x-1][y-1]!=0&&board[x-1][y-1]!=player)
    {
        i=x-2;
        j=y-2;
        while(1)
        {
            if(board[i][j]==player)
            {
                int dest_x=i,dest_y=j;
                for(i=x-1,j=y-1; i>dest_x&&j>dest_y; i--,j--)
                {
                    board[i][j]=player;
                }
                break;
            }
            else if(board[i][j]==0)
            {
                break;
            }
            i--;
            j--;
            if(i<1&&j<1)
            {
                break;
            }
        }
    }

    //8
    if(y>=3&&board[x][y-1]!=0&&board[x][y-1]!=player)
    {
        i=x;
        j=y-2;
        while(1)
        {
            if(board[i][j]==player)
            {
                int dest_y=j;
                for(j=y-1; j>dest_y; j--)
                {
                    board[i][j]=player;
                }
                break;
            }
            else if(board[i][j]==0)
            {
                break;
            }
            j--;
            if(j<1)
            {
                break;
            }
        }
    }

    //4
    if(x>=3&&board[x-1][y]!=0&&board[x-1][y]!=player)
    {
        i=x-2;
        j=y;
        while(1)
        {
            if(board[i][j]==player)
            {
                int dest_x=i;
                for(i=x-1; i>dest_x; i--)
                {
                    board[i][j]=player;
                }
                break;
            }
            else if(board[i][j]==0)
            {
                break;
            }
            i--;
            if(i<1)
            {
                break;
            }
        }
    }
    //3
    if(x<=max_x-2&&y<=max_y-2&&board[x+1][y+1]!=0&&board[x+1][y+1]!=player)
    {
        i=x+2;
        j=y+2;
        while(1)
        {
            if(board[i][j]==player)
            {
                int dest_x=i,dest_y=j;
                for(i=x+1,j=y+1; i<dest_x&&j<dest_y; i++,j++)
                {
                    board[i][j]=player;
                }
                break;
            }
            else if(board[i][j]==0)
            {
                break;
            }
            i++;
            j++;
            if(i>max_x&&j>max_y)
            {
                break;
            }
        }
    }
    //6
    if(x<=max_x-2&&board[x+1][y]!=0&&board[x+1][y]!=player)
    {
        i=x+2;
        j=y;
        while(1)
        {
            if(board[i][j]==player)
            {
                int dest_x=i;
                for(i=x+1; i<dest_x; i++)
                {
                    board[i][j]=player;
                }
                break;
            }
            else if(board[i][j]==0)
            {
                break;
            }
            i++;
            if(i>max_x)
            {
                break;
            }
        }
    }
    //2
    if(y<=max_y-2&&board[x][y+1]!=0&&board[x][y+1]!=player)
    {
        i=x;
        j=y+2;
        while(1)
        {
            if(board[i][j]==player)
            {
                int dest_y=j;
                for(i=x,j=y+1; j<dest_y; j++)
                {
                    board[i][j]=player;
                }
                break;
            }
            else if(board[i][j]==0)
            {
                break;
            }
            j++;
            if(j>max_y)
            {
                break;
            }
        }
    }

    //1
    if(x>=3&&y<=max_y-2&&board[x-1][y+1]!=0&&board[x-1][y+1]!=player)
    {
        i=x-2;
        j=y+2;
        while(1)
        {
            if(board[i][j]==player)
            {
                int dest_x=i,dest_y=j;
                for(i=x-1,j=y+1; i>dest_x&&j<dest_y; i--,j++)
                {
                    board[i][j]=player;
                }
                break;
            }
            else if(board[i][j]==0)
            {
                break;
            }
            i--;
            j++;
            if(i<1&&j>max_y)
            {
                break;
            }
        }
    }
    //9
    if(x<=max_x-2&&y>=3&&board[x+1][y-1]!=0&&board[x+1][y-1]!=player)
    {
        i=x+2;
        j=y-2;
        while(1)
        {
            if(board[i][j]==player)
            {
                int dest_x=i,dest_y=j;
                for(i=x+1,j=y-1; i<dest_x&&j>dest_y; i++,j--)
                {
                    board[i][j]=player;
                }
                break;
            }
            else if(board[i][j]==0)
            {
                break;
            }
            i++;
            j--;
            if(i>max_x&&j<1)
            {
                break;
            }
        }
    }
    return ;

}
int MainWindow::count_value(int board[][max_y+1])
{
    int i,j;
    int value=0;
    for(i=1; i<=max_x; i++)
    {
        for(j=1; j<=max_y; j++)
        {
            if(board[i][j]==1)
            {
                value--;
            }
            else if(board[i][j]==2)
            {
                value++;
            }
        }
    }
    return value;
}
int MainWindow::ai_place(int func_board[][max_y+1],int player, int layer, int *alpha, int *beta,int is_first_node, int max_layer)
{
    if(layer==max_layer)
    {
        return count_value(func_board);
    }
    int local_minscore=0;
    int local_maxscore=0;
    int local_minscore_first_flag=1;
    int local_maxscore_first_flag=1;
    int i,j,k,l;
    int local_is_first_node=is_first_node;
    int local_board[max_x+1][max_y+1];
    int temp;
    for(i=1; i<=max_x; i++)
    {
        for(j=1; j<=max_y; j++)
        {
            local_board[i][j]=func_board[i][j];
        }
    }
    for(i=1; i<=max_x; i++)
    {
        for(j=1; j<=max_y; j++)
        {
            if(is_catch(local_board,player,i,j))
            {
                /*
                   if(layer==0)
                   {
                       printf("x:%d y:%d\n",i,j);
                       fflush(stdout);
                   }*/
                _catch(local_board,player,i,j);
                if(player==1)
                {
                    temp=ai_place(local_board,2,layer+1,alpha,beta,local_is_first_node,max_layer);
                }
                else
                {
                    temp=ai_place(local_board,1,layer+1,alpha,beta,local_is_first_node,max_layer);
                }
                for(k=1; k<=max_x; k++)
                {
                    for(l=1; l<=max_y; l++)
                    {
                        local_board[k][l]=func_board[k][l];
                    }
                }
                if(local_maxscore_first_flag||temp>local_maxscore)
                {
                    local_maxscore=temp;
                    local_maxscore_first_flag=0;
                    if(layer==0)
                    {
                        printf("local_max:%d x:%d y:%d\n",temp,i,j);
                        fflush(stdout);
                        ai_x=i;
                        ai_y=j;
                    }
                }
                if(local_minscore_first_flag||temp<local_minscore)
                {
                    local_minscore_first_flag=0;
                    local_minscore=temp;
                }
            }
        }
    }

    int t=time.elapsed();/*
    if(layer!=0)
    {
        printf("t:%7.2f alpha:%4d beta:%4d ",t/1000.0,alpha_count,beta_count);
        printf("score:%4d x1:%2d y1:%2d x2:%2d y2:%2d ",local_maxscore,ai_x1,ai_y1,ai_x2,ai_y2);
        printf("local x1:%2d y1:%2d x2:%2d y2:%2d\n",i,j,k,l);
        fflush(stdout);
    }*/
    if(layer%2==0)
    {
        return local_minscore;
    }
    else
    {
        return local_maxscore;
    }
}

void MainWindow::mousePressEvent(QMouseEvent *e)
{

    mouse_click_x=(e->pos().x())/zoom;
    mouse_click_y=(e->pos().y())/zoom;

    if(condition==1&&left_chess>=1)
    {
        if(is_catch(board,1,mouse_click_x,mouse_click_y))
        {
            _catch(board,1,mouse_click_x,mouse_click_y);
            board[mouse_click_x][mouse_click_y]=1;

            repaint();
            left_chess--;
            total_chess++;
            //printf("Press x:%d , y:%d (%d,%d) condition:%d player:%d left_chess:%d\n",e->pos().x(),e->pos().y(),mouse_click_x,mouse_click_y,condition,board[mouse_click_x][mouse_click_y],left_chess);
            /*
            int i,j;
            for(i=1;i<=max_x;i++)
            {
                for(j=1;j<=max_y;j++)
                {
                    printf("%d ",board[i][j]);
                }
                printf("\n");
            }
            int v_max_x=0,v_min_x=0, v_max_y=0, v_min_y=0;
            chess_center(&v_max_x,&v_min_x,&v_max_y,&v_min_y);
            printf("max_x:%d min_x:%d max_y:%d min_y:%d\n",v_max_x,v_min_x,v_max_y,v_min_y);

            fflush(stdout);*/
        }
    }
    if(left_chess<=0)
    {
        printf("P2's Turn\n");
        fflush(stdout);
        condition=2;
        time.start();
        int alpha=0,beta=0;
        alpha_count=0;
        beta_count=0;
        ai_place(board,2,0,&alpha,&beta,1,3);

        printf("x:%d y:%d\n",ai_x,ai_y);
        fflush(stdout);
        if(ai_x!=0&&ai_y!=0)
        {
            _catch(board,2,ai_x,ai_y);
            board[ai_x][ai_y]=2;
            ai_x=0;
            ai_y=0;
        }

        repaint();
        total_chess+=1;
        left_chess=1;
        condition=1;
        printf("P1's Turn\n");
        fflush(stdout);
    }
}
void MainWindow::mouseMoveEvent(QMouseEvent *e)
{
    /*
    zoom_revise_x=mouse_click_x-e->pos().x();
    zoom_revise_y=mouse_click_y-e->pos().y();

    zoom_center_x+=zoom_revise_x;
    zoom_center_y+=zoom_revise_y;
    zoom_revise_x=0;
    zoom_revise_y=0;
    //printf("Move x:%d , y:%d",e->pos().x(),e->pos().y());
    //fflush(stdout);
    this->repaint();*/
}
void MainWindow::mouseReleaseEvent(QMouseEvent *e)
{
    /*
    zoom_center_x+=zoom_revise_x;
    zoom_center_y+=zoom_revise_y;
    zoom_revise_x=0;
    zoom_revise_y=0;
    printf("center x:%d , y:%d",zoom_center_x,zoom_center_y);
    fflush(stdout);
    this->repaint();
    //printf("Release x:%d , y:%d",e->pos().x(),e->pos().y());
    //fflush(stdout);
    */
}
void MainWindow::paintEvent(QPaintEvent *e)
{
    int i = 0, j = 0;
    QPainter painter(this);
    painter.setPen(QPen(Qt::red, 5));
    /*
    int revise_x = 0, revise_y = 0;
    if (max_x * zoom > windowsize_x)
    {
        revise_x = zoom_center_x;
    }
    if (max_y * zoom > windowsize_y)
    {
        revise_y = zoom_center_y;
    }
    //滑鼠座標= zoom_center_x
    */


    for (i = 1; i <= max_x+1; i++)
    {
        painter.drawLine(i * zoom, zoom, i * zoom, max_y * zoom+zoom);
    }
    for (j = 1; j <= max_y+1; j++)
    {
        painter.drawLine(zoom, j * zoom, max_x * zoom+zoom, j * zoom);
    }
    painter.setPen(QPen(Qt::black, zoom*3/5));
    for (i = 1; i <= max_x; i++)
    {
        for (j = 1; j <= max_y; j++)
        {
            if (board[i][j]==1)
            {
                painter.drawPoint(zoom/2+i * zoom, zoom/2+j * zoom);
            }
        }
    }
    painter.setPen(QPen(Qt::magenta, zoom*3/5));
    for (i = 1; i <= max_x; i++)
    {
        for (j = 1; j <= max_y; j++)
        {
            if (board[i][j]==2)
            {
                painter.drawPoint(zoom/2+i * zoom, zoom/2+j * zoom);
            }
        }
    }

}
void MainWindow::wheelEvent(QWheelEvent *e)
{
    if (e->delta() < 0)
    {
        if (zoom > 25)
        {
            zoom--;
        }
    }
    else if (e->delta() > 0)
    {
        if (zoom < 45)
        {
            zoom++;
        }
    }
    zoom_center_x=e->x();
    zoom_center_y=e->y();
    //printf("zoom:%d x:%d,y:%d", zoom,e->x(),e->y());
    fflush(stdout);
    this->repaint();

}
