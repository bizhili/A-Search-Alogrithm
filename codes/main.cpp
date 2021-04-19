/***copyright @ bizhi***/
/***2021/3/27***/
#include "opencv_include_all.h"
#include <iostream>
#include <list>
using namespace cv;
using namespace std;

/***initializing map parameters***/
#define s_len 800//square board pixels length
#define block_pixels 19//square block pixels length and width
#define random_line_length 3 //random barrier length
#define random_line_num 200 //amount of random barrier
#define random_seed 7//random seed
/***initializing A* algorithm parameters***/
unsigned int xs=10,ys=10;
unsigned int xe=0,ye=0;
/***struct of nodes***/
typedef struct my_block
{
    unsigned short x;
    unsigned short y;
    unsigned short steps;
    double score;
}block;
/***function:coloring a block***/
void colorBox(Mat image,int x,int y,Scalar Color);
/***function:judge node exiting in list or not***/
int is_not_exist(list<block> table,int x,int y);
/***function:check next step legally and push into list***/
int check_and_do(int x,int y,list<block> &table_o,list<block> &table_t,int steps,uchar *copy_data,Mat image);
/***parameter:calculate the block's length***/
int box_num=s_len/19;
int fast_table[8][2]={{0,1},{0,-1},{1,1},{-1,-1},{-1,0},{-1,1},{1,-1},{1,0}};
int main()
{
    /***create an empty board to demonstrate procedure***/
    Mat empty_p(s_len,s_len,CV_8UC3, Scalar(255,255,255));
    /***create an empty small board to store information***/
    Mat copy_p(box_num,box_num,CV_8UC1, Scalar(255));
    uchar *copy_data = copy_p.data;
    /***initialize board***/
    for(int i=0;i<s_len;i+=19)
        line(empty_p,Point(i,0),Point(i,s_len-1),Scalar(0, 0, 0),1, LINE_8);
    for(int i=0;i<s_len;i+=19)
        line(empty_p,Point(0,i),Point(s_len-1,i),Scalar(0, 0, 0),1, LINE_8);
    //generate random numbers
    theRNG().state = random_seed;
    Mat1i row_rand(random_line_num,1);
    Mat1i col_rand(random_line_num,1);
    Mat1i dir_rand(random_line_num,1);
    randu(row_rand, Scalar(2), Scalar(box_num-2));
    randu(col_rand, Scalar(2), Scalar(box_num-2));
    randu(dir_rand, Scalar(0), Scalar(2));
    //draw map
    for (int i=0;i<random_line_num;i++)
    {
        int init_x=*col_rand[i],init_y=*row_rand[i];
        if(*dir_rand[i])
            for(int j=0;j<random_line_length;j++)
            {
                colorBox(empty_p,init_x+j,init_y,Scalar(150,150,150));
                copy_data[box_num*(init_x+j)+init_y]=0;
            }
        else
            for(int j=0;j<random_line_length;j++)
            {
                colorBox(empty_p,init_x,init_y+j,Scalar(150,150,150));
                copy_data[box_num*init_x+init_y+j]=0;
            }
    }
    namedWindow( "blank", CV_WINDOW_AUTOSIZE );
    waitKey(1);
    /***table_o:store open table;table_t:store terminal table***/
    list<block>table_o,table_t;
    list<block>::iterator iter,iter2;
    int total_loop=0;
    block temp_block1;
    //limit range
    xs=xs<(box_num-1) ? xs:(box_num-1);
    ys=ys<(box_num-1) ? ys:(box_num-1);
    xe=xe<(box_num-1) ? xe:(box_num-1);
    ye=ye<(box_num-1) ? ye:(box_num-1);
    temp_block1.x=xs;
    temp_block1.y=ys;
    temp_block1.steps=0;
    temp_block1.score=sqrt(33*33+33*33);
    //put first node into open table
    table_o.push_back(temp_block1);
    while(table_o.size())
    {
        //find minimal score node in open table
        double score_now=10000000.0f;
        //find minimum score
        for(iter2=table_o.begin();iter2!=table_o.end();iter2++)
            if(iter2->score<score_now)
            {
                score_now=iter2->score;
                iter=iter2;
            }
        int x=iter->x,y=iter->y,steps=iter->steps;
        //drop traced node from open table
        table_o.erase(iter);
        //put traced node into terminal table
        table_t.push_front(*iter);
        //color this block to show that this block has been traced
        colorBox(empty_p,x,y,Scalar(0,250,0));
        imshow("blank", empty_p);
        waitKey(1);
        //terminating loop condition
        if(x==xe and y==ye)
            break;
        //check 8 direction and put proper node into open table
        for(int i=0;i<8;i++)
            check_and_do(x+fast_table[i][0],y+fast_table[i][1],table_o,table_t,steps,copy_data,empty_p);
        ++total_loop;
    }
    //back-trace least cost road
    int last_steps=table_t.begin()->steps+1,last_x=0,last_y=0,least_step=0;
    for(iter2=table_t.begin();iter2!=table_t.end();iter2++)
        if(last_steps>iter2->steps&&fabs(last_x-iter2->x)<=1&&fabs(last_y-iter2->y)<=1)
        {
            colorBox(empty_p,iter2->x,iter2->y,Scalar(0,0,255));
            last_steps=iter2->steps;
            last_x=iter2->x;
            last_y=iter2->y;
            ++least_step;
        }
    cout<<"total loops:"<<total_loop<<endl;
    cout<<"least steps:"<<least_step<<endl;
    imshow("blank", empty_p);
	waitKey();
	return 0;
}

void colorBox(Mat image,int x,int y,Scalar Color)
{
    rectangle(image,Point(x*block_pixels+1,y*block_pixels+1),Point(x*block_pixels+block_pixels-1,y*block_pixels+block_pixels-1),Color,CV_FILLED, 8, 0);
}

int is_not_exist(list<block> table,int x,int y)
{
    list<block>::iterator iter;
    for(iter=table.begin();iter!=table.end();iter++)
        if(iter->x==x && iter->y==y)
            return 0;
    return 1;
}

/***function:check next step legally and push into list***/
int check_and_do(int x,int y,list<block> &table_o,list<block> &table_t,int steps,uchar *copy_data,Mat image)
{
    if(y>=0 &&y<=box_num-1 && x<=box_num-1 && x>=0)
    {
        //not gray block and not added
        if(copy_data[box_num*(x)+y]!=0 && is_not_exist(table_o,x,y)&&is_not_exist(table_t,x,y))
        {
            block temp_block;
            temp_block.x=x;
            temp_block.y=y;
            temp_block.steps=steps+1;
            int dx=x-xe,dy=y-ye;
            /***Here we can choose different heuristic functions***/
            //temp_block.score=sqrt(dx*dx+dy*dy)+steps+1;
            temp_block.score=sqrt(dx*dx+dy*dy)/1000+steps+1;
            //temp_block.score=sqrt(dx*dx+dy*dy)*1000+steps+1;
            //temp_block.score=fabs(dx)+fabs(dy)+steps+1;
            //temp_block.score=fabs(dx)+steps+1;
            //temp_block.score=fabs(dy-dx)+steps+1;
            //temp_block.score=fabs(dy*dx)+steps+1;
            //temp_block.score=fabs(dx*dx)+steps+1;
            //temp_block.score=fabs(dx/(dy+1))+steps+1;
            table_o.push_back(temp_block);
            colorBox(image,x,y,Scalar(120,255,255));
        }
    }
    return 0;
}

