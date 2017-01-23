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
    AvlTree() { root = NULL; } //���캯��

    AvlTree(const AvlTree & rhs) //�������캯��
	{
        root = NULL;
        *this = rhs;
    } 

    const AvlTree & operator=(const AvlTree & rhs) //����=
	{
        if (this != &rhs) {
            makeEmpty();
            root = clone(rhs.root);
        }
        return *this;
    } 
    ~AvlTree() //��������
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

    void makeEmpty() //���������
	{
        makeEmpty(root);
    } 

    void insert(T & x) //������
	{
        insert(x, root);
    } 

    void remove(T & x) //ɾ��x�ڵ�
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

		AvlNode *left;//�����
		AvlNode *right;//�Ҷ���

		//�ڵ�ĸ߶�=�������ĸ߶Ⱥ��������ĸ߶ȵ����ֵ+1��ÿ��ƽ�������Ĳ�����������½ڵ�ĸ߶�
		int height;

		AvlNode(T & t, AvlNode *l, AvlNode *r, int h = 0) : type(t), left(l), right(r), height(h) {}//���캯��
	};
    AvlNode *root;//���ڵ�

    void insert(T & x, AvlNode * & t);//��t�������²���x�ڵ�
    void remove(T & x, AvlNode * & t);

    AvlNode * findMin(AvlNode *t);
    AvlNode * findMax(AvlNode *t);

    bool contains(T & x, AvlNode *t);//�ж�t���������Ƿ����x�ڵ�

	AvlNode findName(T & x, AvlNode *t);

    void makeEmpty(AvlNode * & t);//t��������

    void printTree(AvlNode *t) ;//��ӡ������Ľڵ���Ϣ����Ҫ��T�����<<���������

	void write(AvlNode *t);

	void view(AvlNode *t, bool left,string const& indent);

	int nodeNum(AvlNode *t);

    int treeHeight(AvlNode *t);//�������ĸ߶ȣ����ڼ���ƽ�����ӣ������߶ȼ�ȥ�����߶ȣ�

    AvlNode * clone(AvlNode *t);//�����������

    int height(AvlNode *t);//���ؽڵ�ĸ߶�height

	//����ת
    void rotateWithLeftChild(AvlNode * & k2);//���������k2������������������2�㡣��k2�ڵ���������Ϊ�µĸ��ڵ㣬��ת֮����½ڵ�ĸ߶�
    void rotateWithRightChild(AvlNode * & k2);//���������k2������������������2�㡣��k2�ڵ���Ҷ�����Ϊ�µĸ��ڵ㣬��ת֮����½ڵ�ĸ߶�
	//˫��ת
    void doubleWithLeftChild(AvlNode * & k3);//������������
    void doubleWithRightChild(AvlNode * & k3);//������������
};
