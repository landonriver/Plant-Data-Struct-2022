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
int cmpNum=0;											//比较次数
int movNum=0;											//移动次数
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
int Partition(SqList &L, int low, int high){
	//对顺序表L中的子表p[low..high]进行一趟排序，返回枢轴位置
	//注：p[0]用做枢轴记录
	//需在此对比较次数和移动次数进行修改
	L.p[0] = L.p[low];movNum++;
	string pivkey = L.p[low].sname;

	while(low < high){
		while(low < high &&++cmpNum &&L.p[high].sname >= pivkey){--high;} 
		L.p[low] = L.p[high];movNum++;
		while(low < high&&++cmpNum && L.p[low].sname <= pivkey){++low;}
		L.p[high] = L.p[low];movNum++;
	}
	L.p[low] = L.p[0];movNum++;
	return low;
}									

void QSort(SqList &L,int low,int high){
	//调用前置初值：low=1; high=L.length;
 	//对顺序表L中的子序列L.p[low..high]做快速排序
	if(low < high){
		
		int piv = Partition(L,low,high);
		QSort(L,low,piv-1);
		QSort(L,piv+1,high);
	}
}
void QuickSort(SqList &L){
	//对顺序表L做快速排序 
	QSort(L,1,L.length);

}
