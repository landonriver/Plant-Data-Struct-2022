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
		if(p->data.name.compare(name) == 0)return 2;
		p = p->next;
	}
	return 1;
	
}

bool Insert(LinkList &L, string filename)
{//����ֲ����Ϣ������ֲ������ơ�ѧ�����ֲ��غ�����������Ϣ������ֲ��Ļ�����Ϣ��ӵ�plant.txt�е����
 //�����ֲ�����ƴ�����plant.txt�У�����false�����򣬷���true
//	Plant ap;
//	cin>>ap.name>>ap.sname>>ap.place[1]>>ap.detail;
//	int flag = exam(L,ap.name);
//	if(flag == 2)return false;
//	ofstream outfine(filename);
//	outfine<<ap.name<<"#"<<ap.sname<<"#"<<ap.place[1]<<"#"<<ap.detail;
//	return true;



	Plant ap;
	int placenum;
	cin>>ap.name>>ap.sname;
	cin>>placenum;
	for(int i = 0 ; i < placenum ;i++){
		cin>>ap.place[i];
	}
	cin>>ap.detail;
	
	
	int flag = exam(L,ap.name);
	if(flag == 2)return false;

	ofstream outfine(filename);
	outfine<<ap.name<<"#"<<ap.sname<<"#";
	for(int i = 0 ;i < placenum-1;i++){
		outfine<<ap.place[i]<<"@";
	}
	outfine<<ap.place[placenum-1];
	outfine<<"#"<<ap.detail;
	return true;

}

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
