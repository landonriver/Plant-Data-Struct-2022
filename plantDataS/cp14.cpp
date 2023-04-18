#include<bits/stdc++.h>
#define MAXSIZE 6490
using namespace std;
struct Plant{											//ֲ����Ϣ���� 
	string name;										//���� 
	string sname;										//ѧ��
	string place[100];									//�ֲ��� 
	string detail;										//�������� 
};
typedef struct{            								//˳���
	Plant *p;									
	int length; 										//˳�����
}SqList;

void InitList(SqList &L){   							
	//˳����ʼ��
	L.p = new Plant[20000];
	if(!L.p)exit(0);
	L.length=0;
}
void ListInsert(SqList &L,int i,Plant p){
	//��˳���L�е�i+1��λ�ò����µ�ֲ��p
	//ע��p[0]�����ڱ���Ԫ 
	for(int j=L.length-1;j>=i-1;j--){
		L.p[j+1] = L.p[j];
	}	
		L.p[i-1] = p;
		++L.length;
}
void ReadFile(SqList &L,string filename){
	//��ȡplant.txt�ļ�������ListInsert������ÿ��ֲ�����ݲ���˳��� 
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
void SelectSort(SqList &L,int &cmpNum,int &movNum){
	//��˳���L����ѡ������ 
	//ע��p[0]����
	for(int i = 1 ; i < L.length ; i++){
		int k = i;
		for(int j = i+1 ; j<=L.length ; j++){
			cmpNum++;
			if(L.p[j].sname < L.p[k].sname) k = j;
		}
		if(k!=i){
			Plant t;
			t = L.p[i];movNum++;
			L.p[i] = L.p[k];movNum++;
			L.p[k] = t;movNum++;
		}
	}
}
