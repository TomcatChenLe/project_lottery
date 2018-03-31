#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"register.h"
#include"admin.h"
#include"user.h"

/*******************************用户界面***************************/
void user_desk(user_link u_head,issue_link i_head,buy_link b_head,char *p_name)
{
    int choice = -1;
    int flag = 0;//定义注销账号的标志
    while(1)
    {
	printf("************************\n");
	printf("1:查看信息\n");
	printf("2:账户充值\n");
	printf("3:查看彩票\n");
	printf("4:密码管理\n");
	printf("5:注销账号\n");
	printf("0:退出帐号\n");
	printf("************************\n");
	printf("请输入选择:");
	scanf("%d",&choice);
	while(getchar() != '\n');

	switch(choice)
	{
	    case 1:
		   see_inf(u_head,p_name);//查看个人信息
		   break;
            case 2:
		   recharge(u_head,p_name);//账户充值
		   break;
	    case 3:
		   show_lottery(u_head,i_head,b_head,p_name);//查看彩票
		   break;
	    case 4:
		   change_passwd(u_head,p_name);//修改密码
		   break;
	    case 5:
		   flag = delete_account(u_head,p_name);//注销账号
		   if(flag == 0)
		   {
		       break;
		   }
		   else
		   {
    		       save_user(u_head);
    		       return ;
		   }
	    case 0:
		   return ;
	    default:
		   printf("请输入正确选择\n");
	}
    }
}
/*******************************查看个人信息*************************/
void see_inf(user_link u_head,char *p_name)
{
    if(u_head == NULL)
    {
	printf("头节点有问题\n");
	return ;
    }
    int flag = 0;//定义判断是否有此用户的标志位变量
    u_head = u_head->next;
    while(u_head != NULL)
    {
	if(strcmp(p_name,u_head->user.name) == 0)//查找该用户的指针
	{
	    printf("帐号:%s\n",u_head->user.name);
	    printf("密码:%s\n",u_head->user.passwd);
	    printf("余额:%.2lf\n",u_head->user.money);

	    flag = 1;//有此用户标志位置为1
	    break;
	}
	u_head = u_head->next;
    }
    if(flag != 1)//判断标志位
    {
	printf("没有此用户\n");
    }
}
/********************************账户充值***************************/
void recharge(user_link u_head,char *p_name)
{
    if(u_head == NULL)
    {
	printf("头节点有问题\n");
	return ;
    }
    user_link save_head = u_head;//保存头节点
    u_head = u_head->next;
    while(u_head != NULL)
    {
	if(strcmp(p_name,u_head->user.name) == 0)//查找用户的指针
	{
	    double money = 0;
	    printf("请输入充值金额:");
	    scanf("%lf",&money);
	    u_head->user.money += money;
	    break;
	}
	u_head = u_head->next;
    }
    save_user(save_head);//保存
    printf("充值成功\n");
}
/************************************修改密码***********************/
void change_passwd(user_link u_head,char *p_name)
{
    if(u_head == NULL)
    {
	printf("头节点有问题\n");
	return ;
    }
    user_link save_head = u_head;//保存头节点
    u_head = u_head->next;
    while(u_head != NULL)
    {
	if(strcmp(p_name,u_head->user.name) == 0)
	{
	    char old_passwd[20]= "";
	    char new_passwd[2][20]= {"",""};
	    while(1)
	    {
    		printf("请输入旧密码:");
		scanf("%s",old_passwd);
		while(getchar() != '\n');
    		if(strcmp(old_passwd,u_head->user.passwd) == 0)//验证旧密码
		{
		    printf("密码验证正确\n");

		    while(1)
		    {
    			printf("请输入新密码:");
    			scanf("%s",new_passwd[0]);
    			while(getchar() != '\n');
    			printf("请重新输入新密码:");
    			scanf("%s",new_passwd[1]);
    			while(getchar() != '\n');

			if(strcmp(new_passwd[0],new_passwd[1]) == 0)//判断两次输入是否一致
			{
			    strcpy(u_head->user.passwd,new_passwd[0]);//修改密码
			    break;//跳出输入新密码修改循环
			}
			else
			{
			    printf("两次输入密码不一样\n");
			}
		    }
		    break;//跳出旧密码判断循环
		}
		else
		{
		    printf("密码输入错误\n");
		}
	    }
	    break;//跳出账户查询循环
	}
	u_head = u_head->next;
    }
    save_user(save_head);
    printf("密码修改成功\n");
}
/****************************************注销账号***************************************/
int delete_account(user_link u_head,char *p_name)
{
    if(u_head == NULL)
    {
	printf("头节点有问题\n");
	return 0;
    }
    char yes;//定义是否继续注销账号的变量
    printf("是否确定注销此账号?(y/n)\n");
    scanf("%c",&yes);
    while(getchar() != '\n');
    if(yes != 'y')//判断是否继续注销账号
    {
	return 0;
    }
    user_link delete = select_user(u_head,p_name);//查找删除节点的指针
    if(delete == NULL)
    {
	printf("没有此用户\n");
	return 0;
    }
    user_link pre = NULL;
    while(u_head != delete)//找出删除节点的上一个节点的指针
    {
	pre = u_head;
	u_head = u_head->next;
    }
    pre->next = delete->next;//删除节点的上一个节点指向删除节点的下一个节点
    free(delete);//释放堆空间
    printf("注销成功\n");
    return 1;
}
/****************************************查询用户************************************/
user_link select_user(user_link u_head,char name[20]) 
{
    if(u_head==NULL)
    {
	printf("头节点有问题\n");
	return NULL;
    }
    u_head = u_head->next;
    while(u_head!=NULL)
    {
	if(strcmp(u_head->user.name,name)==0)
	{
	    return u_head;
	}
	u_head=u_head->next;
    }
    printf("没有此用户\n");
    return NULL;
}
/************************************查看彩票***********************************/
void show_lottery(user_link u_head,issue_link i_head,buy_link b_head,char *p_name)
{
    int choice = -1;
    while(1)
    {
	printf("***************************\n");
	printf("1:购买彩票\n");
	printf("2:购买记录\n");
	printf("0:返回\n");
	printf("***************************\n");
	printf("请输入选项:");
	scanf("%d",&choice);
	while(getchar() != '\n');

	switch(choice)
	{
	    case 1:
		   buy_lottery(u_head,i_head,b_head,p_name);//购买彩票
		   break;
	    case 2:
		   buy_record(i_head,b_head,p_name);//购买记录
		   break;
	    case 0:
		   return ;
	    default:
		   printf("请输入正确选项\n");
	}
    }
}
/****************************************购买彩票*******************************/
void buy_lottery(user_link u_head,issue_link i_head,buy_link b_head,char *p_name)
{
    printf("*********************************\n");
    printf("最近一期彩票信息\n");
    printf("*********************************\n");
    printf_issue(i_head);//打印最后一期彩票信息
    printf("*********************************\n");

    issue_link save_head = i_head;//保存发行彩票头节点
    i_head = i_head->next;//跳过发行彩票头节点
    while(i_head->next != NULL)//找到发行彩票最后一期发行彩票的指针
    {
	i_head = i_head->next;
    }
  
    buy_inf b_lottery = {0,0,{0},"",0,"未中奖",0};//定义接受购买彩票的信息的变量
    if(strcmp(i_head->i_lottery.state,"已开奖")!= 0)
    {
    	printf("请输入0～9三个数字，可重复选择，且用空格隔开\n");
    	scanf("%d %d %d",&b_lottery.number[0],&b_lottery.number[1],&b_lottery.number[2]);  
      	printf("请输入购买注:");
    	scanf("%d",&b_lottery.pot);

	b_lottery.date = i_head->i_lottery.date;//将期号赋给购买的彩票上
	b_lottery.ID = i_head->i_lottery.date*1000+i_head->i_lottery.sum_num+1;//设定购买的彩票的ID
	strcpy(b_lottery.name,p_name);//将用户的账号输入到购买的次彩票上

	user_link p_user = select_user(u_head,p_name);//定义并查找该用户的指针
	if(p_user->user.money< b_lottery.pot*i_head->i_lottery.price)//判断余额是否充足
	{
	    printf("余额不足，请充值\n");
	    return ;
	}
	else
	{
	    p_user->user.money = p_user->user.money - b_lottery.pot*i_head->i_lottery.price;//从余额中减去购买彩票的消费
	    save_user(u_head);//保存
	}
	insert_b_node(b_head,b_lottery);
	save_buy(b_head);
	i_head->i_lottery.sum_num += 1;//售出彩票总数加1
	save_issue(save_head);

	printf("彩票购买成功\n");
    }
    else
    {
	printf("还未发行彩票,不能购买\n");
    }

}
/******************************************购买记录**************************************/
void buy_record(issue_link i_head,buy_link b_head,char *p_name)
{
    int flag = 0;//定义是否购买过彩票的标志的变量
    if(b_head == NULL)
    {
	printf("头节点有问题1\n");
	return ;
    }
    b_head = b_head->next;
    if(i_head == NULL)
    {
	printf("头节点有问题2\n");
	return ;
    }
    issue_link save_head = i_head;//保存彩票发行头节点
    i_head =i_head->next;
    while(b_head != NULL)
    {
	if(strcmp(b_head->b_lottery.name,p_name) == 0)//查找该用户是否购买彩票
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
	    printf("购买者账号:%s\n",b_head->b_lottery.name);

	    while(i_head != NULL)
	    {
		if(i_head->i_lottery.date == b_head->b_lottery.date)
		{
		    if(strcmp(i_head->i_lottery.state,"已开奖") == 0)//判断是否已经开奖
		    {
			printf("中奖状态:%s\n",b_head->b_lottery.state);
			if(strcmp(b_head->b_lottery.state,"中奖")== 0)//判断是否中奖
			{
			    printf("中奖金额:%.2lf\n",b_head->b_lottery.win_money);
			}
		    }
		    break;
		}
		i_head = i_head->next;
	    }
	    printf("***************************************\n");
	    flag = 1;//购买过彩票将标志置为1
	}
	i_head = save_head->next;
	b_head = b_head->next;
    }
    if(flag == 0)//判断是否买过彩票
    {
	printf("你还没有买过彩票，请购买\n");
    }
}
/*********************创建购买彩票节点*********************************************/
buy_link create_b_node(buy_inf b_lottery)
{
    buy_link ptr = calloc(1,sizeof(buy));
    ptr->b_lottery = b_lottery;
    ptr->next = NULL;
    return ptr;
}
/****************插入购买彩票节点*****************/
void insert_b_node(buy_link b_head,buy_inf b_lottery)
{
    if(b_head == NULL)
    {
	printf("头节点有问题\n");
	return ;
    }
    while(b_head->next != NULL)
    {
	b_head = b_head->next;
    }
    buy_link newnode = create_b_node(b_lottery);
    b_head->next = newnode;
}
/*************保存*************/
void save_buy(buy_link b_head)
{
    FILE *fp = NULL;
    fp = fopen("buy_list.txt","w");
    b_head = b_head->next;
    while(b_head != NULL)
    {
	fwrite(&b_head->b_lottery,sizeof(buy_inf),1,fp);
	b_head = b_head->next;
    }
    fclose(fp);
}




