#include "xxx.h"


void InitList(LinkList &L)
{//构造一个空的单链表L
    L=new LNode;
    L->next=NULL;
}

void check(string filename)
{//读取文件最后一行内容，即新增植物信息 
	ifstream infile;
	infile.open(filename.c_str());    						//打开文件
	string line, last_line;
	while (getline(infile, line))
	{
		last_line = line;
	}
	cout << last_line << endl;
	infile.close();
}

int main(){
	LinkList L;
	string filename="data_edit/plant.txt";
	InitList(L); 
	//读plant.txt文件 
	ReadFile(L,filename); 
	if(Insert(L,filename))   
	   check(filename); 
	else 
	   cout<<"增加失败\n";   
	return 0;
}
