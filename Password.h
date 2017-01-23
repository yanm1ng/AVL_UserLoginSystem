//输入 密码 回显 * 
#include <iostream>
#include<conio.h>
#include<string>
using namespace std;
class Password
{
	public:
	Password()//构造函数，初始化密码，使之为空
	{
		psw="";//初始化密码为空"";
		length=0; //初始化密码长度
	}
	void inputPassword();//用于输入并显示*为密码

	string getPassword();//返回密码字符串

	private:
	string psw;//用于存密码的字符串；
	int length;//密码长度
};
