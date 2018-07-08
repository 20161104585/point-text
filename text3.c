#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>

#define	MAXSIZE  100   /*此处的宏定义常量表示线性表可能达到的最大长度*/




//*********************结构体定义模块*********************//
//定义选手结构体 
struct student
{
	
	int id;             //选手编号
    char name[10];      //选手姓名
    char sex[10];       //选手性别
    char Proname[10];   //节目名称
    char Procate[10];   //节目类别
    int num;            //电话号码
    char cla[10];     //班级
    
    
    int score[5];   //选手成绩
    int max;		//最大成绩 
    int min;		//最小成绩 
    double ave;         //平均成绩			
};

typedef struct student ElemType;
typedef  struct
{ 
	ElemType  elem[MAXSIZE];  /*线性表占用的数组空间*/
	int       last;    /*记录线性表中最后一个元素在数组elem[ ]中的位置（下标值），空表置为-1*/
}seqlist;
//定义评委结构体 
struct judges
{
	
    char name[10];      //评委姓名
    char sex[10];       //评委性别

    int num;            //电话号码		
};

typedef struct judges ElemTypes;
typedef  struct
{ 
	ElemTypes  ele[MAXSIZE];  /*线性表占用的数组空间*/
	int       jlast;    /*记录线性表中最后一个元素在数组elem[ ]中的位置（下标值），空表置为-1*/
}slist;




//*********************文件加载模块*********************//
//加载选手信息 
void load(seqlist *L)
{
	FILE* fp = fopen("Play_information.csv", "r");
	int i = 0;
	int bh;				//选手编号 
	char na[10];       //选手姓名
    char se[10];       //选手性别
    char Pname[10];    //节目名称
    char Pcate[10];    //节目类别
    int nu;            //电话号码
    char cl[10];      //班级
	
	if(fp == NULL)
		printf("！！！加载文件失败！！！\n");
	else
	{
		while(fscanf(fp,"%d %s %s %s %s %d %s\n",&bh, na, se, Pname, Pcate, &nu, cl)!=EOF)
		{
			L->elem[i].id = bh;
			strcpy(L->elem[i].name, na);
			strcpy(L->elem[i].sex, se);
			strcpy(L->elem[i].Proname, Pname);
			strcpy(L->elem[i].Procate, Pcate);
			L->elem[i].num = nu;
			strcpy(L->elem[i].cla, cl);

			i++;
			L->last++;
		}
		printf("文件加载成功！\n");
		fclose(fp);
	}
}


//加载评委信息 
void load2(slist *K)
{
	FILE* fp = fopen("Judges_information.csv", "r");
	int i = 0;
	char na[10];       //评委姓名
    char se[10];       //评委性别

    int nu;            //电话号码
	
	if(fp == NULL)
		printf("！！！加载文件失败！！！\n");
	else
	{
		while(fscanf(fp,"%s %s %d", na, se, &nu)!=EOF)
		{
			strcpy(K->ele[i].name, na);
			strcpy(K->ele[i].sex, se);
			K->ele[i].num = nu;

			i++;
			K->jlast++;
		}
		printf("文件加载成功！\n");
		fclose(fp);
	}
}


//*********************菜单模块*********************//
void mean()
{
	seqlist L;
	slist K;
	L.last=0;
	load(&L);		//加载文件中选手数据
	load2(&K);		//加载文件中评委数据
	int t;
	while(1)
	{
		printf("\t|***********************  评委打分系统  ***********************|\n");
		printf("\t|  1--------------------显示选手信息                           |\n");
		printf("\t|  2--------------------显示评委信息                           |\n");
		printf("\t|  3--------------------评委打分                               |\n");
		printf("\t|  4--------------------按成绩排序                             |\n");
		printf("\t|  5--------------------保存选手成绩到文件                     |\n");
		printf("\t|  6--------------------保存评委信息到文件                     |\n");
		printf("\t|  0--------------------退出                                   |\n");
		printf("\t|**************************************************************|\n");
		printf("请输入0-6:");
		scanf("%d",&t);
		switch(t)
		{
			case 1 : 
					output(&L);  
					break;
			case 2 : 
					outputJ(&K); 
					break;
			case 3 : 
					scor(&L); 
					break;
			case 4 : 
					output2(&L);
					break;
			case 5 : 
					save(&L); 
					break;
			case 6 : 
					saveJ(&K,&L); 
					break;
			case 0 :  
					return 0;
		}
	}
}


//*********************输出模块*********************//
void output(seqlist *L)
{
	int i;
	printf("|    编号    |   姓名   |   性别   | 节目名称 | 节目类别 | 电话号码 |   班级   |\n");
	for(i=0; i<L->last; i++)
	{
		printf("|%12d|%10s|%10s|%10s|%10s|%10d|%10s|\n",L->elem[i].id,L->elem[i].name,L->elem[i].sex,L->elem[i].Proname,L->elem[i].Procate,L->elem[i].num,L->elem[i].cla);
	}
}


//*********************成绩排序模块1*********************//
void output2(seqlist *L)
{
	quicksort(L, 0,L->last-1);
	int i;
	printf("|   编号   |   姓名   |  成绩1  |  成绩2  |  成绩3  |  成绩4  | 平均成绩 |\n");
	for(i=0; i<L->last; i++)
	{
		printf("|%10d|%10s|%9d|%9d|%9d|%9d|%10.2lf|\n",L->elem[i].id,L->elem[i].name,L->elem[i].score[0],L->elem[i].score[1],L->elem[i].score[2],L->elem[i].score[3],L->elem[i].ave);
	}
}




void outputJ(slist *K)
{
	int i;
	printf("|   姓名   |   性别   | 电话号码 |\n");
	for(i=0; i<K->jlast; i++)
	{
		printf("|%10s|%10s|%10d|\n",K->ele[i].name,K->ele[i].sex,K->ele[i].num);
	}
}



//*********************查找选手信息模块*********************//
int Find(seqlist* L,int N)
{ 	
	int i=0;        									/*i为扫描计数器，初值为0，即从第一个元素开始比较*/
	while ((i <= L->last) && (L->elem[i].id != N))		/*顺序扫描表，直到找到值为key的元素, 或扫描到表尾而没找到*/
	{
		i++; 
	}
	
	if  (i<=L->last)
	{
//		printf("该元素在线性表中的位置为:%d\n",i);
		return(i+1);  							/*若找到值为e的元素，则返回其序号*/
	}

	else
	{
//		printf("在此线性表中没有该元素!\n");
		return(-1);  							/*若没找到，则返回空序号*/

	}
}


//*********************评委打分模块*********************//
void scor(seqlist *L)
{
	int n ,i,j;
	int c=1;
	while(c)
	{
		printf("------请输入打分学生编号：\n");
		scanf("%d", &n);
		i=Find(L,n);
		if(i!=-1)
		{
			i=i-1;
			printf("------请给%d号选手打分：\n",n);
			printf("------一号评委：");
			scanf("%d", &L->elem[i].score[0]);
			
			printf("------二号评委：");
			scanf("%d", &L->elem[i].score[1]);
			
			printf("------三号评委：");
			scanf("%d", &L->elem[i].score[2]);
			
			printf("------四号评委：");
			scanf("%d", &L->elem[i].score[3]);
			
			
			L->elem[i].max = L->elem[i].score[0];
			L->elem[i].min = L->elem[i].score[0];
			for(j=0;j<=3;j++)
			{
				if(L->elem[i].max  < L->elem[i].score[j])
					L->elem[i].max  =L->elem[i].score[j];
				if(L->elem[i].min  > L->elem[i].score[j])
					L->elem[i].min  =L->elem[i].score[j];
			}
			printf("------去掉一个最高分%d，去掉一个最低分%d\n",L->elem[i].max,L->elem[i].min);
			L->elem[i].ave = (L->elem[i].score[0] + L->elem[i].score[1] + L->elem[i].score[2] + L->elem[i].score[3] - L->elem[i].max - L->elem[i].min)/2;
			printf("------%d选手的平均成绩为：%.2lf\n\n",n,L->elem[i].ave);	
			
		}
		else
		{
			printf("------未找到该选手！！！\n");
		}
		
		
		printf("1---继续打分\n0---退出\n");
		scanf("%d", &c);	
	}

}


//*********************成绩排序模块2*********************//
//快排 
void quicksort(seqlist* L,int left, int right)
{
	ElemType t, temp;
	int i, j;
	
	if(left>right)
		return;
	temp = L->elem[left];
	j = right;
	i = left;
	
	while(i!=j)
	{
		while(L->elem[j].ave <=temp.ave && i<j)
			j--;
		while(L->elem[i].ave >=temp.ave && i<j)
			i++;
		if(i<j)
		{
			t = L->elem[j];
			L->elem[j] = L->elem[i];
			L->elem[i] = t;
		}
	}
	
	L->elem[left] = L->elem[i];
	L->elem[i] = temp;
	
	quicksort(L, left, i-1);
	quicksort(L, i+1, right);
}


//*********************保存选手成绩*********************//
void save(seqlist* L)
{
	int i;
	
	FILE* fp;
	fp = fopen("Play_scort.csv", "w");
	if(fp == NULL)
		printf("！！！加载文件失败！！！\n");
	else
	{
		fprintf(fp,"编号 姓名 成绩1 成绩2 成绩3 成绩4 平均成绩\n");
		for(i=0; i<L->last; i++)
		{
			fprintf(fp,"%d %s %d %d %d %d %.2lf\n",L->elem[i].id,L->elem[i].name,L->elem[i].score[0],L->elem[i].score[1],L->elem[i].score[2],L->elem[i].score[3],L->elem[i].ave);
		}
		printf("------信息保存成功!\n");
		fclose(fp);
		return 0;
	}
}


//*********************保存裁判信息*********************//
void saveJ(slist* K,seqlist* L)
{
	int i,j;
	
	FILE* fp;
	fp = fopen("Judges_scort.csv", "w");
	if(fp == NULL)
		printf("！！！加载文件失败！！！\n");
	else
	{
		for(i=0; i<K->jlast; i++)
		{
			fprintf(fp,"%s %s %d ",K->ele[i].name,K->ele[i].sex,K->ele[i].num);
			for(j=0; j<L->last; j++)
			{
				fprintf(fp,"%d ",L->elem[j].score[i]);
			
			}
			fprintf(fp,"\n");
		}
		printf("------信息保存成功!\n");
		fclose(fp);
		return 0;
	}
}

//*********************主函数*********************//
int main()
{	
	mean();
	return 0;
}
