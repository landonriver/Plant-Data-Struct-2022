#include<bits/stdc++.h>
using namespace std;
struct Plant{											//ֲ����Ϣ���� 
	string name;										//���� 
	string sname;										//ѧ��
	string place[100];									//�ֲ��� 
	string detail;										//�������� 
};
typedef struct{            								//˳���
	Plant *plant;
	int length; 
}SqList;
void InitList(SqList &L){   							
	//˳����ʼ�� 
	L.plant = new Plant[20000];
	if(!L.plant)exit(0);
	L.length=0;
}
void ListInsert(SqList &L,int i,Plant p){
	//��˳���L�е�i��λ�ò����µ�ֲ��p 
	for(int j=L.length-1;j>=i-1;j--){
		L.plant[j+1] = L.plant[j];
	}	
		L.plant[i-1] = p;
		++L.length;
}
void ReadFile(SqList &L,string filename){
	//��ȡplant.txt�ļ�������ListInsert������ÿ��ֲ�����ݲ���˳��� 
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
int Search_Seq(SqList L,string key){
	//��˳���L��˳�����ֲ��ѧ������key������Ԫ��
	//���ҵ����򷵻ظ�Ԫ���ڱ��е��±꣬���򷵻�-1
	for(int i = 0; i<=L.length-1;i++){
		if(L.plant[i].sname == key)
		return i;
	}
	return -1;
}
double ASL_Seq(SqList L){
	//���ػ���˳����˳����ҵ�ASL 
	double sum;
	for(int i = 0 ; i <= L.length-1 ; i++){
		sum+=(i+1);
	}
	return sum/L.length;
} 
