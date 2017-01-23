#ifndef USER//防止重复定义
#define USER
#include<iostream>
#include<fstream>
#include<string>
using namespace std;
class User
{
private:
	string name;//用户名
	string password;//密码
public:
	User(string new_name="null",string new_password="null"):name(new_name),password(new_password){}
	string getName();//获取用户名
	string getPassword();//获取密码
	void setName( string );//修改用户名
	void setPassword( string );//修改密码
	//运算符重载
	bool operator > (const User& u);
	bool operator < (const User& u);
	friend ostream &operator<<(ostream &os,const User &u);
	friend istream &operator>>(istream &in,User &u);
	bool operator == (const User& u);
	void read(istream &in);
	void write();
};
#endif