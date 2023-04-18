#include<bits/stdc++.h>
#define m 6600											//ɢ�б�ı� 
using namespace std;
struct Plant{											//ֲ����Ϣ���� 
	string name;										//���� 
	string sname;										//ѧ��
	string place[100];									//�ֲ��� 
	string detail;										//��������
};
typedef struct LNode{          							//������ 
	Plant data;
	struct LNode *next;
}LNode,*LinkList;
LinkList H[m];                                         	//����ַ��ɢ�б�Ĵ洢��ʾ��m�������� 											
void InitList(){   							
	//�����ʼ�� 
	for(int i = 0 ; i < m; i++){
	H[i] = new LNode;
	H[i]->next = NULL;
	}
}
int Hash(string sname){
	//ʵ��ɢ�к������ַ���sname�и��ַ����±꣨��0��ʼ����ƽ�������ַ���Ӧ��ASCII��ֵ����Ӻ���6599ȡ�� 
	int sum=0;
    for(int i=0;i<sname.length();i++){
		sum+=((i)*(i)*int(sname[i]));
	}
	return sum%6599;
}
void ListInsert(Plant p,int &sumCmp){
	//��ɢ�б��в����µ�ֲ��p
    //�ڲ���Ĺ�����ͳ���ܵıȽϴ���sumCmp
	int cnt = Hash(p.sname);
	LinkList r = H[cnt];
	while(r->next){
		r = r->next;
		sumCmp++;   
	}
	sumCmp++;
	LinkList t = new LNode;
	t->data = p;
	t->next = NULL;
	r->next = t;
	r = t;
} 
int ReadFile(int &sumCmp,string filename){
	//��ȡplant.txt�ļ�������ListInsert������ÿ��ֲ�����ݲ���˳���
	//������ľ���ݵ�����  
 	ifstream infile;
 	int count = 0;
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
 		ListInsert(temp,sumCmp);
 		count++;
 	}
 	return count;
}
int SearchHL(string key){
	//��ɢ�б�HT�в���ֲ��ѧ������key��Ԫ��
	//���ҵ����򷵻�ɢ�б�ĵ�Ԫ��ţ����򷵻�-1 
	int cnt = Hash(key);
	LinkList r = H[cnt];
	while(r->next){
		if(r->next->data.sname == key)return cnt;
		r = r->next;
	}
	return -1;
}
double ASL_HL(int sumCmp,int count){
	//���ػ�������ַ����ɢ�в��ҵ�ASL 
	return 1.0*sumCmp/count;
} 
