#include "xxx.h"


void InitList(LinkList &L)
{//����һ���յĵ�����L
    L=new LNode;
    L->next=NULL;
}

void check(string filename)
{//��ȡ�ļ����һ�����ݣ�������ֲ����Ϣ 
	ifstream infile;
	infile.open(filename.c_str());    						//���ļ�
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
	//��plant.txt�ļ� 
	ReadFile(L,filename); 
	if(Insert(L,filename))   
	   check(filename); 
	else 
	   cout<<"����ʧ��\n";   
	return 0;
}
