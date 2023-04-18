#include<bits/stdc++.h>
using namespace std;
struct Plant
{
	//ֲ����Ϣ���� 
	string name;										//ֲ������ 
	string sname;										//ѧ��
	string place[100];									//�ֲ��� 
	string detail;										//�������� 
};

typedef struct LNode
{
    Plant data;    	   //����������   
    struct LNode *next; //ָ����
}LNode,*LinkList;

void ReadFile(LinkList &L,string filename)
{
	ifstream infile;
	infile.open(filename.c_str());
	LinkList r=L; 
	string temline;
	while(getline(infile,temline)){
		Plant temp;
		stringstream ss(temline);
		string s;
		int flag = 0;
		while(getline(ss,s,'#')){
			if(flag ==0) temp.name = s;
			if(flag ==1) temp.sname =s;
			if(flag ==2) {temp.place[0]=s;
			}
			if(flag == 3)temp.detail =s;
			flag++;
		}
		LinkList p;
		p = new LNode;
		p->data = temp;
		p->next = NULL;
		r->next = p;
		r = p;
		
	}
}

void Deletep(LinkList &L,string name,string filename)
{//ɾ��ָ��ֲ����Ϣ
	LinkList p = L;
	while(p->next!=NULL){
		if(p->next->data.name == name){
			LinkList q;
			q = p->next;
			p->next = q->next;
			delete q;
		}
		p = p->next;
	}
	ofstream outfine;
	outfine.open(filename,ios::out);
	while(p->next){
		outfine<<p->data.name<<"#"<<p->data.sname<<"#"<<p->data.place[0]<<"#"<<p->data.detail<<"\n";
		p = p->next;
	}
	
}
