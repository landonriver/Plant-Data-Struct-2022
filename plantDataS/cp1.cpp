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


void ReadFile(LinkList &L, string filename)
{//���ļ��ж�ȡ���ݣ���������L��
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
			if(flag ==2) {
				stringstream ssplace(s);
				string place;
				int placenum = 0;
				while(getline(ssplace,place,'@')){
					temp.place[placenum] = place;
					placenum++;					
				}
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

int exam(LinkList L,string name)
{//�жϸ�ֲ������name�Ƿ������plant.txt��
	LinkList p = L->next;
	while(p){
		if(p->data.name.compare(name) == 0)return 1;
		p = p->next;
	}
	return 2;
	
	
}

bool Insert(LinkList &L, string filename)
{//����ֲ����Ϣ������ֲ������ơ�ѧ�����ֲ��غ�����������Ϣ������ֲ��Ļ�����Ϣ��ӵ�plant.txt�е����
 //�����ֲ�����ƴ�����plant.txt�У�����false�����򣬷���true

	Plant ap;
	int placenum;
	getline(cin,ap.name);
    string temp;   	
	int flag = exam(L,ap.name);
	if(flag == 1)return false;

	getline(cin,ap.sname);
	cin>>placenum;
	for(int i = 0 ; i < placenum ;i++){
		cin>>ap.place[i]; 
	}
	getchar();
	getline(cin,ap.detail);
    
	ofstream outfine(filename);
		outfine<<ap.name<<"#"<<ap.sname<<"#";
		for(int i = 0 ;i < placenum-1;i++){
			outfine<<ap.place[i]<<"@";
		}
		outfine<<ap.place[placenum-1];
				outfine<<"#"<<ap.detail<<endl;
				return true;
				
}
