#include "Password.h"
void Password::inputPassword()
{
	char temp_c;
	while(true)
	{
		temp_c=getch();  //����һ���ַ�
		if(temp_c!=char(13))  //char(13)�ǻس��ַ�����������س��ַ��˳�while
		{
			switch  (temp_c)
			{
			  case 8://char(8)����ո����
				if(length!=0)
				{
					cout<<"\b";//�ƶ���굽��ǰ���볤��λ�ã�һ��Backspace��һ��*��
					psw=psw.substr(0,length-1);
					length--;
				}
				else ;
				break;
			default:
				cout<<"*"; //*�ű�ʾ����
				psw+=temp_c;//���������ַ���
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