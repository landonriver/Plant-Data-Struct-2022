#include "iostream"
#include<bits/stdc++.h>
#include <string>
#include<stdlib.h>
using namespace std;

#define MAXLEN 5000			//������󳤶�

struct Plant
{
	//ֲ����Ϣ���� 
	string name;										//ֲ������ 
	string sname;										//ѧ��
	string place[100];									//�ֲ��� 
	string detail;										//�������� 
};


typedef struct LNode
{
    Plant data;    	   //����������   
    struct LNode *next; //ָ����
}LNode,*LinkList;

void ReadFile(LinkList &L,string filename)
{//��ȡ�ļ��������ݴ�������L
	ifstream infile;
	infile.open(filename.c_str());
	LinkList r=L; 
	string temline;
	while(getline(infile,temline)){
		Plant temp;
		stringstream ss(temline);
		string s;
		int flag = 0;
		while(getline(ss,s,'#')){
			if(flag ==0) temp.name = s;
			if(flag ==1) temp.sname =s;
			if(flag ==2) {temp.place[0]=s;
			}
			if(flag == 3)temp.detail =s;
			flag++;
		}
		LinkList p;
		p = new LNode;
		p->data = temp;
		p->next = NULL;
		r->next = p;
		r = p;
	}
}


void GetChinese(string target,string ChiKey[],int *len)
{//�����ִ洢��������,�����˺������뷨�µı��
	int tnum = target.length();
	for(int i = 0 ; i < tnum ; i++){
		char c = target[i];
	    if((c>='0'&&c<='9')||(c>='a'&&c<='z'||(c>='A'&&c<='Z'))||c=='='||c=='!'||c=='?'||c=='_'||c=='{'||c=='}'||c==','|| c==';'||c=='-' || c=='/'||c=='('||c==')'|| c==':'||c=='��'||c=='['||c==']'||c=='.'|| c==' '){
			ChiKey[++*len]=target[i];

		}
		else{
			ChiKey[++*len]=target[i];
			ChiKey[*len]+=target[i+1];
			i++;
			ChiKey[*len]+=target[i+1];
			i++;
		}
	}
}
void GetNext(string pattern[], int next[],int newlength)
{//��ģʽ��pattern��next����ֵ����������next
	string PS[100];
	GetChinese(*pattern,PS,&newlength);
	int i = 1;
	next[1] = 0;
	int j = 0;
	while(i < newlength){
		if(j == 0||PS[i] == PS[j]){
			i++;
			j++;
			next[i] = j;
		}else j = next[j];
	}
	
}

int Index_KMP(string target[], string pattern[], int next[],int len1,int len2)
{//KMPƥ���㷨,targetΪ������patternΪ�Ӵ�
	//ƥ��ɹ����������������Ӵ���һ�γ��ֵ�λ�ã����򷵻�-1
	//����GetNext������ȡģʽ����next����
	GetNext(pattern,next,len2);
	string TS[2000];
	string PS[2000];
	GetChinese(*target,TS,&len1);
	GetChinese(*pattern,PS,&len2);
	int i = 1;
	int j = 1;
	while(i <= len1&&j <= len2){
		if(j==0 || TS[i] == PS[j]){
			i++;
			j++;
		}else j = next[j];
	}
	if(j > len2) return i-len2;
	else return 0;
}

void SearchInfo(LinkList L,string keyword)
{//���õ���Index_KMP�������йؼ���Ϣ��ѯ
	LinkList p = L->next;
	int next[200];
	int len1 = 0,len2 = 0;
		while(p){
		int flag = Index_KMP(&p->data.detail,&keyword,next,len1,len2);
		if(flag != 0){
			cout<<p->data.name<<endl;
		}
		p = p->next;
	}
}
