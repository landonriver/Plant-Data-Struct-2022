#include<bits/stdc++.h>
#define MVNum 34                           //��󶥵���
#define ERROR 0
#define MAXINT 10000
using namespace std;

typedef struct
{
    string vexs[MVNum];               	//�����
    int arcs[MVNum][MVNum];            	//�ڽӾ���
    int vexnum;                        	//ͼ���ܶ�����
    int arcnum;                        	//ͼ���ܱ���
}Graph;
int LocateVex(Graph G,string u)
{//�����򷵻�u�ڶ�����е��±꣬���򷵻�ERROR
	for(int i = 0 ; i < G.vexnum; i ++){
		if(G.vexs[i] == u)return i;
	}return ERROR;
}
string OrigialVex(Graph G,int u)
{//�����򷵻ض�������±�Ϊu��Ԫ��
	if (u >= 0 && u <= G.vexnum) {
		return G.vexs[u];
	}
}
void InitGraph(Graph &G){
	G.vexnum=34;		//34��ʡ��������λ
	string place[]={"����","�Ϻ�","���","����","���ɹ�","����","����","����","�½�","���","����","�ӱ�","ɽ��","����","����","������","����","�㽭","����","����","����","ɽ��","����","����","����","�㶫","����","�Ĵ�","����","����","����","����","�ຣ","̨��"};
    for(int i=0;i<G.vexnum;i++)
		G.vexs[i]=place[i];
}

void CreateGraph(Graph &G,string filename)
{//�����ڽӾ����ʾ������distance.txt����������ͼG
 //��distance.txtʱҪʹ��filename����

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
{//����Dijkstra�㷨��v1��v2�����·��������·������
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
{//ʹ��filename��ȡplant.txt�ļ�
 //���ݴ����ֲ�������õ�ֲ��ֲ���distribution�������طֲ�������
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
