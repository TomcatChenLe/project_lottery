#ifndef _ADMIN_H_
#define _ADMIN_H_
typedef struct issue_information//发行彩票信息
{
    int date;//发行期号
    float price;//彩票单价
    char state[16];//开奖状态
    int win_num[3];//中奖号码
    int flag;//奖金发放标志
    int sum_num;//本期售出总数
    double sum_money;//本期奖池总额
}issue_inf;

typedef struct issue//发行彩票链节
{
    issue_inf i_lottery;//彩票信息
    struct issue *next;//下一个节点
}issue,*issue_link;

void admin_desk(user_link,issue_link);//管理员界面
void issue_lottery(issue_link);//发行彩票
void printf_issue(issue_link);//打印发行彩票
void show_buyer(user_link);//查询彩民信息界面
void show_all(user_link);//查看全部彩民信息
void accord_money(user_link);//根据余额查询彩民信息
void accord_account(user_link);//根据账户名查询彩民信息
void sort(user_link);//排序界面
void sort_money(user_link);//根据余额排序
void sort_account(user_link);//根据账号排序

issue_link create_i_node(issue_inf);//创建彩票发行节点
void insert_i_node(issue_link,issue_inf);//插入彩票发行节点
void save_issue(issue_link);//发行彩票保存

#endif
