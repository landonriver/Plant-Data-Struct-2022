#include<bits/stdc++.h>
#include<string>

using namespace std;
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


int Is_EngChar(char c)
{//判断是否为英文字符，若是，则返回1，不是则返回0
    if((c>='0'&&c<='9')||(c>='a'&&c<='z'||(c>='A'&&c<='Z'))||c=='='||c=='!'||c=='?'||c=='_'||c=='{'||c=='}'||c==','|| c==';'||c=='-' || c=='/'||c=='('||c==')'|| c==':'||c=='×'||c=='['||c==']'||c=='.'|| c=='I')
        return 1;
    
    else
        return 0;
}

int Index_BF(string S,string T,int pos)
{//返回模式T在主串S中第pos个字符开始第一次出现的位置。若不存在，则返回值为0 
 //其中，T非空，1≤pos≤S.length
 //为判断是否为汉字，需调用Is_EngChar函数
 
	int ls = (int)S.size();
	int lt = (int)T.size();
	pos = 0;
	for(int i = pos ; i < ls ; i++ ){
		int flag = 0;
		for(int j = pos ; j < lt ; j++){
			if(S[i+j] != T[j]){
				flag = 1;
				break;
			}
		}if(flag == 0)return i;
	}
	return 0;
} 

void SearchInfo(LinkList L,string keyWord)
{//调用Index_BF算法进行关键信息查询
	LinkList p = L->next;
	while(p){
		int flag = Index_BF(p->data.detail,keyWord,1);
		if(flag != 0){
			cout<<p->data.name<<endl;
		}
		p = p->next;
	}
}


