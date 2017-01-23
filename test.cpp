#include "User.h"
#include "AvlTree.cpp"
int main() 
{
    AvlTree<User> userTree;
	string name,password;
	ifstream inUser("Userdata.txt");
	while(inUser>>name>>password)
	{
		User user(name,password);
		userTree.insert(user);
	}	
	userTree.Menu_select();
	return 0;
}