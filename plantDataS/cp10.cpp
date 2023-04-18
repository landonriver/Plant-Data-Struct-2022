#include<bits/stdc++.h>
#include<string>

using namespace std;
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


int Is_EngChar(char c)
{//�ж��Ƿ�ΪӢ���ַ������ǣ��򷵻�1�������򷵻�0
    if((c>='0'&&c<='9')||(c>='a'&&c<='z'||(c>='A'&&c<='Z'))||c=='='||c=='!'||c=='?'||c=='_'||c=='{'||c=='}'||c==','|| c==';'||c=='-' || c=='/'||c=='('||c==')'|| c==':'||c=='��'||c=='['||c==']'||c=='.'|| c=='I')
        return 1;
    
    else
        return 0;
}

int Index_BF(string S,string T,int pos)
{//����ģʽT������S�е�pos���ַ���ʼ��һ�γ��ֵ�λ�á��������ڣ��򷵻�ֵΪ0 
 //���У�T�ǿգ�1��pos��S.length
 //Ϊ�ж��Ƿ�Ϊ���֣������Is_EngChar����
 
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
{//����Index_BF�㷨���йؼ���Ϣ��ѯ
	LinkList p = L->next;
	while(p){
		int flag = Index_BF(p->data.detail,keyWord,1);
		if(flag != 0){
			cout<<p->data.name<<endl;
		}
		p = p->next;
	}
}


