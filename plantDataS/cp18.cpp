#include<bits/stdc++.h>
#define MVNum 34                           //最大顶点数
#define ERROR 0
#define MAXINT 10000

using namespace std;

typedef struct
{
    string vexs[MVNum];               	//顶点表
    int arcs[MVNum][MVNum];            	//邻接矩阵
    int vexnum;                        	//图的总顶点数
    int arcnum;                        	//图的总边数
}Graph;

struct tonglu{
	string placename[100];
	int length;
}; 
tonglu tot[15];
int numoftot = 0;

int LocateVex(Graph G,string u)
{//存在则返回u在顶点表中的下标，否则返回ERROR
	for(int i = 0 ; i < G.vexnum; i ++){
		if(G.vexs[i] == u)return i;
	}return ERROR;
}
string OrigialVex(Graph G,int u)
{//存在则返回顶点表中下标为u的元素
	if (u >= 0 && u <= G.vexnum) {
		return G.vexs[u];
	}
}
void InitGraph(Graph &G){
	G.vexnum=34;		//34个省级行政单位
	string place[]={"北京","上海","天津","重庆","内蒙古","广西","西藏","宁夏","新疆","香港","澳门","河北","山西","辽宁","吉林","黑龙江","江苏","浙江","安徽","福建","江西","山东","河南","湖北","湖南","广东","海南","四川","贵州","云南","陕西","甘肃","青海","台湾"};
	for(int i=0;i<G.vexnum;i++){
		G.vexs[i]=place[i];
	}
}
void CreateGraph(Graph &G, string filename)
{//采用邻接矩阵表示法，读distance.txt，创建有向图G
 //读distance.txt时要调用filename参数
	memset(G.arcs, MAXINT, sizeof(G.arcs));
	ifstream infile;
	infile.open(filename.c_str());
	string temline;
	while (getline(infile, temline)) {
		string startp, endp;
		stringstream ss(temline);
		string s;
		int flag = 0;
		while (getline(ss, s, '#')) {
			if (flag == 0) startp = s;
			if (flag == 1) endp = s;
			if (flag == 2) {
				G.arcs[LocateVex(G, startp)][LocateVex(G, endp)] = stoi(s);
				G.arcs[LocateVex(G, endp)][LocateVex(G, startp)] = stoi(s);
			}
			flag++;
		}
	}
	for(int i = 0; i < 34; i++) {
		G.arcs[i][i] = 0;
	}
}


void DFS(Graph G,int &i,int &length,int n,int &nownumofp,string s[],string p2){
	for(int j = 0; j < G.vexnum; j++){
		int flag=0;
		if(G.arcs[i][j] == MAXINT) continue;
		string tempp=OrigialVex(G,j);
		for(int i = 0; i < nownumofp; i++){
			if(s[i]==tempp){
				flag=1;
				break;
			} 
			
		}
		if(flag) continue;

		length += G.arcs[i][j];
		if(length>n){
			length -= G.arcs[i][j];
			continue;
		}
		
		if(tempp == p2){
			tot[numoftot].length = length;
			length-=G.arcs[i][j];
			s[nownumofp] = p2;
			nownumofp = 0;
			while(s[nownumofp] != ""){
				tot[numoftot].placename[nownumofp]=s[nownumofp];
				nownumofp++;
			}
			s[nownumofp--] = "";
			numoftot++;
			continue;
		}
		s[nownumofp++] = tempp;
		DFS(G,j,length,n,nownumofp,s,p2);
	}
	
	if(numoftot !=0 && length == 0) return;
	nownumofp--;
	int a = LocateVex(G,s[nownumofp-1]);
	int b = LocateVex(G,s[nownumofp]);
	length -= G.arcs[a][b];
	s[nownumofp]="";
}

void FindWay(Graph G,string p1,string p2,int n)
{//找到p1到p2所有长度小于n的路径并按路程从小到大输出
 //若需用到递归函数或全局变量等请自行定义并合理调用
 	int nownumofp = 1;
 	int length = 0;
 	string s[100];
 	s[0] = p1;
    for(int i=1;i<G.vexnum;i++){
    	s[i]="";
	}
	
    int v0=LocateVex(G,p1);
	DFS(G,v0,length,n,nownumofp,s,p2);
	
	for(int i = 0 ; i < numoftot-1; i++){
		tonglu t;
		for(int j = 0; j < numoftot-i-1; j++){
			if(tot[j].length > tot[j+1].length){
				t = tot[j];
				tot[j] = tot[j+1];
				tot[j+1] = t;
			}
		}
	}
	
	
	for(int i = 0; i < numoftot; i++){
		int j = 0;
		while(tot[i].placename[j] != ""){
			
			cout<<tot[i].placename[j++];
			
			if(tot[i].placename[j] != ""){
				cout<<" ";
			}
		}
		
		cout<<endl;
	}
}
