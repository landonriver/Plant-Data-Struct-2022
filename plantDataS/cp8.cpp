#include<bits/stdc++.h>
#define m 6600											//ɢ�б�ı� 
using namespace std;
struct Plant{											//ֲ����Ϣ���� 
	string name;										//���� 
	string sname;										//ѧ��
	string place[100];									//�ֲ��� 
	string detail;										//�������� 
};
typedef struct{            								//���ŵ�ַ��ɢ�б�Ĵ洢��ʾ
	Plant *key;
	int length;
}HashTable;
void InitHT(HashTable &HT){   							
	//ɢ�б��ʼ�� 
	HT.key = new Plant[20000];
	if(!HT.key)exit(0);
	HT.length = 0;
}
int H(string sname){
	//ʵ��ɢ�к������ַ���sname�и��ַ����±꣨��0��ʼ����ƽ�������ַ���Ӧ��ASCII��ֵ����Ӻ���6599ȡ�� 
	int sum=0;
    for(int i=0;i<sname.length();i++){
		sum+=((i)*(i)*int(sname[i]));
	}
	return sum%6599;
}
void HTInsert(HashTable &HT,Plant p,int &sumCmp){
	//��ɢ�б��в����µ�ֲ��p
    //�ڲ���Ĺ�����ͳ���ܵıȽϴ���sumCmp
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
		//��ǰ̽�� 
		
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
	//��� 
}
} 
void ReadFile(HashTable &HT,int &sumCmp,string filename){
	//��ȡplant.txt�ļ�������HT������ÿ��ֲ�����ݲ���ɢ�б� 
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
	//��ɢ�б�HT�в���ֲ��ѧ������key��Ԫ��
	//���ҵ����򷵻�ɢ�б�ĵ�Ԫ��ţ����򷵻�-1 
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
	//���ػ��ڿ��ŵ�ַ����ɢ�в��ҵ�ASL 
	return 1.0*sumCmp/HT.length;
} 
