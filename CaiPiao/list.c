    #include <stdio.h>  
    #include<stdlib.h>  
    #define  LEN  sizeof(struct node)  
    struct node  
    {  
    int data;  
    struct node  *next;  
    };  
    void main()  
    {     struct  node  *p, *pl,* head;  
              head=p=(struct node * )malloc(LEN);  
              scanf("%d",&p->data);/*头结点的数据成员*/  
              while(p->data!=0)   /*给出0结束条件,退出循环*/  
              {    pl=p;  
                   p=(struct node * )malloc(LEN);  
                      scanf("%d",&p->data);/*中间结点数据成员*/  
                      pl->next=p;/*中间结点的指针成员值*/  
              }  
              p-> next=NULL;/*尾结点的指针成员值*/  
              p=head;/*链表显示*/  
              printf("链表数据成员是：");  
              while(p->next!=NULL)  
              {  
              printf("%d",p->data);  
              p=p->next;  
              }  
              printf("%d\n",p->data);  
    }  
