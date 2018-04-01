#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"register.h"
#include"admin.h"
#include"user.h"

/*************************************************管理员界面*************************************/
void admin_desk(user_link u_head,issue_link i_head)
{
    int choice = -1;
    while(1)
    {
	printf("***********************\n");
	printf("1:发行彩票\n");
	printf("2:查询彩民信息\n");
	printf("3:排序\n");
	printf("4:保存\n");
	printf("0:退出\n");
	printf("***********************\n");
	printf("请输入选择:");
	scanf("%d",&choice);
	while(getchar() != '\n');
	printf("%d\n",choice);

	switch(choice)
	{
	    case 1:
		   issue_lottery(i_head);//发行彩票
		   break;
            case 2:
		   show_buyer(u_head);//查看彩民信息
		   break;
	    case 3:
		   sort(u_head);//排序
		   break;
	    case 4:
		   save_issue(i_head);//保存发行的彩票
		   break;
	    case 0:
		   return ;
	    default:
		   printf("请输入正确选项\n");
	}
    }
}
/**********************************发行彩票*****************************/
void issue_lottery(issue_link i_head)
{
    if(i_head == NULL)
    {
	printf("头节点有问题\n");
	return ;
    }
    issue_link save_head = i_head;
    i_head = i_head->next;
    if(i_head != NULL)//第一发行彩票
    {
	while(i_head->next != NULL)
	{
	    i_head = i_head->next;
	}
	if(strcmp(i_head->i_lottery.state,"已开奖") != 0)
	{
	    printf("上一期彩票还未开奖，不能发行彩票\n");
	    return ;
	}
    }
    issue_inf i_lottery = {0,0,"",{0},0,0,0};//定义用接收输入发行彩票的信息的变量
    printf("请输入期号:");
    scanf("%d",&i_lottery.date);
    while(getchar() != '\n');

    printf("请输入彩票单价:");
    scanf("%f",&i_lottery.price);
    while(getchar() != '\n');

    strcpy(i_lottery.state,"未开奖");//将开奖状态设为未开奖  

    printf("请输入本期奖池总额:");
    scanf("%lf",&i_lottery.sum_money);
    while(getchar() != '\n');

    insert_i_node(i_head,i_lottery);//在发行链表中插入节点
    save_issue(i_head);//保存
    printf_issue(i_head);
    printf("发行成功\n");
}
/************************打印发行彩票*****************************************/
void printf_issue(issue_link i_head)
{
    if(i_head==NULL)
    {
	printf("头节点有问题\n");
	return ;
    }
    i_head = i_head->next;//跳过头节点
    while(i_head->next != NULL)
    {
	i_head = i_head->next;
    }

    printf("第%d期\n",i_head->i_lottery.date);
    printf("彩票价格:%.2f/注\n",i_head->i_lottery.price);
    printf("开奖状态:%s\n",i_head->i_lottery.state);
    if(strcmp(i_head->i_lottery.state,"已开奖")== 0)//判断是否已开奖
    {
	printf("中奖号码:");
	for(int i= 0;i< 3;i++)
	{
    	    printf("%d\t",i_head->i_lottery.win_num[i]);
	}
	printf("\n");
        printf("本期售出总数:%d\n",i_head->i_lottery.sum_num);
    }
    printf("本期奖池总额:%.2lf\n",i_head->i_lottery.sum_money);
}
/***************************************查询彩民信息界面*************************/
void show_buyer(user_link u_head)
{
    int choice = -1;
    while(1)
    {
	printf("*****************************\n");
	printf("1:查看全部彩民信息\n");
	printf("2:根据余额查看彩民信息\n");
	printf("3:根据账户查看彩民信息\n");
	printf("0:返回\n");
	printf("*****************************\n");
	printf("请输入选项:");
	scanf("%d",&choice);
	while(getchar() != '\n');

	switch(choice)
	{
	    case 1:
		   show_all(u_head);//查看全部彩民信息
		   break;
	    case 2:
		   accord_money(u_head);//根据余额查看彩民信息
		   break;
	    case 3:
		   accord_account(u_head);//根据账户名查看彩民信息
		   break;
	    case 0:
		   return ;//返回上一层
	    default:
		   printf("请输入正确选项\n");
	}
    }
}
/***********************************查看所有彩民信息*******************************************/
void show_all(user_link u_head)
{
    if(u_head==NULL)
    {
	printf("头节点有问题\n");
	return ;
    }
    u_head = u_head->next;//跳过头节点
    while(u_head != NULL )//输出全部彩民信息
    {
	printf("********************************\n");
	printf("%s\n",u_head->user.name);//账户名
	printf("%s\n",u_head->user.passwd);//账户密码
	printf("%.2lf\n",u_head->user.money);//账户余额
	u_head = u_head->next;
    }
}
/***********************************根据余额查询彩民信息**********************/
void accord_money(user_link u_head)
{
    if(u_head==NULL)
    {
	printf("头节点有问题\n");
	return ;
    }
    u_head = u_head->next;
    double money = 0;//定义接受输入金额的变量
    int flag = 0;//定义判断是否有此有此余额的彩民的标志位
    printf("请输入金额:");
    scanf("%lf",&money);
    while(getchar() != '\n');

    while(u_head != NULL )
    {
	if(money == u_head->user.money)//判断与输入金额相同的彩民
	{
    	    printf("********************************\n");
    	    printf("%s\n",u_head->user.name);
    	    printf("%s\n",u_head->user.passwd);
    	    printf("%.2lf\n",u_head->user.money);
	    flag = 1;//存在余额相同的彩民，则标志位为1
	}
     	u_head = u_head->next;	
    }
    if(flag != 1)//判断是否有此余额的彩民
    {
	printf("没有此余额的彩民\n");
    }
}
/**************************************根据账户名查询彩民信息*****************************/
void accord_account(user_link u_head)
{
    char name[20] = "";//定义接受输入账户名
    printf("请输入账号:");
    scanf("%s",name);
    see_inf(u_head,name);//调用查看个人信息
}
/*******************************************排序界面*************************************/
void sort(user_link u_head)
{
    int choice = -1;
    while(1)
    {
	printf("1:根据余额排序\n");
	printf("2:根据账号排序\n");
	printf("0:返回\n");
	printf("请输入选项:");
	scanf("%d",&choice);

	switch(choice)
	{
	    case 1:
		   sort_money(u_head);//根据余额排序，从小到大
		   break;
	    case 2:
		   sort_account(u_head);//根据账号排序，根据字符的ASC码从小到大排序
		   break;
	    case 0:
		   return ;
	    default:
		   printf("请输入正确选项\n");
	}
    }
}
/*****************************根据余额排序************************/
void sort_money(user_link u_head)
{
    if(u_head==NULL)
    {
	printf("头节点有问题\n");
	return ;
    }
    user_link save_head = u_head;//保存头节点
    u_head = u_head->next;
    int length = 0;//定义链表长度变量
    while(u_head != NULL)
    {
	length++;
	u_head = u_head->next;
    }
    u_head = save_head->next;
    for(int i= 0;i< length;i++)//冒泡排序
    {
	for(int j= 0;j< length-1;j++)
	{
	    if(u_head->user.money > u_head->next->user.money)//判断余额大小
	    {
		user_inf user = u_head->user;
		u_head->user = u_head->next->user;
		u_head->next->user = user;
	    }
	    u_head = u_head->next;
	}
	u_head = save_head->next;
    }
    u_head = save_head;
    show_all(u_head);//显示排序结果
}
/*****************************根据账号排序****************************/
void sort_account(user_link u_head)
{
    if(u_head==NULL)
    {
	printf("头节点有问题\n");
	return ;
    }
    user_link save_head = u_head;
    u_head = u_head->next;
    int length = 0;//定义链表长度变量
    while(u_head != NULL)
    {
	length++;
	u_head = u_head->next;
    }
    u_head = save_head->next;
    for(int i= 0;i< length;i++)//冒泡排序
    {
	for(int j= 0;j< length-1;j++)
	{
	    if(strcmp(u_head->user.name,u_head->next->user.name)> 0)//判断账号的字符的ASC码的大小
	    {
		user_inf user = u_head->user;
		u_head->user = u_head->next->user;
		u_head->next->user = user;
	    }
	    u_head = u_head->next;
	}
	u_head = save_head->next;
    }
    u_head = save_head;
    show_all(u_head);//显示排序结果
}
/*********************创建彩票发行节点*********************************************/
issue_link create_i_node(issue_inf i_lottery)
{
    issue_link ptr = calloc(1,sizeof(issue));
    ptr->i_lottery = i_lottery;
    ptr->next = NULL;
    return ptr;
}
/****************插入彩票发行节点*****************/
void insert_i_node(issue_link i_head,issue_inf i_lottery)
{
    if(i_head==NULL)
    {
	printf("头节点有问题\n");
	return ;
    }
    while(i_head->next != NULL)
    {
	i_head = i_head->next;
    }
    issue_link newnode = create_i_node(i_lottery);
    i_head->next = newnode;
}
/*************彩票发行保存*************/
void save_issue(issue_link i_head)
{
    FILE *fp = NULL;
    fp = fopen("issue_list.txt","w");
    i_head = i_head->next;
    while(i_head != NULL)
    {
	fwrite(&i_head->i_lottery,sizeof(issue_inf),1,fp);
	i_head = i_head->next;
    }
    fclose(fp);
}

















