#include <stdlib.h>
#include <fstream>
#include <time.h>
#include <iostream>
using namespace std;
//代码不多，仔细看，对你们来说easy
int main()
{
	ifstream fin("D:/aaaaaaaaaaaaaalerogo/VS2017/Project1/Debug/text.txt");		//这里写名单存放路径
	char str[541][541] = { 0 };				//emm
	char input = '\0';
	int nameNum = 0;
	while (fin.getline(str[nameNum], 541) && nameNum < 541)
	{
		nameNum++;
	}

	srand(time(NULL));
	while (cout << "输入c选择，输入其他退出" << endl && cin >> input && input == 'c')
	{
		cout << "幸运的孩子是： "<<"\n" << str[rand() % nameNum]<<"\n" << endl;
	}
	return 1;
}