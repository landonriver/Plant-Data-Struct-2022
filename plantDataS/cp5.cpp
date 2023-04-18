#include<bits/stdc++.h>
using namespace std;
struct Plant{											//植物信息定义 
	string name;										//名称 
	string sname;										//学名
	string place[100];									//分布地 
	string detail;										//详情描述 
};
typedef struct LNode{          							//单链表 
	Plant data;
	struct LNode *next;
}LNode,*LinkList; 
void InitList(LinkList &L){   							
	//链表初始化 
	L = new LNode;
	L->next = NULL;
}
void ListInsert(LinkList &L,int i,Plant temp){
	//在带头结点的单链表L中第i个位置插入新结点
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
	//读取plant.txt文件，调用ListInsert函数将每条植物数据插入链表
	//返回树木数据的条数 
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
	//在带头结点的单链表L中查找植物学名为key的元素 
	LinkList p = L->next;
	while(p != NULL){
		if(p->data.sname == key)
		return p;
		p = p->next;
	}
	return NULL;
}
double ASL_LinkList(LinkList L,int count){
	//返回基于链表的顺序查找的ASL 
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
