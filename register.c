#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"register.h"
/*****************************************用户注册**************************/
void user_register(user_link u_head)
{
    if(u_head == NULL)
    {
	printf("头节点有问题\n");
	return ;
    }
    user_link save_head = u_head;//保存头节点
    u_head = u_head->next;//跳过头节点
    user_inf user = {0,"",""};//定义接受输入注册用户的帐号和密码

    printf("请输入注册帐号:");
    scanf("%s",user.name);
    while(getchar() != '\n');

    while(u_head != NULL)
    {
	if(strcmp(user.name,u_head->user.name)==0)//帐号查重
	{
	    printf("此帐号已存在\n");
	    printf("请输入注册帐号:");
    	    scanf("%s",user.name);
	    while(getchar() != '\n');
	    u_head = save_head->next;
       	}
	else
	    u_head = u_head->next;   
	
    }

    printf("请输入密码:");
    scanf("%s",user.passwd);

    u_head = save_head;
    insert_u_node(u_head,user);//插入节点
    save_user(u_head);
    printf("注册成功\n");

}
/*********************创建用户节点*********************************************/
user_link create_u_node(user_inf user)
{
    user_link ptr = calloc(1,sizeof(user));
    ptr->user = user;
    ptr->next = NULL;
    return ptr;
}
/****************插入用户节点*****************/
void insert_u_node(user_link u_head,user_inf user)
{
    if(u_head == NULL)
    {
	printf("头节点有问题\n");
	return ;
    }
    while(u_head->next != NULL)
    {
	u_head = u_head->next;
    }
    user_link newnode = create_u_node(user);
    u_head->next = newnode;
}
/*************保存用户信息*************/
void save_user(user_link u_head)
{
    FILE *fp = NULL;
    fp = fopen("user_list.txt","w");
    u_head = u_head->next;
    while(u_head != NULL)
    {
	fwrite(&u_head->user,sizeof(user_inf),1,fp);
	u_head = u_head->next;
    }
    fclose(fp);
}
















