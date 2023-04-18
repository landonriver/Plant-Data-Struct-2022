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
    for(int i=0;i<G.vexnum;i++)
		G.vexs[i]=place[i];
}

void CreateGraph(Graph &G,string filename)
{//采用邻接矩阵表示法，读distance.txt，创建有向图G
 //读distance.txt时要使用filename参数

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

int Dijkstra(Graph G,string v1,string v2)
{//利用Dijkstra算法求v1到v2的最短路径并返回路径长度
    int v0 = LocateVex(G,v1);
    int ve = LocateVex(G,v2);
    int n = G.vexnum;
    int S[34],D[34],Path[34];
    for(int v = 0 ; v < n ; ++v){
		S[v] = false;
		D[v] = G.arcs[v0][v];
		if(D[v]<MAXINT) Path[v] = v0;
		else Path[v] = -1;
	}
	S[v0] = true;
	D[v0] = 0;
	for(int i = 1 ; i < n; i++){
		int min = MAXINT;
		int v;
		for(int w = 0; w < n ; w++){
			if(!S[w]&&D[w]<min){
				v = w;
				min = D[w];
			}
		}
		S[v] = true;
		for(int w = 0; w < n ;w++){
			if(!S[w]&&(D[v]+G.arcs[v][w]<D[w])){
				D[w] = D[v]+G.arcs[v][w];
				Path[w] = v;
			}
		}
	}
	return D[ve];


}


int GetDistribution(string name,string distribution[],string filename)
{//使用filename读取plant.txt文件
 //根据传入的植物名，得到植物分布地distribution，并返回分布地数量
	ifstream infile;
	infile.open(filename.c_str());
	string temline;
	while(getline(infile,temline)){
		stringstream ss(temline);
		string s;
		string temname,stemname;
		int flag = 0;
		while(getline(ss,s,'#')){
			if(flag == 0) temname = s;
			if(flag == 1) stemname =s;
			if(flag == 2){
				if(temname == name){
					stringstream ssplace(s);
					string place;
					int placenum = 0;
					while(getline(ssplace,place,'@')){
						distribution[placenum] = place;
//						cout<<distribution[placenum]<<endl;
						placenum++;					

				}
			return placenum;	
			}
		}
		flag++;
	}
}
return 0;

}
