#include "AvlTree.h"

template<class T>
typename AvlTree<T>::AvlNode * AvlTree<T>::findMin(AvlNode *t) //一直向左子树找最小的节点
{
    if (t == NULL)
        return NULL;
    if (t->left == NULL)
        return t;
    return findMin(t->left);
}

template<class T>
typename AvlTree<T>::AvlNode * AvlTree<T>::findMax(AvlNode *t) //一直向右子树找最大的节点
{
    if (t == NULL)
        return NULL;
    if (t->right == NULL)
        return t;
    return findMax(t->left);
}

template<class T>
bool AvlTree<T>::contains(T & x, AvlNode *t) 
{
    if (t == NULL)
        return false;
    else if (t->type > x)//如果x小于t的值，向t的左子树查找
        return contains(x, t->left);
    else if (t->type < x)//如果x大于t的值，向t的右子树查找
        return contains(x, t->right);
    else if (x == t->type )
        return true; //查找到节点值为x的节点
}

template<class T>
void AvlTree<T>::insert(T & x, AvlNode * & t) 
{
    if (t == NULL)//如果节点为空(树叶节点),就在此节点处加入newUser
        t = new AvlNode(x, NULL, NULL);
    else if (t->type > x) //如果newUser小于给的节点,就继续在节点的左子树中插入
	{
        insert(x, t->left);
        if (height(t->left) - height(t->right) == 2) //计算平衡因子
		{
            if (t->left->type > x)
                rotateWithLeftChild(t);  //如果t插在左子树，单旋转情况，进行一次右旋操作
            else
                doubleWithLeftChild(t); //如果t插在右子树，双旋情况，先左旋再右旋
        }
    } 
	else if (t->type < x) //如果newUser大于给的节点,就继续在节点的右子树中插入
	{
        insert(x, t->right);
        if (height(t->right) - height(t->left) == 2) //计算平衡因子
		{
            if (t->right->type < x)
                rotateWithRightChild(t);   //如果t插在右子树，单旋转情况，进行一次左旋操作
            else
                doubleWithRightChild(t);//如果t插在左子树，双旋情况，先右旋再左旋
        }
    } else
        ; 
    t->height = max(height(t->left), height(t->right)) + 1; //更新树的高度
}

template<class T>
void AvlTree<T>::remove(T & x, AvlNode * & t) 
{
    if (t == NULL)//一直查找到t是树叶节点
        return;
    if (t->type > x) //如果x小于t的值，继续向t的左子树查找一直到树叶节点
	{
        remove(x, t->left);
        if (height(t->right) - height(t->left) == 2) 
		{
            if (height(t->right->right) >= height(t->right->left))//考虑删除之后右子树节点的平衡因子
                rotateWithRightChild(t);
            else
                doubleWithRightChild(t);
        }
    } 
	else if (t->type < x) //如果x大于t的值，继续向t的右子树查找一直到树叶节点
	{
        remove(x, t->right);
        if (height(t->left) - height(t->right) == 2) 
		{
            if (height(t->left->left) >= height(t->left->right))//考虑删除之后左子树节点的平衡因子
                rotateWithLeftChild(t);
            else
                doubleWithLeftChild(t);
        }
    } 
	else if (t->left != NULL && t->right != NULL) //如果是内部节点，有左右两颗子树
	{
        t->type = findMin(t->right)->type;//将它右子树中最左边的（最小）节点拿到当前节点位置，这样可以保证他的左子树都比他小，右子树都比他大
        remove(t->type, t->right);
        t->height = max(height(t->left), height(t->right)) + 1;//更新树高
    } 
	else //如果t只有一颗子树，将t移除，t的左子树或右子树向上移到t的位置
	{
        AvlNode *oldNode = t;
        t = (t->left != NULL) ? t->left : t->right;
        delete oldNode;
    }
    if (t != NULL)
        t->height = max(height(t->left), height(t->right)) + 1;
}

template<class T>
void AvlTree<T>::makeEmpty(AvlNode * & t) //递归左右子树清空
{
    if (t != NULL) {
        makeEmpty(t->left);//清空左子树
        makeEmpty(t->right);//清空右子树
        delete t;//清空当前节点
    }
    t = NULL;
}

template<class T>
typename AvlTree<T>::AvlNode * AvlTree<T>::clone(AvlNode *t)
{
    if (t == NULL)
        return NULL;
    return new AvlNode(t->type, clone(t->left), clone(t->right));
}

template<class T>
void AvlTree<T>::printTree(AvlNode *t)  //中序遍历
{
    if (t != NULL) {
        printTree(t->left);//遍历左子树
        cout << t->type << " 节点高度:" << t->height<<"  平衡因子："<<(height(t->left)-height(t->right))<<endl;//输出节点值，需要对T类进行<< 运算符重载
        printTree(t->right);//遍历右子树
    }
}
template<class T>
void AvlTree<T>::write(AvlNode *t) 
{
	ofstream out;
	out.open("Userdata.txt",ios::app);
	if (t != NULL) {
        write(t->left);//遍历左子树
        out << t->type <<endl;
        write(t->right);//遍历右子树
    }
	out.close();
}

template<class T>
int AvlTree<T>::height(AvlNode *t) //返回节点的高度
{
    return t == NULL ? -1 : t->height;
}

template<class T>
void AvlTree<T>::rotateWithLeftChild(AvlNode * & k2) //右旋情况，三个节点一条直线,其他两个节点都是左儿子
{
    AvlNode *k1 = k2->left;     //k1为k2的左儿子，进行右旋将k1作为新的子树根节点

    k2->left = k1->right; //k1右子树成为k2的左子树
    k1->right = k2;  //k2成为k1的右儿子
	//更新节点高度
    k2->height = max(height(k2->left), height(k2->right)) + 1;
    k1->height = max(height(k1->left), k2->height) + 1;
	
    k2 = k1;  //k1成为这颗子树的根节点
}

template<class T>
void AvlTree<T>::rotateWithRightChild(AvlNode * & k2) //左旋情况，三个节点一条直线，其他两个节点都是右儿子
{
    AvlNode *k1 = k2->right;    //k1为k2的右儿子，进行左旋将k1作为新的子树根节点

    k2->right = k1->left; //k1左子树成为k2的右子树
    k1->left = k2; //k2成为k1的左儿子
	//更新节点高度
    k2->height = max(height(k2->right), height(k2->left)) + 1;
    k1->height = max(height(k1->right), k2->height) + 1;

    k2 = k1; //k1成为这颗子树的根节点
}
//先左旋再右旋 <
template<class T>
void AvlTree<T>::doubleWithLeftChild(AvlNode * & k3) {
    rotateWithRightChild(k3->left);
    rotateWithLeftChild(k3);
}
//先右旋再左旋，三个节点排列如 >
template<class T>
void AvlTree<T>::doubleWithRightChild(AvlNode * & k3) {
    rotateWithLeftChild(k3->right);
    rotateWithRightChild(k3);
}
template<class T>
int AvlTree<T>::treeHeight(AvlNode *t) //返回树的高度，去左右子树最大高度再加一
{
    if (t == NULL)
        return -1;
    else
        return 1 + max(treeHeight(t->left), treeHeight(t->right));
}
template<class T>
void AvlTree<T>::view(AvlNode *t,bool left,string const& indent)
{
	if(t->right)
    {
        view(t->right, false, indent + (left ? "|     " : "      "));
    }
    cout<<indent;
    cout<<(left ? '\\' : '/');
    cout<<"-----";
    cout<<t->type<<endl;
    if(t->left)
    {
        view(t->left, true, indent + (left ? "      " : "|     "));
    }
}
template<class T>
void AvlTree<T>::Menu_select()
{
	system("cls");
	string choose;
	cout<<"\t\t\t◇◇欢迎进入用户登录系统◇◇"<<endl;
	cout<<"\t\t\t       UserLoginSystem"<<endl;
	cout<<"\t\t\t                 version:1.0"<<endl;
	cout<<"\t\t\t============================"<<endl<<endl<<endl;
	cout<<"\t\t\t1.用户登录"<<endl<<endl;
	cout<<"\t\t\t2.用户注册"<<endl<<endl;
	cout<<"\t\t\t3.用户列表"<<endl<<endl;
	cout<<"\t\t\t4.退出系统"<<endl<<endl;
	cout<<"\t\t\t请输入你的选择(1~4)...";
	cin>>choose;
	cout<<endl;
	while(choose!="1"&&choose!="2"&&choose!="3"&&choose!="4")
	{
		system("cls");
		cout<<"\t\t\t◇◇欢迎进入用户登录系统◇◇"<<endl;
		cout<<"\t\t\t       UserLoginSystem"<<endl;
		cout<<"\t\t\t                 version:1.0"<<endl;
		cout<<"\t\t\t============================"<<endl<<endl<<endl;
		cout<<"\t\t\t1.用户登录"<<endl<<endl;
		cout<<"\t\t\t2.用户注册"<<endl<<endl;
		cout<<"\t\t\t3.用户列表"<<endl<<endl;
		cout<<"\t\t\t4.退出系统"<<endl<<endl;
		cout<<"\t\t\t请输入你的选择(1~4)...";
		cin>>choose;
		cout<<endl;
	}
	int i=atoi(choose.c_str());
	switch(i)
	{
		case 1:Menu_userLogin();break;
		case 2:Menu_insert();break;	
		case 3:Menu_view();break;
		case 4:
			{	system("cls");
				cout<<"\t\t\t◇◇成功退出用户登录系统◇◇"<<endl;
				return;
			}break;
		default:break;
	}
}

template<class T>
void AvlTree<T>::Menu_userLogin()
{
	system("cls");
	string name,password,choose,fh;
	Password inputP;
	cout<<"\t\t\t◇◇欢迎进入用户登录界面◇◇"<<endl;
	cout<<"\t\t\t============================"<<endl<<endl<<endl;
	cout<<"\t\t\t用户名：";
	cin>>name;
	cout<<endl<<endl;
	cout<<"\t\t\t密码：";
	inputP.inputPassword();
	password=inputP.getPassword();
	User loginUser(name,password);
	cout<<endl<<endl<<endl;
	cout<<"\t\t\t============================"<<endl<<endl<<endl;
	system("cls");
	if(AvlTree<T>::contains(loginUser))
	{
		cout<<"\t\t\t登录成功！欢迎你 ";
		cout<<loginUser.getName()<<endl<<endl;
		cout<<"\t\t\t============================"<<endl<<endl<<endl;
		cout<<"\t\t\t1.修改密码"<<endl;
		cout<<"\t\t\t2.删除用户"<<endl;
		cout<<"\t\t\t3.退出"<<endl<<endl;
		cout<<"\t\t\t请输入你的选择(1~3)...";
		cin>>choose;
		cout<<endl;
		while(choose!="1"&&choose!="2"&&choose!="3")
		{
			system("cls");
			cout<<"\t\t\t登录成功！欢迎你 ";
			cout<<loginUser.getName()<<endl<<endl;
			cout<<"\t\t\t============================"<<endl<<endl<<endl;
			cout<<"\t\t\t1.修改密码"<<endl;
			cout<<"\t\t\t2.删除用户"<<endl;
			cout<<"\t\t\t3.退出"<<endl<<endl;
			cout<<"\t\t\t输入有误,请重新输入(1~3)...";
			cin>>choose;
			cout<<endl;
		}
		int i=atoi(choose.c_str());
		system("cls");
		switch(i)
		{
			case 1:
				{
					cout<<"\t\t\t◇◇欢迎进入修改密码界面◇◇"<<endl;
					cout<<"\t\t\t============================"<<endl<<endl<<endl;
					cout<<"\t\t\t请输入你的原密码：";
					string oldPass;
					Password oldP;
					oldP.inputPassword();
					oldPass=oldP.getPassword();
					cout<<endl;
					while(oldPass!=loginUser.getPassword())
					{
						system("cls");
						cout<<"\t\t\t◇◇欢迎进入修改密码界面◇◇"<<endl;
						cout<<"\t\t\t============================"<<endl<<endl<<endl;
						cout<<"\t\t\t密码不正确，请重新输入原密码：";
						Password againP;
						againP.inputPassword();
						oldPass=againP.getPassword();
						cout<<endl;
					}
					cout<<"\t\t\t密码验证成功！"<<endl;
					cout<<"\t\t\t请输入你的新密码：";
					string newPass;
					cin>>newPass;
					cout<<endl;
					cout<<"\t\t\t请再次确认新密码：";
					string newPass_again;
					cin>>newPass_again;
					cout<<endl;
					while(newPass!=newPass_again)
					{
						cout<<"\t\t\t密码不一致！"<<endl;
						cout<<"\t\t\t请输入你的新密码：";
						cin>>newPass;
						cout<<endl;
						cout<<"\t\t\t请再次确认新密码：";
						cin>>newPass_again;
						cout<<endl;
					}
					User reviseUser(name,newPass);
					AvlTree<T>::remove(loginUser);
					AvlTree<T>::insert(reviseUser);
					AvlTree::write();
					cout<<"\t\t\t修改密码成功！"<<endl;
					cout<<"\t\t\t请输入任意键返回选择菜单...";
					cin>>fh;
					Menu_select();
					break;
				}
			case 2:
				{
					cout<<"\t\t\t◇◇欢迎进入用户删除界面◇◇"<<endl;
					cout<<"\t\t\t****************************"<<endl<<endl<<endl;
					cout<<"\t\t\t请验证你的密码：";
					string p;
					Password P;
					P.inputPassword();
					p=P.getPassword();
					cout<<endl;
					if(p!=loginUser.getPassword())
					{
						cout<<"\t\t\t密码不正确，请重新输入密码：";
						P.inputPassword();
						p=P.getPassword();
						cout<<endl;
					}
					cout<<"\t\t\t删除用户后将不可恢复！"<<endl;
					cout<<"\t\t\t1.确认删除"<<endl;
					cout<<"\t\t\t2.取消,返回选择菜单"<<endl;
					cout<<"\t\t\t请输入你的选择(1~3)...";
					cin>>choose;
					cout<<endl;
					while(choose!="1"&&choose!="2"&&choose!="3")
					{
						cout<<"\t\t\t输入有误,请重新输入(1~3)...";
						cin>>choose;
						cout<<endl;
					}
					int i=atoi(choose.c_str());
					system("cls");
					switch(i)
					{	
						case 1:
							{
								cout<<"\t\t\t删除成功！"<<endl;
								AvlTree<T>::remove(loginUser);
								AvlTree::write();
								cout<<"\t\t\t请输入任意键返回选择菜单...";
								cin>>fh;
								Menu_select();
								break;
							}
						case 2:
							Menu_select();break;
						default:
							break;
					}break;
				}
			case 3:
				Menu_select();break;
			default:
				break;
		}
	}
	else
	{
		cout<<"\t\t\t登录失败！用户不存在或密码错误"<<endl<<endl;
		cout<<"\t\t\t1.重新登录"<<endl;
		cout<<"\t\t\t2.注册用户"<<endl;
		cout<<"\t\t\t3.找回密码"<<endl;
		cout<<"\t\t\t请输入你的选择(1~3)";
		cin>>choose;
		cout<<endl;
		while(choose!="1"&&choose!="2"&&choose!="3")
		{
			system("cls");
			cout<<"\t\t\t登录失败！密码错误"<<endl<<endl;
			cout<<"\t\t\t1.重新登录"<<endl;
			cout<<"\t\t\t2.注册用户"<<endl;
			cout<<"\t\t\t3.找回密码"<<endl;
			cout<<"\t\t\t输入有误,请重新输入(1~3)...";
			cin>>choose;
			cout<<endl;
		}
		int i=atoi(choose.c_str());
		switch(i)
		{
			case 1:
				Menu_userLogin();break;
			case 2:
				Menu_insert();break;
			case 3:
				Menu_word();break;
		}
	}
}

template<class T>
void AvlTree<T>::Menu_insert()
{
	system("cls");
	string name,password,choose;
	cout<<"\t\t\t◇◇欢迎进入用户注册界面◇◇"<<endl;
	cout<<"\t\t\t****************************"<<endl<<endl<<endl;
	cout<<"\t\t\t注册新用户名：";
	cin>>name;
	cout<<endl;
	cout<<"\t\t\t密码：";
	cin>>password;
	cout<<endl;
	int n=0;
	if(name==""||password=="")
	{
		Menu_insert();
	}
	ifstream in("Userdata.txt");
	vector<string> info;
	string s1,s2;
	char c;
	while(in>>s1>>c>>s2)
		info.push_back(s1);
	for(int i=0;i<info.size();++i)
	{
		if(name==info[i])
			n=1;
	}
	User newUser=User(name,password);
	if(n==1)
	{
		cout<<"\t\t\t该用户名已经被注册!"<<endl<<endl;
		cout<<"\t\t\t1.重新注册"<<endl;
		cout<<"\t\t\t2.退出"<<endl;
		cout<<"\t\t\t请输入你的选择(1~2)"<<endl;
		cin>>choose;
		cout<<endl;
		while(choose!="1"&&choose!="2")
		{
			system("cls");
			cout<<"\t\t\t该用户名已经被注册!"<<endl<<endl;
			cout<<"\t\t\t1.重新注册"<<endl;
			cout<<"\t\t\t2.退出"<<endl;
			cout<<"\t\t\t输入有误,请重新输入(1~2)...";
			cin>>choose;
			cout<<endl;
		}
		int i=atoi(choose.c_str());
		switch(i)
		{
			case 1:
				Menu_insert();break;
			case 2:
				Menu_select();break;
			default:
				break;
		}
	}
	else
	{
		system("cls");
		cout<<"\t\t\t新用户 ";
		cout<<newUser.getName();
		cout<<"注册成功！"<<endl;
		AvlTree<T>::insert(newUser);
		AvlTree::write();
		cout<<"\t\t\t1.立即登录"<<endl;
		cout<<"\t\t\t2.退出"<<endl;
		cout<<"\t\t\t请输入你的选择(1~2)"<<endl;
		cin>>choose;
		cout<<endl;
		while(choose!="1"&&choose!="2")
		{
			system("cls");
			cout<<"\t\t\t新用户 ";
			cout<<newUser.getName();
			cout<<"	注册成功！"<<endl;
			cout<<"\t\t\t1.立即登录"<<endl;
			cout<<"\t\t\t2.退出"<<endl;
			cout<<"\t\t\t输入有误,请重新输入(1~2)...";
			cin>>choose;
			cout<<endl;
		}
		int i=atoi(choose.c_str());
		switch(i)
		{
			case 1:
				Menu_userLogin();break;
			case 2:
				Menu_select();break;
		}
	}
}
template<class T>
void AvlTree<T>::Menu_word()
{
	system("cls");
	string c="@";
	string name,email,words,fh;
	cout<<"\t\t\t◇◇欢迎进入找回密码留言界面◇◇"<<endl;
	cout<<"\t\t\t请输入用户名：";
	cin>>name;
	cout<<endl;
	cout<<"\t\t\t请输入留言内容：";
	cin>>words;
	cout<<endl;
	ofstream out("words.txt",ios::app);
	if(!out)
		cout<<"\t\t\t不能打开留言文件!"<<endl;
	out<<name<<" "<<words<<endl;
	out.close();
	cout<<"\t\t\t感谢你的留言，我们会尽快处理"<<endl;
	cout<<"\t\t\t请输入任意键返回选择菜单..."<<endl;
	cin>>fh;
	Menu_select();
}
template<class T>
void AvlTree<T>::Menu_view()
{
	string fh;
	system("cls");
	cout<<"\t\t\t◇◇用户列表◇◇"<<endl;
	if(root->right)
    {
        view(root->right, false," ");
    }
    cout<<root->type<<endl;
    if(root->left)
    {
        view(root->left, true," ");
    }
	cout<<"\t\t\t请输入任意键返回选择菜单..."<<endl;
	cin>>fh;
	Menu_select();
}