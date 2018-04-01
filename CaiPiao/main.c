#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"register.h"
#include"admin.h"
#include"user.h"
#include"greffier.h"

void user_login(user_link u_head,issue_link i_head,buy_link b_head);//用户登录

int check(user_link u_head,user_inf user);//判断用户账号和密码

void admin_login(user_link u_head,issue_link i_head);//管理员登录

void greffier_login(user_link u_head,issue_link i_head,buy_link b_head);//公证员登录

void load_user(user_link u_head);//用户信息加载

void load_issue(issue_link i_head);//发行彩票信息加载

void load_buy(buy_link b_head);//购买彩票信息加载

void delete_u_link(user_link u_head);//释放用户链表堆空间

void delete_i_link(issue_link i_head);//释放发行彩票链表堆空间

void delete_b_link(buy_link b_head);//释放购买彩票链表堆空间

void main()
{
    int choice = -1;

    user_inf user = {0,"",""};
    user_link u_head = create_u_node(user);//创建用户链表头节点
    load_user(u_head);//加载用户信息

    issue_inf i_lottery = {0,0,"",{0},0,0,0};
    issue_link i_head = create_i_node(i_lottery);//创建发行彩票链表头节点
    load_issue(i_head);//加载发行彩票的信息

    buy_inf b_lottery = {0,0,{0},"",0,"",0};
    buy_link b_head = create_b_node(b_lottery);//创建购买彩票链表头节点
    load_buy(b_head);//加载购买彩票的信息

    while(1)
    {
	printf("**************************\n");
	printf("\t1:用户登录\n");
	printf("**************************\n");
	printf("\t2:用户注册\n");
	printf("**************************\n");
	printf("\t3:管理员登录\n");
	printf("**************************\n");
	printf("\t4:公证员登录\n");
	printf("**************************\n");
	printf("\t0:退出\n");
	printf("**************************\n");

	printf("请输入选择:");
	scanf("%d",&choice);
	while(getchar() != '\n');

	switch(choice)
	{
	    case 1:
		   user_login(u_head,i_head,b_head);//调用用户登录函数，进入登录
		   break;
	    case 2:
		   user_register(u_head);//进入用户注册
		   break;
	    case 3:
		   admin_login(u_head,i_head);//管理员登录
		   break;
	    case 4:
		   greffier_login(u_head,i_head,b_head);//公证员登录
		   break;
	    case 0:
		   delete_u_link(u_head);//释放堆空间
		   delete_i_link(i_head);
		   delete_b_link(b_head);
		   return ;
	    default:
		   printf("请输入正确选项\n");
	}
    }
}
/*******************************用户登录***************************/
void user_login(user_link u_head,issue_link i_head,buy_link b_head)
{
    user_inf user={0,"",""};
    int num = 0;//定义登录次数

    while(num< 3)
    {
    	printf("输入帐号:");
    	scanf("%s",user.name);
    	while(getchar() != '\n');
	printf("输入密码:");
    	scanf("%s",user.passwd);
    	while(getchar() != '\n');

    	int flag = check(u_head,user);//判断帐号密码是否正确
    	if(flag == 0)
    	{
	    printf("登录成功\n");
	    user_desk(u_head,i_head,b_head,user.name);//进入用户操作界面
	    return;
    	}
	else if(flag == 1)
    	{
    	    printf("此帐号未注册\n");
    	}
    	else if(flag == 2)
	{
    	    printf("密码不正确\n");
	}
	else
	    printf("发现登录问题\n");
	num++;
   }
   printf("登录失败次数过多\n");

}
/****************************管理员登录*********************/
void admin_login(user_link u_head,issue_link i_head)
{ 
    char admin_account[20] = "admin";//管理员帐号
    char admin_passwd[20] = "admin";//管理员密码
    char admin[20] = "",passwd[20] = "";//定义接受输入帐号和密码的变量
    int num = 0;//定义登录次数变量

    while(num< 3)//当登录次数超过三次自动退出
    {
    	printf("输入帐号:");
    	scanf("%s",admin);
    	while(getchar() != '\n');   
       	printf("输入密码:");
    	scanf("%s",passwd);
    	while(getchar() != '\n');

	if((strcmp(admin,admin_account) == 0)&&(strcmp(passwd,admin_passwd) == 0))
	{
	    printf("登录成功\n");
	    admin_desk(u_head,i_head);//进入管理员界面
	    return ;
	}
	else
	{
	    printf("登录失败\n");
	    num++;
	}
    }
    printf("登录失败次数过多\n");
}
/****************************公证员登录*********************/
void greffier_login(user_link u_head,issue_link i_head,buy_link b_head)
{ 
    char admin_account[20] = "greffier";//公证员帐号
    char admin_passwd[20] = "greffier110";//公证员密码
    char admin[20] = "",passwd[20] = "";//定义接受输入帐号和密码的变量
    int num = 0;//定义登录次数变量

    while(num< 3)//当登录次数超过三次自动退出
    {
    	printf("输入帐号:");
    	scanf("%s",admin);
    	while(getchar() != '\n');   
       	printf("输入密码:");
    	scanf("%s",passwd);
    	while(getchar() != '\n');

	if((strcmp(admin,admin_account) == 0)&&(strcmp(passwd,admin_passwd) == 0))
	{
	    printf("登录成功\n");
	    greffier_desk(u_head,i_head,b_head);//进入公证员界面
	    return ;
	}
	else
	{
	    printf("登录失败\n");
	    num++;
	}
    }
    return ;
}
/************************************判断用户帐号和密码是否正确***************************/
int check(user_link u_head,user_inf user)
{
    if(u_head == NULL)
    {
	printf("头节点有问题\n");
	return 3;
    }
    int flag1 = 0,flag2 = 0;
    u_head = u_head->next;
    while(u_head != NULL)
    {
	if(strcmp(user.name,u_head->user.name) == 0)//判断帐号
	{
	    flag1 = 1;
	}
	if(strcmp(user.passwd,u_head->user.passwd) == 0)//判断密码
	{
	    flag2 = 1;
	}
	u_head = u_head->next;
    }
    if(flag1 == 0)
    {
	return 1;//1代表此帐号不存在
    }
    if(flag2 == 0)
    {
	return 2;//2代表密码不正确
    }
    return 0;//0代表帐号和密码正确

}
/************************用户信息加载*****************/
void load_user(user_link u_head)
{
    FILE *fp = NULL;
    fp = fopen("user_list.txt","r");
    if(fp == NULL)
    {
	printf("文件不存在，系统重新创建\n");
	system("touch user_list.txt");
	fp = fopen("user_list.txt","r");
    } 
    while(!feof(fp))
    {
	user_inf user;
	int flag = fread(&user,sizeof(user_inf),1,fp);
	if(flag< 1)
	    break;
	insert_u_node(u_head,user);
    }
    fclose(fp);
}
/*****************************发行彩票的信息加载***********************/
void load_issue(issue_link i_head)
{
    FILE *fp = NULL;
    fp = fopen("issue_list.txt","r");
    if(fp == NULL)
    {
	printf("文件不存在，系统重新创建\n");
	system("touch issue_list.txt");
	fp = fopen("issue_list.txt","r");
    } 
    while(!feof(fp))
    {
	issue_inf i_lottery;
	int flag = fread(&i_lottery,sizeof(issue_inf),1,fp);
	if(flag< 1)
	    break;
	insert_i_node(i_head,i_lottery);
    }
    fclose(fp);
}
/*****************************购买彩票的信息加载***********************/
void load_buy(buy_link b_head)
{
    FILE *fp = NULL;
    fp = fopen("buy_list.txt","r");
    if(fp == NULL)
    {
	printf("文件不存在，系统重新创建\n");
	system("touch buy_list.txt");
	fp = fopen("buy_list.txt","r");
    } 
    while(!feof(fp))
    {
	buy_inf b_lottery;
	int flag = fread(&b_lottery,sizeof(buy_inf),1,fp);
	if(flag< 1)
	    break;
	insert_b_node(b_head,b_lottery);
    }
    fclose(fp);
}
/***************释放发行彩票堆空间******************/
void delete_i_link(issue_link i_head)
{
    if(i_head == NULL)//判断头节点情况
    {
	printf("头节点为空\n");
	return ;
    }
    while(i_head->next != NULL)
    {
	issue_link save_head = i_head->next;//保存删除的结构体中指针
	free(i_head);//释放该堆空间
	i_head = save_head;//让i_head指向下一个节点
    }
    free(i_head);//释放最后一个节点
}
/***************释放用户堆空间******************/
void delete_u_link(user_link u_head)
{
    if(u_head == NULL)//判断头节点情况
    {
	printf("头节点为空\n");
	return ;
    }
    while(u_head->next != NULL)
    {
	user_link save_head = u_head->next;//保存删除的结构体中指针
	free(u_head);//释放该堆空间
	u_head = save_head;//让u_head指向下一个节点
    }
    free(u_head);//释放最后一个节点
}
/***************释放购买彩票堆空间******************/
void delete_b_link(buy_link b_head)
{
    if(b_head == NULL)//判断头节点情况
    {
	printf("头节点为空\n");
	return ;
    }
    while(b_head->next != NULL)
    {
	buy_link save_head = b_head->next;//保存删除的结构体中指针
	free(b_head);//释放该堆空间
	b_head = save_head;//让b_head指向下一个节点
    }
    free(b_head);//释放最后一个节点
}


























