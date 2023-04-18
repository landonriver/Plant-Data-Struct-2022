#include<bits/stdc++.h>
using namespace std;
struct Plant{											//植物信息定义 
	string name;										//名称 
	string sname;										//学名
	string place[100];									//分布地 
	string detail;										//详情描述 
};
typedef struct BSTNode{									//二叉排序树 
   Plant data;
   struct BSTNode *lchild,*rchild;
}BSTNode,*BSTree;
void InitBSTree(BSTree &T){   							
	//二叉排序树初始化 
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
	//读取plant.txt文件，调用BSTreeInsert函数将每条植物数据插入二叉排序树
	//返回树木数据的条数 
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
	//中序遍历二叉树T的递归算法
    if (T) {
        InOrderTraverse(T->lchild);
   		cout<<T->data.sname<<endl;
        InOrderTraverse(T->rchild);
    }
}
BSTree SearchBST(BSTree T,string key){
	//在根指针T所指二叉排序树中递归地查找某植物学名等于key的数据元素
 	//若查找成功，则返回指向该数据元素结点的指针，否则返回空指针
	if((!T)||key ==T->data.sname)return T;
	else if(key<T->data.sname)return SearchBST(T->lchild,key);
	else return SearchBST(T->rchild,key);
}

int BSTasl(BSTree t, int d)//总权值，注意调用时d赋值为0
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
	//返回基于二叉排序树查找的ASL
	return BSTasl(T, -1) * 1.0 / count;
} 
