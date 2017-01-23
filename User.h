#ifndef USER//��ֹ�ظ�����
#define USER
#include<iostream>
#include<fstream>
#include<string>
using namespace std;
class User
{
private:
	string name;//�û���
	string password;//����
public:
	User(string new_name="null",string new_password="null"):name(new_name),password(new_password){}
	string getName();//��ȡ�û���
	string getPassword();//��ȡ����
	void setName( string );//�޸��û���
	void setPassword( string );//�޸�����
	//���������
	bool operator > (const User& u);
	bool operator < (const User& u);
	friend ostream &operator<<(ostream &os,const User &u);
	friend istream &operator>>(istream &in,User &u);
	bool operator == (const User& u);
	void read(istream &in);
	void write();
};
#endif