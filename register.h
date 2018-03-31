#ifndef _REGISTER_H_
#define _REGISTER_H_
typedef struct user_information//彩民信息
{
    double money;//账户金额
    char name[20];//账户名
    char passwd[20];//账户密码
}user_inf;

typedef struct user//彩民链节
{
    user_inf user;//彩民信息
    struct user *next;//下一个节点
}user,*user_link;

void user_register(user_link);//用户注册
user_link create_u_node(user_inf);//创建用户节点
void insert_u_node(user_link,user_inf);//插入用户节点
void save_user(user_link);//保存用户数据
#endif
