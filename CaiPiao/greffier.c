#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"register.h"
#include"admin.h"
#include"user.h"
#include"greffier.h"

/*********************************公证员界面******************/
void greffier_desk(user_link u_head,issue_link i_head,buy_link b_head)
{
    int choice = -1;
    while(1)
    {
	printf("********************************\n");
	printf("1:开奖\n");
	printf("2:查看彩票信息\n");
	printf("0:返回\n");
	printf("********************************\n");
	printf("请输入选项:");
	scanf("%d",&choice);
	while(getchar() != '\n');

	switch(choice)
	{
	    case 1:
		   open_win(u_head,i_head,b_head);//开奖
		   break;
	    case 2:
		   display_lottery(i_head,b_head);//查看彩票信息
		   break;
	    case 0:
		   return ;
	    default:
		   printf("请输入正确选项\n");
	}

    }
}
/*****************************开奖界面****************************/
void open_win(user_link u_head,issue_link i_head,buy_link b_head)
{
    int choice = -1;
    while(1)
    {
	printf("********************************\n");
	printf("1:公布中奖号码\n");
	printf("2:发放奖金\n");
	printf("0:返回\n");
	printf("********************************\n");
	printf("请输入选项:");
	scanf("%d",&choice);
	switch(choice)
	{
	    case 1:
		   publish_num(i_head);//发行中奖号码
		   break;
	    case 2:
		   give_money(u_head,i_head,b_head);//发放奖金
		   break;
	    case 0:
		   return ;
	    default:
		   printf("请输入正确选项\n");
	}
    }
}
/*****************************发行中奖号码************************/
void publish_num(issue_link i_head)
{
    if(i_head == NULL)
    {
	printf("头节点有问题\n");
	return ;
    }
    issue_link save_head = i_head;//保存头节点
    i_head = i_head->next;
    while(i_head->next != NULL)//将发行彩票链表指针指向位开奖的节点的地址
    {
	i_head = i_head->next;
    }
    if(strcmp(i_head->i_lottery.state,"未开奖")== 0)//判断是否已经开过奖了
    {
    	strcpy(i_head->i_lottery.state,"已开奖");//将开奖状态设为已开奖
    }
    else
    {
	printf("此期中奖号码已经公布了\n");
	return ;
    }
    printf("请输入0～9三个数字，可重复选择，且用空格隔开\n");
    scanf("%d %d %d",&i_head->i_lottery.win_num[0],&i_head->i_lottery.win_num[1],&i_head->i_lottery.win_num[2]);//输入中奖号码
    while(getchar() != '\n');

    i_head = save_head;
    printf_issue(i_head);
    save_issue(i_head);
    printf("中奖号码公布成功\n");
}
/*********************************发放奖金***********************/
void give_money(user_link u_head,issue_link i_head,buy_link b_head)
{
    if(i_head == NULL)
    {
	printf("头节点有问题\n");
	return ;
    }
    issue_link save_i_head = i_head;//保存发行彩票链表的头节点
    i_head = i_head->next;
    while(i_head->next != NULL)//查找最后发放一期彩票的指针
    {
	i_head = i_head->next;
    }
    if(strcmp(i_head->i_lottery.state,"已开奖")!= 0)//判断此期彩票是否已经开奖
    {
	printf("此期彩票还未开奖\n");
	return ;
    }
    if(i_head->i_lottery.flag == 1)//判断奖金是否已经发放
    {
	printf("此期奖金已经发放了\n");
	return ;
    }
    if(b_head == NULL)
    {
	printf("头节点有问题\n");
	return ;
    }
    buy_link save_b_head = b_head;//保存购买彩票链表的头节点
    b_head = b_head->next;
    while(b_head != NULL)//查找发放奖金的这一期的期号的第一个指针
    {
	if(b_head->b_lottery.date == i_head->i_lottery.date)//通过期号进行判断来查找其指针
	{
	    break;
	}
	b_head = b_head->next;
    }
    if(u_head == NULL)
    {
	printf("头节点有问题\n");
	return ;
    }
    user_link save_u_head = u_head;//保存用户链表的头节点
    u_head = u_head->next;
    while(b_head != NULL)
    {
	if((b_head->b_lottery.number[0]== i_head->i_lottery.win_num[0])&&(b_head->b_lottery.number[1]== i_head->i_lottery.win_num[1])&&(b_head->b_lottery.number[2]== i_head->i_lottery.win_num[2]))//通过发布的中奖号码和购买号码进行判断而找出购买该号码的在购买链表中的指针
	{
	    while(u_head != NULL)
	    {
		if(strcmp(b_head->b_lottery.name,u_head->user.name)== 0)//通过用账号找到用户在用户链表中的指针
		{
		    strcpy(b_head->b_lottery.state,"中奖");//将购买彩票上的中奖状态改为中奖
		    b_head->b_lottery.win_money = 1000*b_head->b_lottery.pot;//修改购买彩票上的中奖金额
		    u_head->user.money += 1000*b_head->b_lottery.pot;//发放奖金到用户余额中
		    i_head->i_lottery.sum_money -= 1000*b_head->b_lottery.pot;//更改奖池的奖金
		    break;
		}
		else
		    u_head = u_head->next;
	    }
	}
	u_head = save_u_head->next;
	b_head = b_head->next;
    }

    i_head->i_lottery.flag = 1;//奖金发放后将其标志位置为1

    u_head = save_u_head;
    save_user(u_head);//保存用户信息

    b_head = save_b_head;
    save_buy(b_head);//保存彩票购买信息

    i_head = save_i_head;
    save_issue(i_head);//保存彩票发行信息
    printf("奖金发放成功\n");
}
/***********************************查看彩票信息界面*************************/
void display_lottery(issue_link i_head,buy_link b_head)
{
    int choice = -1;
    while(1)
    {
	printf("********************************\n");
	printf("1:查看发放彩票记录\n");
	printf("2:查看购买彩票记录\n");
	printf("0:返回\n");
	printf("********************************\n");
	printf("请输入选项:");
	scanf("%d",&choice);
	switch(choice)
	{
	    case 1:
		   display_issue(i_head);//查看发行彩票记录
		   break;
	    case 2:
		   display_buy(b_head);//查看购买彩票记录
		   break;
	    case 0:
		   return ;
	    default:
                    printf("请输入正确选项\n");
	}
    }	
    
}
/***********************************查看发行彩票记录*****************************/
void display_issue(issue_link i_head)
{
    if(i_head == NULL)
    {
	printf("头节点有问题\n");
	return ;
    }
    i_head = i_head->next;
    while(i_head != NULL)
    {
	printf("********************************\n");
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
    	else
    	{
    	    printf("本期已售出总数:%d\n",i_head->i_lottery.sum_num);
    	}
    	printf("本期奖池总额:%.2lf\n",i_head->i_lottery.sum_money);
	printf("********************************\n");
    	i_head = i_head->next;
    }
}
/***************************************查看购买彩票记录***************************/
void display_buy(buy_link b_head)
{
    if(b_head == NULL)
    {
	printf("头节点有问题\n");
	return ;
    }
    b_head = b_head->next;
    while(b_head != NULL)
    {
	printf("***************************************\n");
	printf("期号:%d\n",b_head->b_lottery.date);
	printf("ID:%ld\n",b_head->b_lottery.ID);

	printf("购买号码:");
	for(int i= 0;i< 3;i++)
	{
	    printf("\t%d",b_head->b_lottery.number[i]);
	}

	printf("\n注数:%d\n",b_head->b_lottery.pot);
	printf("***************************************\n");
	b_head = b_head->next;
    }
}

















