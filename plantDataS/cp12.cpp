#include<bits/stdc++.h>
#define MAXSIZE 6490
using namespace std;
struct Plant{											//植物信息定义 
	string name;										//名称 
	string sname;										//学名
	string place[100];									//分布地 
	string detail;										//详情描述 
};
typedef struct{            								//顺序表
	Plant *p;									
	int length; 										//顺序表长度
}SqList;

void InitList(SqList &L){   							
	//顺序表初始化
	L.p = new Plant[20000];
	if(!L.p)exit(0);
	L.length=0;
}
void ListInsert(SqList &L,int i,Plant p){
	//在顺序表L中第i+1个位置插入新的植物p
	//注：p[0]用做哨兵单元 
	for(int j=L.length-1;j>=i-1;j--){
		L.p[j+1] = L.p[j];
	}	
		L.p[i-1] = p;
		++L.length;
}
void ReadFile(SqList &L,string filename){
	//读取plant.txt文件，调用ListInsert函数将每条植物数据插入顺序表 
	ifstream infile;
	infile.open(filename.c_str());
	string temline;
	int i = 2;
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
}

void InsertSort(SqList &L,int &cmpNum,int &movNum){
	//对顺序表L做直接插入排序
	//注：p[0]用做哨兵单元 
	int j;
	for(int i=2;i<=L.length;i++){
		cmpNum++;
		if(L.p[i].sname<L.p[i-1].sname){
			L.p[0]=L.p[i];movNum++;
			L.p[i]=L.p[i-1];movNum++;
			for( j=i-2;cmpNum++,L.p[0].sname<L.p[j].sname;j--){
				L.p[j+1]=L.p[j];movNum++;
			}
			L.p[j+1]=L.p[0];movNum++;
		}
	}
}
