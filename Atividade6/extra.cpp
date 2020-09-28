#include <cstdio>
#include <vector>
#include <cstring>
#include <algorithm>
#define MAXN 50010
using namespace std;

int nodes;
int edges;
int size;
int grau[MAXN];
int heap[MAXN];
bool ciclo;
bool marc[MAXN];
vector<int> resp;
vector<int> myv[MAXN];

int left(int i){
    return 2*i;
}
int right(int i){
    return 2*i+1;
}
int parent(int i){
    return i/2;
}

void heapify_down(int v){

    int l = left(v);
    int r = right(v);

    int maior;
    if( l <= size  && heap[l] < heap[v]) maior = l;
    else maior = v;

    if( r <= size && heap[r] < heap[maior]) maior = r;

    if( maior != v ){
        int aux;
        aux = heap[maior];
        heap[maior] = heap[v];
        heap[v] = aux;
        heapify_down(maior);
    }

}

void heapify_up(int v){

    if(v > 1){

        int pai = parent(v);
        if(heap[v] < heap[pai]){

            int aux = heap[v];
            heap[v] = heap[pai];
            heap[pai] = aux;

            heapify_up(pai);

        }

    }

}

void faz_tudo(){

    //printf("%d\n",heap[1]-1);
    resp.push_back(heap[1]-1);
    int cara = heap[1];

    int aux;
    aux = heap[1];
    heap[1] = heap[size];
    heap[size] = aux;
    size--;
    heapify_down(1);

    for(int i = 0;i<myv[cara].size();i++){
        grau[myv[cara][i]]--;
        if(!grau[myv[cara][i]]){
            heap[++size] = myv[cara][i];
            heapify_up(size);
        }
    }

    if(size >= 1) faz_tudo();

}

void dfs(int x){
    marc[x] = 1;
    //printf("{%d}\n",x);
    for(int i = 0;i<myv[x].size();i++){
        //printf("%d\n",marc[myv[x][i]]);
        if( marc[myv[x][i]] ) ciclo = 1;
        else dfs(myv[x][i]);
    }
}

int main(){

    scanf("%d %d",&nodes,&edges);

    memset(grau,0,sizeof grau);

    for(int i = 1;i<=edges;i++){
        int a,b;
        scanf("%d %d",&a,&b);
        a++;
        b++;

        myv[a].push_back(b);
        grau[b]++;

    }

    int cont = 0;

    size = 0;
    for(int i = 1;i<=nodes;i++) if(!grau[i]) heap[++size] = i;

    if(size > 0) faz_tudo();

    if(resp.size() == nodes) for(int i = 0;i<resp.size();i++) printf("%d\n",resp[i]);
    else printf("*\n");

    return 0;
}
