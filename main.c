#include <stdio.h>
#include <stdlib.h>

typedef struct btree{                           //建立二叉树的结构体
    char data;
    int ltag,rtag;
    struct btree *lchild;
    struct btree *rchild;
}btree,*b_tree;

btree *pre;                                       //定义前驱结点

b_tree Creat_Tree();                                //建立一个二叉树
void p_order(btree *bt);                            // 按照先序顺序打印此二叉树
void P_clue_order(btree *bt);                       //先序线索化二叉树
b_tree P_clue_build(btree *bt);                     //构造先序线索二叉树
b_tree previous(btree *bt,char ch);                 //查找节点的前驱
b_tree next(btree *bt,char ch);                     //查找结点的后继
void preorder(btree *bt);                           //打印先序线索二叉树遍历的结果


int main()
{
    char ch;
    btree *Tree,*pre_Tree;
    printf("请输入先序二叉树根节点:\n");
    Tree = Creat_Tree();
    printf("此二叉树按照先序遍历结果是:\n");
	p_order(Tree);
    printf("\n先序线索此二叉树的遍历结果是:\n");
    pre_Tree = P_clue_build(Tree);
    preorder(pre_Tree);
    printf("\n请输入要查找前驱和后继的节点:\n");
    getchar();
    ch = getchar();
    printf("%c\n",previous(pre_Tree,ch)->data);
    printf("%c\n",next(pre_Tree,ch)->data);
    return 0;
}

b_tree Creat_Tree()                               //建立一个二叉树
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
        printf("请输入%c的左子树,输入0表示结束:\n",bt->data);
        getchar();
        bt->lchild = Creat_Tree();
        printf("请输入%c的右子树,输入0表示结束:\n",bt->data);
        getchar();
        bt->rchild = Creat_Tree();
    }
    return bt;
}

void p_order(btree *bt)      // 按照先序顺序打印此二叉树
{
    if(bt)
    {
        printf("%c ",bt->data);
        p_order(bt->lchild);
        p_order(bt->rchild);
    }
}

void P_clue_order(btree *bt)    //先序线索化二叉树
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

b_tree P_clue_build(btree *bt)          //构造先序线索二叉树
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


 b_tree previous(btree *bt,char ch)                 //查找节点的前驱
{
    btree *p;
    printf("该节点的前驱是:");
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

b_tree next(btree *bt,char ch)                  //查找结点的后继
{
    btree *p;
    printf("该节点的后继是:");
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

void preorder(btree *bt)                //打印先序线索二叉树遍历的结果
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

