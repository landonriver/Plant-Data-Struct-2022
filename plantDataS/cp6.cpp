#include<bits/stdc++.h>
using namespace std;
struct Plant{											//植物信息定义 
	string name;										//名称 
	string sname;										//学名
	string place[100];									//分布地 
	string detail;										//详情描述 
};
typedef struct{            								//顺序表
	Plant *plant;
	int length; 
	
	
}SqList;
void InitList(SqList &L){   							
	//顺序表初始化 
	L.plant = new Plant[20000];
	if(!L.plant)exit(0);
	L.length=0;
}
void ListInsert(SqList &L,int i,Plant p){
	//在顺序表L中第i个位置插入新的植物p 
	for(int j=L.length-1;j>=i-1;j--){
		L.plant[j+1] = L.plant[j];
	}	
		L.plant[i-1] = p;
		++L.length;
}
void ReadFile(SqList &L,string filename){
	//读取plant.txt文件，调用ListInsert函数将每条植物数据插入顺序表 
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
}
void Sort_Seq(SqList L){
	//根据植物学名对顺序表L由小到大进行排序
	Plant temp;
	for(int i = 1; i < L.length ; i++){
		for(int j = 0 ; j < L.length-i; j++){
			if(L.plant[j].sname > L.plant[j+1].sname){
				temp = L.plant[j+1];
				L.plant[j+1] = L.plant[j];
				L.plant[j] = temp;
			}
		}
	}
	
}
int Search_Bin(SqList L,string key){
	//在顺序表L中折半查找植物学名等于key的数据元素
	//若找到，则返回该元素在表中的下标，否则返回-1
 	int low =1,high = L.length;
 	int mid;
 	while(low <= high){
	 	mid = (low+high)/2;
	 	if(L.plant[mid].sname == key)return mid;
	 	else if(L.plant[mid].sname > key)high = mid -1;
	 	else low = mid+1;
	 }
	 return -1;
}
double ASL_Bin(SqList L){
	//返回基于顺序表的折半查找的ASL 
	double sum = 0;
	for(int i = 0; i<L.length; i++){
		int low=1,high=L.length,mid;
		int num = 0;
	
 		while(low <= high){
 		num++;
	 	mid = (low+high)/2;
	 	if(mid == i)break;
	 	else if(mid > i)high = mid -1;
	 	else low = mid+1;
		}
	sum+=num;
	}
	
	return sum/L.length;
} 
