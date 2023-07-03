#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
	int weight;
	int parent;
	int lchild;
	int rchild;
}HTNode,*HuffmanTree;


void Menu();

int CreateHT(HuffmanTree* HT,int num);

void Select(HuffmanTree HT, int num, int* order1, int* order2);

void ShowHT(HuffmanTree HT,int num,char *ch);

void SaveHT(HuffmanTree HT,int num,char *ch);

void Coding(HuffmanTree HT,int num,char ***code);

void ShowCode(char **code,int num);

int main()
{
	int flag = 1;
	HuffmanTree HT;
	int num ;
	int opt ;
	char ch[100]={0};
	char **code;
	HT=NULL;	//初始化HuffmanTree 
	//char decode[100];
	while (flag)
	{
		Menu();
		printf("请输入选项：\n");
		scanf("%d", &opt);
		getchar();
		
		switch (opt)
		{
		case 1:
			printf("请输入字符的个数：\n");
			scanf("%d", &num);
			getchar();
			printf("请依次输入%d个字符：\n", num);
			for (int i = 1; i <= num; i++)
			{
				scanf("%c", &ch[i]);
				getchar();
			}
			printf("请依次输入%d个字符的权值：\n", num);
			CreateHT(&HT,num);
			break;
		case 2:
			ShowHT(HT,num,ch);
			break;
		case 3:
			SaveHT(HT,num,ch);
			printf("保存成功！\n") ;
			break;
		case 4:
			Coding(HT,num,&code);
			printf("编码成功！\n");
			break;
		case 5:
			printf("HuffmanTree代码具有不唯一性！");
			printf("下面展示的仅为其中一种："); 
			ShowCode(code,num);
			break;
		case 6:
			system("cls");
			break;
		case 0:
			flag=0;
			break; 
		default:
			printf("请输入正确序号！\n");
			break;
		}
	}
	return 0;
}

void Menu()
{
	printf("HuffmanTree Operation\n");
	printf("1.创建HuffmanTree\n");
	printf("2.显示HuffmanTree\n");
	printf("3.保存HuffmanTree到data.txt\n");
	printf("4.编码\n");
	printf("5.显示编码内容\n");
	printf("6.清空当前屏幕\n");
	printf("0.退出程序\n");
}

int CreateHT(HuffmanTree* HT,int num)
{
	int order1, order2;
	if (num <= 1)
	{
		return 0;
	}
	int sum = 2 * num - 1;	//节点总数等于输入节点的二倍减一
	*HT = (HuffmanTree)malloc( (sum+1)*sizeof(HTNode));
	for (int i = 1; i <= sum; i++)
	{
		(*HT)[i].weight = 0;
		(*HT)[i].parent = 0;
		(*HT)[i].lchild = 0;
		(*HT)[i].rchild = 0;
	}
	for (int i = 1; i <= num; i++)
	{
		scanf("%d", &(*HT)[i].weight);
		getchar();
	}
	for (; num < sum; num++)	//这里需要计算出除了已知节点外的节点 
	{
		Select(*HT, num , &order1, &order2);	//从HT数组1-num选出最小两位order1、order2
		(*HT)[order1].parent = num+1;
		(*HT)[order2].parent = num+1;
		(*HT)[num+1].lchild = order1;
		(*HT)[num+1].rchild = order2;
		(*HT)[num+1].weight = (*HT)[order1].weight + (*HT)[order2].weight;
	}
	return 1;
}

void Select(HuffmanTree HT, int num, int* order1, int* order2)
{
	int i=1;
	int temp;
	while(HT[i].parent!=0&&i<=num)
	{
		i++;
	}
	if(i==num+1)
	{
		return;
	}
	*order1=i;
	i++;
	while(HT[i].parent!=0&&i<=num)
	{
		i++;
	}
	if(i==num+1)
	{
		return;
	}
	*order2=i;
	i++;
	if(HT[*order1].weight>HT[*order2].weight)
	{
		temp=*order1;
		*order1=*order2;
		*order2=temp;
	}
	for(;i<=num;i++)
	{
		if(HT[i].parent==0)
		{
			if(HT[i].weight<HT[*order1].weight)
			{
				*order2=*order1,*order1=i;
			}
			else if (HT[i].weight < HT[*order2].weight)
			{
				*order2=i;
			}
		}
	}
}

void ShowHT(HuffmanTree HT,int num,char *ch)
{
	int sum=2*num-1;
	printf("节点\t字符\t权值\t双亲\t左孩子\t右孩子\t\n");
	for(int i=1;i<=sum;i++)
	{
		printf("%d\t%c\t%d\t%d\t%d\t%d\t\n",i,ch[i],HT[i].weight,HT[i].parent,HT[i].lchild,HT[i].rchild);
	}
}

void SaveHT(HuffmanTree HT,int num,char *ch)
{
	int sum =2*num-1;
	FILE* fp;
    if((fp=fopen("data.txt","w+"))==NULL)
    {
    	printf("Open file \"data.txt\" error!");
	}
	fprintf(fp,"节点\t字符\t权值\t双亲\t左孩子\t右孩子\t\n");
	for(int i=1;i<=sum;i++)
	{
		fprintf(fp,"%d\t%c\t%d\t%d\t%d\t%d\t\n",i,ch[i],HT[i].weight,HT[i].parent,HT[i].lchild,HT[i].rchild);
	}
	fclose(fp);
}

void Coding(HuffmanTree HT,int num,char ***code)
{
	int start,f,c;  
    char *temp;
    
    (*code)=(char **)malloc((num+1)*sizeof(char *));
	/*声明形参为什么用***： 
	因为molloc返回的是（分配好大小的）头地址
	所以本身就是二重指针的code需要再加一个*用来给实参返回一个经molloc修改后的地址*/ 
    temp=(char *)malloc(num*sizeof(char));   //分配求编码的工作空间
    temp[num-1]='\0';
    for(int i=1; i<=num; i++)
    {
        start=num-1;
        for (c = i, f = HT[i].parent; f != 0;c=f,f = HT[f].parent)
		{
		    if (HT[f].lchild == c)
		    {
		    	temp[--start] = '0';
			}
		    else if(HT[f].rchild == c)
		    {
		        temp[--start] = '1';
			}
    	}
        (*code)[i]=(char *)malloc((num-start)*sizeof(char));
        strcpy((*code)[i],&temp[start]);
		/*temp代表整个分配空间的首地址，&temp[start]是start位置的地址 
		这样赋值可以将start地址之前的空间省去
		将start之后的空间上复制给(*code)[i]*/ 
	}
    free(temp);
    return ;
}

void ShowCode(char **code,int num)
{
	printf("序号\t编码\t\n");
	for(int i=1;i<=num;i++)
	{
		printf("%d\t%s\t\n",i,code[i]);
	}
}