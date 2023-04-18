#include<bits/stdc++.h>
using namespace std;
struct Plant
{
	//植物信息定义 
	string name;										//植物名称 
	string sname;										//学名
	string place[100];									//分布地 
	string detail;										//详情描述 
};


typedef struct LNode
{
    Plant data;    	   //结点的数据域   
    struct LNode *next; //指针域
}LNode,*LinkList;


void ReadFile(LinkList &L, string filename)
{//从文件中读取数据，存入链表L中
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
{//判断该植物名称name是否存在于plant.txt中
	LinkList p = L->next;
	while(p){
		if(p->data.name.compare(name) == 0)return 1;
		p = p->next;
	}
	return 2;
	
	
}

bool Insert(LinkList &L, string filename)
{//增加植物信息，输入植物的名称、学名、分布地和详情描述信息，将该植物的基本信息添加到plant.txt中的最后
 //如果该植物名称存在于plant.txt中，返回false，否则，返回true

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
