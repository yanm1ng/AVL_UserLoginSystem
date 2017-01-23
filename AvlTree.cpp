#include "AvlTree.h"

template<class T>
typename AvlTree<T>::AvlNode * AvlTree<T>::findMin(AvlNode *t) //һֱ������������С�Ľڵ�
{
    if (t == NULL)
        return NULL;
    if (t->left == NULL)
        return t;
    return findMin(t->left);
}

template<class T>
typename AvlTree<T>::AvlNode * AvlTree<T>::findMax(AvlNode *t) //һֱ�������������Ľڵ�
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
    else if (t->type > x)//���xС��t��ֵ����t������������
        return contains(x, t->left);
    else if (t->type < x)//���x����t��ֵ����t������������
        return contains(x, t->right);
    else if (x == t->type )
        return true; //���ҵ��ڵ�ֵΪx�Ľڵ�
}

template<class T>
void AvlTree<T>::insert(T & x, AvlNode * & t) 
{
    if (t == NULL)//����ڵ�Ϊ��(��Ҷ�ڵ�),���ڴ˽ڵ㴦����newUser
        t = new AvlNode(x, NULL, NULL);
    else if (t->type > x) //���newUserС�ڸ��Ľڵ�,�ͼ����ڽڵ���������в���
	{
        insert(x, t->left);
        if (height(t->left) - height(t->right) == 2) //����ƽ������
		{
            if (t->left->type > x)
                rotateWithLeftChild(t);  //���t����������������ת���������һ����������
            else
                doubleWithLeftChild(t); //���t������������˫�������������������
        }
    } 
	else if (t->type < x) //���newUser���ڸ��Ľڵ�,�ͼ����ڽڵ���������в���
	{
        insert(x, t->right);
        if (height(t->right) - height(t->left) == 2) //����ƽ������
		{
            if (t->right->type < x)
                rotateWithRightChild(t);   //���t����������������ת���������һ����������
            else
                doubleWithRightChild(t);//���t������������˫�������������������
        }
    } else
        ; 
    t->height = max(height(t->left), height(t->right)) + 1; //�������ĸ߶�
}

template<class T>
void AvlTree<T>::remove(T & x, AvlNode * & t) 
{
    if (t == NULL)//һֱ���ҵ�t����Ҷ�ڵ�
        return;
    if (t->type > x) //���xС��t��ֵ��������t������������һֱ����Ҷ�ڵ�
	{
        remove(x, t->left);
        if (height(t->right) - height(t->left) == 2) 
		{
            if (height(t->right->right) >= height(t->right->left))//����ɾ��֮���������ڵ��ƽ������
                rotateWithRightChild(t);
            else
                doubleWithRightChild(t);
        }
    } 
	else if (t->type < x) //���x����t��ֵ��������t������������һֱ����Ҷ�ڵ�
	{
        remove(x, t->right);
        if (height(t->left) - height(t->right) == 2) 
		{
            if (height(t->left->left) >= height(t->left->right))//����ɾ��֮���������ڵ��ƽ������
                rotateWithLeftChild(t);
            else
                doubleWithLeftChild(t);
        }
    } 
	else if (t->left != NULL && t->right != NULL) //������ڲ��ڵ㣬��������������
	{
        t->type = findMin(t->right)->type;//����������������ߵģ���С���ڵ��õ���ǰ�ڵ�λ�ã��������Ա�֤����������������С����������������
        remove(t->type, t->right);
        t->height = max(height(t->left), height(t->right)) + 1;//��������
    } 
	else //���tֻ��һ����������t�Ƴ���t���������������������Ƶ�t��λ��
	{
        AvlNode *oldNode = t;
        t = (t->left != NULL) ? t->left : t->right;
        delete oldNode;
    }
    if (t != NULL)
        t->height = max(height(t->left), height(t->right)) + 1;
}

template<class T>
void AvlTree<T>::makeEmpty(AvlNode * & t) //�ݹ������������
{
    if (t != NULL) {
        makeEmpty(t->left);//���������
        makeEmpty(t->right);//���������
        delete t;//��յ�ǰ�ڵ�
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
void AvlTree<T>::printTree(AvlNode *t)  //�������
{
    if (t != NULL) {
        printTree(t->left);//����������
        cout << t->type << " �ڵ�߶�:" << t->height<<"  ƽ�����ӣ�"<<(height(t->left)-height(t->right))<<endl;//����ڵ�ֵ����Ҫ��T�����<< ���������
        printTree(t->right);//����������
    }
}
template<class T>
void AvlTree<T>::write(AvlNode *t) 
{
	ofstream out;
	out.open("Userdata.txt",ios::app);
	if (t != NULL) {
        write(t->left);//����������
        out << t->type <<endl;
        write(t->right);//����������
    }
	out.close();
}

template<class T>
int AvlTree<T>::height(AvlNode *t) //���ؽڵ�ĸ߶�
{
    return t == NULL ? -1 : t->height;
}

template<class T>
void AvlTree<T>::rotateWithLeftChild(AvlNode * & k2) //��������������ڵ�һ��ֱ��,���������ڵ㶼�������
{
    AvlNode *k1 = k2->left;     //k1Ϊk2������ӣ�����������k1��Ϊ�µ��������ڵ�

    k2->left = k1->right; //k1��������Ϊk2��������
    k1->right = k2;  //k2��Ϊk1���Ҷ���
	//���½ڵ�߶�
    k2->height = max(height(k2->left), height(k2->right)) + 1;
    k1->height = max(height(k1->left), k2->height) + 1;
	
    k2 = k1;  //k1��Ϊ��������ĸ��ڵ�
}

template<class T>
void AvlTree<T>::rotateWithRightChild(AvlNode * & k2) //��������������ڵ�һ��ֱ�ߣ����������ڵ㶼���Ҷ���
{
    AvlNode *k1 = k2->right;    //k1Ϊk2���Ҷ��ӣ�����������k1��Ϊ�µ��������ڵ�

    k2->right = k1->left; //k1��������Ϊk2��������
    k1->left = k2; //k2��Ϊk1�������
	//���½ڵ�߶�
    k2->height = max(height(k2->right), height(k2->left)) + 1;
    k1->height = max(height(k1->right), k2->height) + 1;

    k2 = k1; //k1��Ϊ��������ĸ��ڵ�
}
//������������ <
template<class T>
void AvlTree<T>::doubleWithLeftChild(AvlNode * & k3) {
    rotateWithRightChild(k3->left);
    rotateWithLeftChild(k3);
}
//�������������������ڵ������� >
template<class T>
void AvlTree<T>::doubleWithRightChild(AvlNode * & k3) {
    rotateWithLeftChild(k3->right);
    rotateWithRightChild(k3);
}
template<class T>
int AvlTree<T>::treeHeight(AvlNode *t) //�������ĸ߶ȣ�ȥ�����������߶��ټ�һ
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
	cout<<"\t\t\t���ӭ�����û���¼ϵͳ���"<<endl;
	cout<<"\t\t\t       UserLoginSystem"<<endl;
	cout<<"\t\t\t                 version:1.0"<<endl;
	cout<<"\t\t\t============================"<<endl<<endl<<endl;
	cout<<"\t\t\t1.�û���¼"<<endl<<endl;
	cout<<"\t\t\t2.�û�ע��"<<endl<<endl;
	cout<<"\t\t\t3.�û��б�"<<endl<<endl;
	cout<<"\t\t\t4.�˳�ϵͳ"<<endl<<endl;
	cout<<"\t\t\t���������ѡ��(1~4)...";
	cin>>choose;
	cout<<endl;
	while(choose!="1"&&choose!="2"&&choose!="3"&&choose!="4")
	{
		system("cls");
		cout<<"\t\t\t���ӭ�����û���¼ϵͳ���"<<endl;
		cout<<"\t\t\t       UserLoginSystem"<<endl;
		cout<<"\t\t\t                 version:1.0"<<endl;
		cout<<"\t\t\t============================"<<endl<<endl<<endl;
		cout<<"\t\t\t1.�û���¼"<<endl<<endl;
		cout<<"\t\t\t2.�û�ע��"<<endl<<endl;
		cout<<"\t\t\t3.�û��б�"<<endl<<endl;
		cout<<"\t\t\t4.�˳�ϵͳ"<<endl<<endl;
		cout<<"\t\t\t���������ѡ��(1~4)...";
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
				cout<<"\t\t\t���ɹ��˳��û���¼ϵͳ���"<<endl;
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
	cout<<"\t\t\t���ӭ�����û���¼������"<<endl;
	cout<<"\t\t\t============================"<<endl<<endl<<endl;
	cout<<"\t\t\t�û�����";
	cin>>name;
	cout<<endl<<endl;
	cout<<"\t\t\t���룺";
	inputP.inputPassword();
	password=inputP.getPassword();
	User loginUser(name,password);
	cout<<endl<<endl<<endl;
	cout<<"\t\t\t============================"<<endl<<endl<<endl;
	system("cls");
	if(AvlTree<T>::contains(loginUser))
	{
		cout<<"\t\t\t��¼�ɹ�����ӭ�� ";
		cout<<loginUser.getName()<<endl<<endl;
		cout<<"\t\t\t============================"<<endl<<endl<<endl;
		cout<<"\t\t\t1.�޸�����"<<endl;
		cout<<"\t\t\t2.ɾ���û�"<<endl;
		cout<<"\t\t\t3.�˳�"<<endl<<endl;
		cout<<"\t\t\t���������ѡ��(1~3)...";
		cin>>choose;
		cout<<endl;
		while(choose!="1"&&choose!="2"&&choose!="3")
		{
			system("cls");
			cout<<"\t\t\t��¼�ɹ�����ӭ�� ";
			cout<<loginUser.getName()<<endl<<endl;
			cout<<"\t\t\t============================"<<endl<<endl<<endl;
			cout<<"\t\t\t1.�޸�����"<<endl;
			cout<<"\t\t\t2.ɾ���û�"<<endl;
			cout<<"\t\t\t3.�˳�"<<endl<<endl;
			cout<<"\t\t\t��������,����������(1~3)...";
			cin>>choose;
			cout<<endl;
		}
		int i=atoi(choose.c_str());
		system("cls");
		switch(i)
		{
			case 1:
				{
					cout<<"\t\t\t���ӭ�����޸����������"<<endl;
					cout<<"\t\t\t============================"<<endl<<endl<<endl;
					cout<<"\t\t\t���������ԭ���룺";
					string oldPass;
					Password oldP;
					oldP.inputPassword();
					oldPass=oldP.getPassword();
					cout<<endl;
					while(oldPass!=loginUser.getPassword())
					{
						system("cls");
						cout<<"\t\t\t���ӭ�����޸����������"<<endl;
						cout<<"\t\t\t============================"<<endl<<endl<<endl;
						cout<<"\t\t\t���벻��ȷ������������ԭ���룺";
						Password againP;
						againP.inputPassword();
						oldPass=againP.getPassword();
						cout<<endl;
					}
					cout<<"\t\t\t������֤�ɹ���"<<endl;
					cout<<"\t\t\t��������������룺";
					string newPass;
					cin>>newPass;
					cout<<endl;
					cout<<"\t\t\t���ٴ�ȷ�������룺";
					string newPass_again;
					cin>>newPass_again;
					cout<<endl;
					while(newPass!=newPass_again)
					{
						cout<<"\t\t\t���벻һ�£�"<<endl;
						cout<<"\t\t\t��������������룺";
						cin>>newPass;
						cout<<endl;
						cout<<"\t\t\t���ٴ�ȷ�������룺";
						cin>>newPass_again;
						cout<<endl;
					}
					User reviseUser(name,newPass);
					AvlTree<T>::remove(loginUser);
					AvlTree<T>::insert(reviseUser);
					AvlTree::write();
					cout<<"\t\t\t�޸�����ɹ���"<<endl;
					cout<<"\t\t\t���������������ѡ��˵�...";
					cin>>fh;
					Menu_select();
					break;
				}
			case 2:
				{
					cout<<"\t\t\t���ӭ�����û�ɾ��������"<<endl;
					cout<<"\t\t\t****************************"<<endl<<endl<<endl;
					cout<<"\t\t\t����֤������룺";
					string p;
					Password P;
					P.inputPassword();
					p=P.getPassword();
					cout<<endl;
					if(p!=loginUser.getPassword())
					{
						cout<<"\t\t\t���벻��ȷ���������������룺";
						P.inputPassword();
						p=P.getPassword();
						cout<<endl;
					}
					cout<<"\t\t\tɾ���û��󽫲��ɻָ���"<<endl;
					cout<<"\t\t\t1.ȷ��ɾ��"<<endl;
					cout<<"\t\t\t2.ȡ��,����ѡ��˵�"<<endl;
					cout<<"\t\t\t���������ѡ��(1~3)...";
					cin>>choose;
					cout<<endl;
					while(choose!="1"&&choose!="2"&&choose!="3")
					{
						cout<<"\t\t\t��������,����������(1~3)...";
						cin>>choose;
						cout<<endl;
					}
					int i=atoi(choose.c_str());
					system("cls");
					switch(i)
					{	
						case 1:
							{
								cout<<"\t\t\tɾ���ɹ���"<<endl;
								AvlTree<T>::remove(loginUser);
								AvlTree::write();
								cout<<"\t\t\t���������������ѡ��˵�...";
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
		cout<<"\t\t\t��¼ʧ�ܣ��û������ڻ��������"<<endl<<endl;
		cout<<"\t\t\t1.���µ�¼"<<endl;
		cout<<"\t\t\t2.ע���û�"<<endl;
		cout<<"\t\t\t3.�һ�����"<<endl;
		cout<<"\t\t\t���������ѡ��(1~3)";
		cin>>choose;
		cout<<endl;
		while(choose!="1"&&choose!="2"&&choose!="3")
		{
			system("cls");
			cout<<"\t\t\t��¼ʧ�ܣ��������"<<endl<<endl;
			cout<<"\t\t\t1.���µ�¼"<<endl;
			cout<<"\t\t\t2.ע���û�"<<endl;
			cout<<"\t\t\t3.�һ�����"<<endl;
			cout<<"\t\t\t��������,����������(1~3)...";
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
	cout<<"\t\t\t���ӭ�����û�ע�������"<<endl;
	cout<<"\t\t\t****************************"<<endl<<endl<<endl;
	cout<<"\t\t\tע�����û�����";
	cin>>name;
	cout<<endl;
	cout<<"\t\t\t���룺";
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
		cout<<"\t\t\t���û����Ѿ���ע��!"<<endl<<endl;
		cout<<"\t\t\t1.����ע��"<<endl;
		cout<<"\t\t\t2.�˳�"<<endl;
		cout<<"\t\t\t���������ѡ��(1~2)"<<endl;
		cin>>choose;
		cout<<endl;
		while(choose!="1"&&choose!="2")
		{
			system("cls");
			cout<<"\t\t\t���û����Ѿ���ע��!"<<endl<<endl;
			cout<<"\t\t\t1.����ע��"<<endl;
			cout<<"\t\t\t2.�˳�"<<endl;
			cout<<"\t\t\t��������,����������(1~2)...";
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
		cout<<"\t\t\t���û� ";
		cout<<newUser.getName();
		cout<<"ע��ɹ���"<<endl;
		AvlTree<T>::insert(newUser);
		AvlTree::write();
		cout<<"\t\t\t1.������¼"<<endl;
		cout<<"\t\t\t2.�˳�"<<endl;
		cout<<"\t\t\t���������ѡ��(1~2)"<<endl;
		cin>>choose;
		cout<<endl;
		while(choose!="1"&&choose!="2")
		{
			system("cls");
			cout<<"\t\t\t���û� ";
			cout<<newUser.getName();
			cout<<"	ע��ɹ���"<<endl;
			cout<<"\t\t\t1.������¼"<<endl;
			cout<<"\t\t\t2.�˳�"<<endl;
			cout<<"\t\t\t��������,����������(1~2)...";
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
	cout<<"\t\t\t���ӭ�����һ��������Խ�����"<<endl;
	cout<<"\t\t\t�������û�����";
	cin>>name;
	cout<<endl;
	cout<<"\t\t\t�������������ݣ�";
	cin>>words;
	cout<<endl;
	ofstream out("words.txt",ios::app);
	if(!out)
		cout<<"\t\t\t���ܴ������ļ�!"<<endl;
	out<<name<<" "<<words<<endl;
	out.close();
	cout<<"\t\t\t��л������ԣ����ǻᾡ�촦��"<<endl;
	cout<<"\t\t\t���������������ѡ��˵�..."<<endl;
	cin>>fh;
	Menu_select();
}
template<class T>
void AvlTree<T>::Menu_view()
{
	string fh;
	system("cls");
	cout<<"\t\t\t����û��б���"<<endl;
	if(root->right)
    {
        view(root->right, false," ");
    }
    cout<<root->type<<endl;
    if(root->left)
    {
        view(root->left, true," ");
    }
	cout<<"\t\t\t���������������ѡ��˵�..."<<endl;
	cin>>fh;
	Menu_select();
}