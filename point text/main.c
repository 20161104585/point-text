//
//  main.c
//  point text
//
//  Created by 20161104585 on 2018/6/25.
//  Copyright © 2018年 20161104585. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>

typedef struct player
{
    int id;             //选手编号
    char name[10];      //选手姓名
    char sex[10];       //选手性别
    char Proname[10];   //节目名称
    char Procate[10];   //节目类别
    int num;            //电话号码
    char class[10];     //班级
    
    
    double score[10];   //选手成绩
    double ave;         //平均成绩
    struct player *next;
}stu;

int menu()
{
    int Menu;
    
    printf("》》》》》》》》》欢迎进入评委打分系统！！！《《《《《《《《《");
    printf("\n ");
    printf("         | ***********评委打分系统********* |          \n");
    printf("          | -----------------------------------|          \n");
    printf("          |              主菜单项              |          \n");
    printf("          | -----------------------------------|          \n");
    printf("          |	  1 --- 显示选手信息  	       |          \n");
    printf("          |	  2 --- 评委打分	           |          \n");
    printf("          |	  3 --- 成绩排序	           |          \n");
   // printf("          |	  4 --- 删除课程信息	       |          \n");
    printf("          |	  4 --- 保存选手成绩	       |          \n");
    printf("          |	  0 --- 退出系统  	       |          \n");
    
    do
    {
        printf("\n请输入选项（0－5）：");
        fflush(stdin);
        scanf("%d",&Menu);
    }while(Menu<0||Menu>5);
    
    return Menu;
}
void input()
{
    int i,j;
    double t;
    char c='y';
    
    while(c == 'y' || c == 'Y')
    {
        stu *p1=(stu *)malloc(sizeof(stu));
        printf("\n请输入要录入的选手信息：\n");
        printf("\n选手编号：");
        scanf("%d",&p1->id);
        
        printf("\n 输入10位评委点评成绩：");
        for(i=0; i<10; i++)
        {
            scanf("%lf",&p1->score[i]);
        }
        
        
        for(i=0; i<10; i++)
            for(j=0; j<9-i;j++)
            {
                if(p1->score[j]>p1->score[j+1])
                {
                    t=p1->score[j];
                    p1->score[j]=p1->score[j+1];
                    p1->score[j+1]=t;
                }
            }
        p1->ave=0;
        for(i=1;i<10;i++)
        {
            p1->ave=p1->ave+p1->score[i];
        }
        
    }
}
void output()
{
    
}
void sort()
{
    
}
/******************************************/
//
//读取选手信息到链表（录入excel文件）
//
//
/******************************************/
void load()
{
    FILE *fp=fopen("/Users/a20161104585/Desktop/point text/point text/player.xlsx", "r");
    int i,j;
    char na[10];       //选手姓名
    char se[10];       //选手性别
    char Pname[10];    //节目名称
    char Pcate[10];    //节目类别
    int nu;            //电话号码
    char cla[10];      //班级
    if(fp==NULL)
    {
        printf("文件读取错误，请检查文件player.xlsx是否存在!");
    }
    else
    {
        printf("文件载入成功!\n");
        fseek(fp, 10L, SEEK_SET);
        while(fscanf(fp,"%s %s %s %s %d %s\n",na,se,Pname,Pcate,&nu,cla)!=EOF)
        {
            stu *p,*q;
            q=(stu *)malloc(sizeof(stu));
            strcpy(q->name,na);
            strcpy(q->sex,se);
            strcpy(q->Proname,Pname);
            strcpy(q->Procate,Pcate);
            q->next=NULL;
            p->next=q;
            p=p->next;
        }
    }
}


/******************************************/
//
//保存选手信息到文件（存入excel文件）
//
//
/******************************************/
void save()
{
    
}

int main()
{
    int c;
    switch (c)
    {
        case 1:
            input();
            break;
        case 2:
            output();
            break;
        case 3:
            sort();
            break;
        case 4:
            save();
            break;
    }
    return 0;
}
