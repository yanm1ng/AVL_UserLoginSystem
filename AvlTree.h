#include <iostream>
#include <windows.h>
#include <string>
#include <vector>
#include <queue>
#include "Password.h"
template<class T>
class AvlTree 
{
public:
    AvlTree() { root = NULL; } //构造函数

    AvlTree(const AvlTree & rhs) //拷贝构造函数
	{
        root = NULL;
        *this = rhs;
    } 

    const AvlTree & operator=(const AvlTree & rhs) //重载=
	{
        if (this != &rhs) {
            makeEmpty();
            root = clone(rhs.root);
        }
        return *this;
    } 
    ~AvlTree() //析构函数
	{
        makeEmpty();
    } 

    const T & findMin() 
	{
        return findMin(root);
    } 

    const T & findMax()  
	{
        return findMax(root);
    } 

    bool contains(T & x) 
	{
        return contains(x, root);
    } 

    bool isEmpty()  
	{
        return root == NULL;
    } 

    void makeEmpty() //清空整棵树
	{
        makeEmpty(root);
    } 

    void insert(T & x) //构造树
	{
        insert(x, root);
    } 

    void remove(T & x) //删除x节点
	{
        remove(x, root);
    } 

    void printTree() 
	{
        if (isEmpty())
            cout << "Empty Tree..." << endl;
        else
            printTree(root);
    } 

	void write() 
	{
		ofstream out;
		out.open("Userdata.txt");
		write(root);
        out.close();
    } 

    int treeHeight() 
	{
        return treeHeight(root);
    }

	void Menu_select();
	void Menu_userLogin();
	void Menu_insert();
	void Menu_word();
	void Menu_view();
private:
	struct AvlNode 
	{
		T type;

		AvlNode *left;//左儿子
		AvlNode *right;//右儿子

		//节点的高度=左子树的高度和右子树的高度的最大值+1，每次平衡完树的操作都必须更新节点的高度
		int height;

		AvlNode(T & t, AvlNode *l, AvlNode *r, int h = 0) : type(t), left(l), right(r), height(h) {}//构造函数
	};
    AvlNode *root;//根节点

    void insert(T & x, AvlNode * & t);//在t的子树下插入x节点
    void remove(T & x, AvlNode * & t);

    AvlNode * findMin(AvlNode *t);
    AvlNode * findMax(AvlNode *t);

    bool contains(T & x, AvlNode *t);//判断t的子树内是否包含x节点

	AvlNode findName(T & x, AvlNode *t);

    void makeEmpty(AvlNode * & t);//t这棵树清空

    void printTree(AvlNode *t) ;//打印这颗树的节点信息，需要对T类进行<<运算符重载

	void write(AvlNode *t);

	void view(AvlNode *t, bool left,string const& indent);

	int nodeNum(AvlNode *t);

    int treeHeight(AvlNode *t);//返回树的高度，便于计算平衡因子（左树高度减去右树高度）

    AvlNode * clone(AvlNode *t);//复制这颗子树

    int height(AvlNode *t);//返回节点的高度height

	//单旋转
    void rotateWithLeftChild(AvlNode * & k2);//右旋情况，k2的左子树比右子树深2层。将k2节点的左儿子作为新的根节点，旋转之后更新节点的高度
    void rotateWithRightChild(AvlNode * & k2);//左旋情况，k2的右子树比左子树深2层。将k2节点的右儿子作为新的根节点，旋转之后更新节点的高度
	//双旋转
    void doubleWithLeftChild(AvlNode * & k3);//先左旋再右旋
    void doubleWithRightChild(AvlNode * & k3);//先右旋再左旋
};
