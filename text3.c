#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>

#define	MAXSIZE  100   /*�˴��ĺ궨�峣����ʾ���Ա���ܴﵽ����󳤶�*/




//*********************�ṹ�嶨��ģ��*********************//
//����ѡ�ֽṹ�� 
struct student
{
	
	int id;             //ѡ�ֱ��
    char name[10];      //ѡ������
    char sex[10];       //ѡ���Ա�
    char Proname[10];   //��Ŀ����
    char Procate[10];   //��Ŀ���
    int num;            //�绰����
    char cla[10];     //�༶
    
    
    int score[5];   //ѡ�ֳɼ�
    int max;		//���ɼ� 
    int min;		//��С�ɼ� 
    double ave;         //ƽ���ɼ�			
};

typedef struct student ElemType;
typedef  struct
{ 
	ElemType  elem[MAXSIZE];  /*���Ա�ռ�õ�����ռ�*/
	int       last;    /*��¼���Ա������һ��Ԫ��������elem[ ]�е�λ�ã��±�ֵ�����ձ���Ϊ-1*/
}seqlist;
//������ί�ṹ�� 
struct judges
{
	
    char name[10];      //��ί����
    char sex[10];       //��ί�Ա�

    int num;            //�绰����		
};

typedef struct judges ElemTypes;
typedef  struct
{ 
	ElemTypes  ele[MAXSIZE];  /*���Ա�ռ�õ�����ռ�*/
	int       jlast;    /*��¼���Ա������һ��Ԫ��������elem[ ]�е�λ�ã��±�ֵ�����ձ���Ϊ-1*/
}slist;




//*********************�ļ�����ģ��*********************//
//����ѡ����Ϣ 
void load(seqlist *L)
{
	FILE* fp = fopen("Play_information.csv", "r");
	int i = 0;
	int bh;				//ѡ�ֱ�� 
	char na[10];       //ѡ������
    char se[10];       //ѡ���Ա�
    char Pname[10];    //��Ŀ����
    char Pcate[10];    //��Ŀ���
    int nu;            //�绰����
    char cl[10];      //�༶
	
	if(fp == NULL)
		printf("�����������ļ�ʧ�ܣ�����\n");
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
		printf("�ļ����سɹ���\n");
		fclose(fp);
	}
}


//������ί��Ϣ 
void load2(slist *K)
{
	FILE* fp = fopen("Judges_information.csv", "r");
	int i = 0;
	char na[10];       //��ί����
    char se[10];       //��ί�Ա�

    int nu;            //�绰����
	
	if(fp == NULL)
		printf("�����������ļ�ʧ�ܣ�����\n");
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
		printf("�ļ����سɹ���\n");
		fclose(fp);
	}
}


//*********************�˵�ģ��*********************//
void mean()
{
	seqlist L;
	slist K;
	L.last=0;
	load(&L);		//�����ļ���ѡ������
	load2(&K);		//�����ļ�����ί����
	int t;
	while(1)
	{
		printf("\t|***********************  ��ί���ϵͳ  ***********************|\n");
		printf("\t|  1--------------------��ʾѡ����Ϣ                           |\n");
		printf("\t|  2--------------------��ʾ��ί��Ϣ                           |\n");
		printf("\t|  3--------------------��ί���                               |\n");
		printf("\t|  4--------------------���ɼ�����                             |\n");
		printf("\t|  5--------------------����ѡ�ֳɼ����ļ�                     |\n");
		printf("\t|  6--------------------������ί��Ϣ���ļ�                     |\n");
		printf("\t|  0--------------------�˳�                                   |\n");
		printf("\t|**************************************************************|\n");
		printf("������0-6:");
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


//*********************���ģ��*********************//
void output(seqlist *L)
{
	int i;
	printf("|    ���    |   ����   |   �Ա�   | ��Ŀ���� | ��Ŀ��� | �绰���� |   �༶   |\n");
	for(i=0; i<L->last; i++)
	{
		printf("|%12d|%10s|%10s|%10s|%10s|%10d|%10s|\n",L->elem[i].id,L->elem[i].name,L->elem[i].sex,L->elem[i].Proname,L->elem[i].Procate,L->elem[i].num,L->elem[i].cla);
	}
}


//*********************�ɼ�����ģ��1*********************//
void output2(seqlist *L)
{
	quicksort(L, 0,L->last-1);
	int i;
	printf("|   ���   |   ����   |  �ɼ�1  |  �ɼ�2  |  �ɼ�3  |  �ɼ�4  | ƽ���ɼ� |\n");
	for(i=0; i<L->last; i++)
	{
		printf("|%10d|%10s|%9d|%9d|%9d|%9d|%10.2lf|\n",L->elem[i].id,L->elem[i].name,L->elem[i].score[0],L->elem[i].score[1],L->elem[i].score[2],L->elem[i].score[3],L->elem[i].ave);
	}
}




void outputJ(slist *K)
{
	int i;
	printf("|   ����   |   �Ա�   | �绰���� |\n");
	for(i=0; i<K->jlast; i++)
	{
		printf("|%10s|%10s|%10d|\n",K->ele[i].name,K->ele[i].sex,K->ele[i].num);
	}
}



//*********************����ѡ����Ϣģ��*********************//
int Find(seqlist* L,int N)
{ 	
	int i=0;        									/*iΪɨ�����������ֵΪ0�����ӵ�һ��Ԫ�ؿ�ʼ�Ƚ�*/
	while ((i <= L->last) && (L->elem[i].id != N))		/*˳��ɨ���ֱ���ҵ�ֵΪkey��Ԫ��, ��ɨ�赽��β��û�ҵ�*/
	{
		i++; 
	}
	
	if  (i<=L->last)
	{
//		printf("��Ԫ�������Ա��е�λ��Ϊ:%d\n",i);
		return(i+1);  							/*���ҵ�ֵΪe��Ԫ�أ��򷵻������*/
	}

	else
	{
//		printf("�ڴ����Ա���û�и�Ԫ��!\n");
		return(-1);  							/*��û�ҵ����򷵻ؿ����*/

	}
}


//*********************��ί���ģ��*********************//
void scor(seqlist *L)
{
	int n ,i,j;
	int c=1;
	while(c)
	{
		printf("------��������ѧ����ţ�\n");
		scanf("%d", &n);
		i=Find(L,n);
		if(i!=-1)
		{
			i=i-1;
			printf("------���%d��ѡ�ִ�֣�\n",n);
			printf("------һ����ί��");
			scanf("%d", &L->elem[i].score[0]);
			
			printf("------������ί��");
			scanf("%d", &L->elem[i].score[1]);
			
			printf("------������ί��");
			scanf("%d", &L->elem[i].score[2]);
			
			printf("------�ĺ���ί��");
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
			printf("------ȥ��һ����߷�%d��ȥ��һ����ͷ�%d\n",L->elem[i].max,L->elem[i].min);
			L->elem[i].ave = (L->elem[i].score[0] + L->elem[i].score[1] + L->elem[i].score[2] + L->elem[i].score[3] - L->elem[i].max - L->elem[i].min)/2;
			printf("------%dѡ�ֵ�ƽ���ɼ�Ϊ��%.2lf\n\n",n,L->elem[i].ave);	
			
		}
		else
		{
			printf("------δ�ҵ���ѡ�֣�����\n");
		}
		
		
		printf("1---�������\n0---�˳�\n");
		scanf("%d", &c);	
	}

}


//*********************�ɼ�����ģ��2*********************//
//���� 
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


//*********************����ѡ�ֳɼ�*********************//
void save(seqlist* L)
{
	int i;
	
	FILE* fp;
	fp = fopen("Play_scort.csv", "w");
	if(fp == NULL)
		printf("�����������ļ�ʧ�ܣ�����\n");
	else
	{
		fprintf(fp,"��� ���� �ɼ�1 �ɼ�2 �ɼ�3 �ɼ�4 ƽ���ɼ�\n");
		for(i=0; i<L->last; i++)
		{
			fprintf(fp,"%d %s %d %d %d %d %.2lf\n",L->elem[i].id,L->elem[i].name,L->elem[i].score[0],L->elem[i].score[1],L->elem[i].score[2],L->elem[i].score[3],L->elem[i].ave);
		}
		printf("------��Ϣ����ɹ�!\n");
		fclose(fp);
		return 0;
	}
}


//*********************���������Ϣ*********************//
void saveJ(slist* K,seqlist* L)
{
	int i,j;
	
	FILE* fp;
	fp = fopen("Judges_scort.csv", "w");
	if(fp == NULL)
		printf("�����������ļ�ʧ�ܣ�����\n");
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
		printf("------��Ϣ����ɹ�!\n");
		fclose(fp);
		return 0;
	}
}

//*********************������*********************//
int main()
{	
	mean();
	return 0;
}
