#include "iostream"
#include<bits/stdc++.h>
#include <string>
#include<stdlib.h>
using namespace std;

#define MAXLEN 5000			//串的最大长度

struct Plant
{
	//植物信息定义 
	string name;										//植物名称 
	string sname;										//学名
	string place[100];									//分布地 
	string detail;										//详情描述 
};


typedef struct LNode
{
    Plant data;    	   //结点的数据域   
    struct LNode *next; //指针域
}LNode,*LinkList;

void ReadFile(LinkList &L,string filename)
{//读取文件，将数据存入链表L
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
{//将汉字存储在数组里,包括了汉字输入法下的标点
	int tnum = target.length();
	for(int i = 0 ; i < tnum ; i++){
		char c = target[i];
	    if((c>='0'&&c<='9')||(c>='a'&&c<='z'||(c>='A'&&c<='Z'))||c=='='||c=='!'||c=='?'||c=='_'||c=='{'||c=='}'||c==','|| c==';'||c=='-' || c=='/'||c=='('||c==')'|| c==':'||c=='×'||c=='['||c==']'||c=='.'|| c==' '){
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
{//求模式串pattern的next函数值并存入数组next
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
{//KMP匹配算法,target为主串，pattern为子串
	//匹配成功返回主串中所含子串第一次出现的位置，否则返回-1
	//调用GetNext函数获取模式串的next数组
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
{//调用调用Index_KMP函数进行关键信息查询
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
