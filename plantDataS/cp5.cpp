#include<bits/stdc++.h>
using namespace std;
struct Plant{											//ֲ����Ϣ���� 
	string name;										//���� 
	string sname;										//ѧ��
	string place[100];									//�ֲ��� 
	string detail;										//�������� 
};
typedef struct LNode{          							//������ 
	Plant data;
	struct LNode *next;
}LNode,*LinkList; 
void InitList(LinkList &L){   							
	//�����ʼ�� 
	L = new LNode;
	L->next = NULL;
}
void ListInsert(LinkList &L,int i,Plant temp){
	//�ڴ�ͷ���ĵ�����L�е�i��λ�ò����½��
	LinkList r = L;
	int j = 0;
	while(r&&(j<i-1)){
		r = r->next;
		j++;
	}
	LinkList p = new LNode;
	p->data = temp;
	p->next = r->next;
	r->next = p;
}

int ReadFile(LinkList &L,string filename){
	//��ȡplant.txt�ļ�������ListInsert������ÿ��ֲ�����ݲ�������
	//������ľ���ݵ����� 
	ifstream infile;
	infile.open(filename.c_str());
	string temline;
	int i = 1;
	while(getline(infile,temline)){
		Plant temp;
		stringstream ss(temline);
		string s;
		int flag = 0;
		while(getline(ss,s,'#')){
			if(flag ==0) temp.name = s;
			if(flag ==1) temp.sname =s;
			if(flag ==2) {
				stringstream ssplace(s);
				string place;
				int placenum = 0;
				while(getline(ssplace,place,'@')){
					temp.place[placenum] = place;
					placenum++;					
				}
			}	
			if(flag ==3)temp.detail =s;	
			flag++;
		}
		ListInsert(L,i,temp);
		i++;			
	}
	return i-1;
}
LNode *LocateElem(LinkList L,string key){
	//�ڴ�ͷ���ĵ�����L�в���ֲ��ѧ��Ϊkey��Ԫ�� 
	LinkList p = L->next;
	while(p != NULL){
		if(p->data.sname == key)
		return p;
		p = p->next;
	}
	return NULL;
}
double ASL_LinkList(LinkList L,int count){
	//���ػ��������˳����ҵ�ASL 
	double sum = 0;
	int i = 0;
	LinkList p = L->next;
	while(p){
		i++;
		sum+=i;
		p = p->next;
	}
	return sum/count;
} 
