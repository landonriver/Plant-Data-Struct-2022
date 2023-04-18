#include<bits/stdc++.h>
using namespace std;
struct Plant{											//ֲ����Ϣ���� 
	string name;										//���� 
	string sname;										//ѧ��
	string place[100];									//�ֲ��� 
	string detail;										//�������� 
};
typedef struct BSTNode{									//���������� 
   Plant data;
   struct BSTNode *lchild,*rchild;
}BSTNode,*BSTree;
void InitBSTree(BSTree &T){   							
	//������������ʼ�� 
	T = new BSTNode;
	T->lchild = NULL;
	T->rchild = NULL;
}
void BSTreeInsert(BSTree &T,Plant temp){
	BSTNode *S;
	if(!T){
 		S = new BSTNode;
		S->data = temp;
		S->lchild = S->rchild = NULL;
		T = S;
	}
	else if(temp.sname<T->data.sname){
		BSTreeInsert(T->lchild,temp);
	}else if(temp.sname>T->data.sname){
		BSTreeInsert(T->rchild,temp);
	}
}

int ReadFile(BSTree &T,string filename){
	//��ȡplant.txt�ļ�������BSTreeInsert������ÿ��ֲ�����ݲ������������
	//������ľ���ݵ����� 
	ifstream infile;
	infile.open(filename.c_str());
	string temline;
	int i = 0;
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
		BSTreeInsert(T,temp);
		i++;				
	}
	return i;
}

void InOrderTraverse(BSTree T){
	//�������������T�ĵݹ��㷨
    if (T) {
        InOrderTraverse(T->lchild);
   		cout<<T->data.sname<<endl;
        InOrderTraverse(T->rchild);
    }
}
BSTree SearchBST(BSTree T,string key){
	//�ڸ�ָ��T��ָ�����������еݹ�ز���ĳֲ��ѧ������key������Ԫ��
 	//�����ҳɹ����򷵻�ָ�������Ԫ�ؽ���ָ�룬���򷵻ؿ�ָ��
	if((!T)||key ==T->data.sname)return T;
	else if(key<T->data.sname)return SearchBST(T->lchild,key);
	else return SearchBST(T->rchild,key);
}

int BSTasl(BSTree t, int d)//��Ȩֵ��ע�����ʱd��ֵΪ0
{
    d++;
    int a = d;
    if (t->lchild)
        d += BSTasl(t->lchild, a);
    if (t->rchild)
        d += BSTasl(t->rchild, a);
    return d;
}


double ASL_BSTree(BSTree T,int count){
	//���ػ��ڶ������������ҵ�ASL
	return BSTasl(T, -1) * 1.0 / count;
} 
