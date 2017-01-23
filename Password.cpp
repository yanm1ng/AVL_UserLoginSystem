#include "Password.h"
void Password::inputPassword()
{
	char temp_c;
	while(true)
	{
		temp_c=getch();  //输入一个字符
		if(temp_c!=char(13))  //char(13)是回车字符，如果遇到回车字符退出while
		{
			switch  (temp_c)
			{
			  case 8://char(8)代表空格符号
				if(length!=0)
				{
					cout<<"\b";//移动光标到当前密码长度位置，一次Backspace退一个*；
					psw=psw.substr(0,length-1);
					length--;
				}
				else ;
				break;
			default:
				cout<<"*"; //*号表示密码
				psw+=temp_c;//连成密码字符串
				length++;
				break;
			}
		}
		else break;
	}   
}
string Password::getPassword()
{
	return psw; 
}