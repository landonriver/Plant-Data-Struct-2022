#include<bits/stdc++.h>
#define m 6600											//散列表的表长 
using namespace std;
struct Plant{											//植物信息定义 
	string name;										//名称 
	string sname;										//学名
	string place[100];									//分布地 
	string detail;										//详情描述 
};
typedef struct{            								//开放地址法散列表的存储表示
	Plant *key;
	int length;
}HashTable;
void InitHT(HashTable &HT){   							
	//散列表初始化 
	HT.key = new Plant[20000];
	if(!HT.key)exit(0);
	HT.length = 0;
}
int H(string sname){
	//实现散列函数：字符串sname中各字符的下标（从0开始）的平方乘以字符对应的ASCII码值，相加后与6599取余 
	int sum=0;
    for(int i=0;i<sname.length();i++){
		sum+=((i)*(i)*int(sname[i]));
	}
	return sum%6599;
}
void HTInsert(HashTable &HT,Plant p,int &sumCmp){
	//往散列表中插入新的植物p
    //在插入的过程中统计总的比较次数sumCmp
    int cnt = H(p.sname);
    if(HT.key[cnt].sname.empty()){
		HT.key[cnt]=p;
		sumCmp++;
		return ;
	}else{
		int i;
		sumCmp++;
		for(i=cnt+1;i<m;i++){
			sumCmp++;
			if(HT.key[i].sname.empty()){
				HT.key[i]=p;
				break;
			}
		}
		//向前探测 
		
		if(i==m){
		for(int j=0;j<=cnt;j++){
			if(HT.key[j].sname.empty())
			{
				HT.key[j]=p;
				break;
			}
			sumCmp++;
		}
	}
	//向后 
}
} 
void ReadFile(HashTable &HT,int &sumCmp,string filename){
	//读取plant.txt文件，调用HT函数将每条植物数据插入散列表 
 	ifstream infile;
 	infile.open(filename.c_str());
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
 			if(flag ==3)temp.detail =s;	
 			flag++;
 		}
 		HTInsert(HT,temp,sumCmp);
 		HT.length++;
 	}
}
int SearchHash(HashTable HT,string key){
	//在散列表HT中查找植物学名等于key的元素
	//若找到，则返回散列表的单元标号，否则返回-1 
	int cnt = H(key);
	if(HT.key[cnt].sname == key){
		return cnt;
	} else {
		int i;
		for(i=cnt+1;i<m;i++){
			if(HT.key[i].sname==key){
				return i;
			}
		}
		if(i==m){
		for(int j=0;j<=cnt;j++){
			if(HT.key[j].sname==key)
			{
				return j;
			}
		}
	}
	}
	return -1;
}

double ASL_HT(HashTable HT,int sumCmp){
	//返回基于开放地址法的散列查找的ASL 
	return 1.0*sumCmp/HT.length;
} 
