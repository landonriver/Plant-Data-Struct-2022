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
int cmpNum=0;											//�Ƚϴ���
int movNum=0;											//�ƶ�����
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
int Partition(SqList &L, int low, int high){
	//��˳���L�е��ӱ�p[low..high]����һ�����򣬷�������λ��
	//ע��p[0]���������¼
	//���ڴ˶ԱȽϴ������ƶ����������޸�
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
	//����ǰ�ó�ֵ��low=1; high=L.length;
 	//��˳���L�е�������L.p[low..high]����������
	if(low < high){
		
		int piv = Partition(L,low,high);
		QSort(L,low,piv-1);
		QSort(L,piv+1,high);
	}
}
void QuickSort(SqList &L){
	//��˳���L���������� 
	QSort(L,1,L.length);

}
