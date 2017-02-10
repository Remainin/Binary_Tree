#include <stdio.h>
#include <stdlib.h>

typedef struct btree{                           //�����������Ľṹ��
    char data;
    int ltag,rtag;
    struct btree *lchild;
    struct btree *rchild;
}btree,*b_tree;

btree *pre;                                       //����ǰ�����

b_tree Creat_Tree();                                //����һ��������
void p_order(btree *bt);                            // ��������˳���ӡ�˶�����
void P_clue_order(btree *bt);                       //����������������
b_tree P_clue_build(btree *bt);                     //������������������
b_tree previous(btree *bt,char ch);                 //���ҽڵ��ǰ��
b_tree next(btree *bt,char ch);                     //���ҽ��ĺ��
void preorder(btree *bt);                           //��ӡ�������������������Ľ��


int main()
{
    char ch;
    btree *Tree,*pre_Tree;
    printf("������������������ڵ�:\n");
    Tree = Creat_Tree();
    printf("�˶���������������������:\n");
	p_order(Tree);
    printf("\n���������˶������ı��������:\n");
    pre_Tree = P_clue_build(Tree);
    preorder(pre_Tree);
    printf("\n������Ҫ����ǰ���ͺ�̵Ľڵ�:\n");
    getchar();
    ch = getchar();
    printf("%c\n",previous(pre_Tree,ch)->data);
    printf("%c\n",next(pre_Tree,ch)->data);
    return 0;
}

b_tree Creat_Tree()                               //����һ��������
{
    char ch;
    btree *bt;
    ch = getchar();
    if(ch=='0')
        bt=NULL;
    else
    {
        bt = (struct btree*)malloc(sizeof(btree));
        bt->data = ch;
        bt->ltag = 0;
        bt->rtag = 0;
        printf("������%c��������,����0��ʾ����:\n",bt->data);
        getchar();
        bt->lchild = Creat_Tree();
        printf("������%c��������,����0��ʾ����:\n",bt->data);
        getchar();
        bt->rchild = Creat_Tree();
    }
    return bt;
}

void p_order(btree *bt)      // ��������˳���ӡ�˶�����
{
    if(bt)
    {
        printf("%c ",bt->data);
        p_order(bt->lchild);
        p_order(bt->rchild);
    }
}

void P_clue_order(btree *bt)    //����������������
{
    if(bt)
    {
        if(bt->lchild == NULL)
        {
            bt->ltag = 1;
            bt->lchild = pre;
        }
        if(pre->rchild == NULL)
        {
            pre->rtag = 1;
            pre->rchild = bt;
        }
        pre = bt;
        if(bt->ltag == 0)
            P_clue_order(bt->lchild);
        if(bt->rtag == 0)
            P_clue_order(bt->rchild);
    }
}

b_tree P_clue_build(btree *bt)          //������������������
{
    btree *head;
    head = (struct btree*)malloc(sizeof(btree));
    head->ltag = 0;
    head->rtag = 1;
    head->rchild = head;
    if(bt==NULL)
        head->lchild = head;
    else
    {
        head->lchild = bt;
        pre = head;
        P_clue_order(bt);
        pre->rchild = head;
        pre->rtag = 1;
        head->rchild = pre;
    }
    return head;
}


 b_tree previous(btree *bt,char ch)                 //���ҽڵ��ǰ��
{
    btree *p;
    printf("�ýڵ��ǰ����:");
    p = bt->lchild;
    while(p!=bt)
    {
        if(p->ltag == 0)
        {
            if(p->lchild->data == ch)
                return p;
            else
                p = p->lchild;
        }
        else
        {
            if(p->rchild->data == ch)
                return p;
            else
                p = p->rchild;
        }
    }
}

b_tree next(btree *bt,char ch)                  //���ҽ��ĺ��
{
    btree *p;
    printf("�ýڵ�ĺ����:");
    p = bt->lchild;
    while(p!=bt)
    {
        if(p->data == ch)
        {
            if(p->ltag == 0)
                return p->lchild;
            else
                return p->rchild;
        }
        else
        {
            if(p->ltag == 0)
                p = p->lchild;
            else
                p = p->rchild;
        }
    }
}

void preorder(btree *bt)                //��ӡ�������������������Ľ��
{
    btree *p;
	p = bt->lchild;
	while (p!=bt)
	{
		printf("%c ", p->data);
		if (p->ltag == 0)
			p = p->lchild;
		else
			p = p->rchild;
    }
}

