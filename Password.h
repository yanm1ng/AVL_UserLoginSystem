//���� ���� ���� * 
#include <iostream>
#include<conio.h>
#include<string>
using namespace std;
class Password
{
	public:
	Password()//���캯������ʼ�����룬ʹ֮Ϊ��
	{
		psw="";//��ʼ������Ϊ��"";
		length=0; //��ʼ�����볤��
	}
	void inputPassword();//�������벢��ʾ*Ϊ����

	string getPassword();//���������ַ���

	private:
	string psw;//���ڴ�������ַ�����
	int length;//���볤��
};
