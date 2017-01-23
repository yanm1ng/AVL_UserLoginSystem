#include "User.h"
string User::getName()
{
	return name;
}
string User::getPassword()
{
	return password;
}
void User::setName(string str)
{
	name=str;
}
void User::setPassword(string str)
{
	password=str;
}
bool User::operator > (const User& u)
{
	if(name>u.name)
		return true;
	else
		return false;
}
bool User::operator < (const User& u)
{
	if(name<u.name)
		return true;
	else
		return false;
}
bool User::operator == (const User& u)
{
	if(name==u.name && password==u.password)
		return true;
	else
		return false;
}
ostream & operator<<(ostream &os,const User &u)
{
    os<<u.name<<" "<<u.password<<" ";
    return os;
}
istream &operator>>(istream &in,User &u)
{
	u.read(in);
	return in;
}
void User::read(istream & in)
{
	in>>name>>password;
}
void User::write()
{
	ofstream out("Userdata.txt");
	out<<name<<" "<<password<<endl;
}