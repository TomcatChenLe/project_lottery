#ifndef _USER_H_
#define _USER_H_
typedef struct buy_information//购买彩票信息
{
    int date;//发行期号
    unsigned long ID;//单张彩票唯一标识ID
    int number[3];//彩票上选中的号码
    char name[20];//购买者帐号
    int pot;//已购买某一票号的注数
    char state[16];//中奖状态
    double win_money;//中奖金额
}buy_inf;
typedef struct buy//购买彩票链表
{
    buy_inf b_lottery;//购买的彩票的信息
    struct buy *next;//指向下一个节点
}buy,*buy_link;

void user_desk(user_link,issue_link,buy_link,char*);//用户界面
void see_inf(user_link,char *);//查看个人信息
void recharge(user_link,char *);//账户充值
void change_passwd(user_link,char *);//修改密码
int delete_account(user_link,char *);//注销账号
user_link select_user(user_link,char []);//查询用户
void show_lottery(user_link,issue_link,buy_link,char *);//查看彩票
void buy_lottery(user_link,issue_link,buy_link,char *);//购买彩票
void buy_record(issue_link,buy_link,char *);//购买记录

buy_link create_b_node(buy_inf);//创建购买彩票节点
void insert_b_node(buy_link,buy_inf);//插入购买彩票节点
void save_buy(buy_link);//保存彩票购买信息

#endif
