#include <bits/stdc++.h>
using namespace std;

#define pb push_back
#define ll long long
#define ld long double
#define mp make_pair
#define nl "\n"

#define FAST_IO ios_base::sync_with_stdio(0); cin.tie(0);

struct Edge{
    int u,v;
    ll w;
    Edge(int u,int v,ll w){
        this->u=u;
        this->v=v;
        this->w=w;
    }

    bool operator<(const Edge& b){
        return this->w<b.w;
    }
};


void prim(vector<vector<pair<ll,int>>>& adj,int N,int root){
    vector<bool>visited(N);
    vector<Edge>mst_edges;
    priority_queue<pair<ll,pair<int,int>>,vector<pair<ll,pair<int,int>>>,greater<pair<ll,pair<int,int>>>>pq;
    ll total_weight=0;
    pq.push({0,{root,-1}});
    while(!pq.empty()){
        ll w=pq.top().first;
        int u=pq.top().second.first;
        int parent=pq.top().second.second;
        pq.pop();

        if(visited[u]) continue;

        total_weight+=w;
        visited[u]=true;

        if(parent!=-1){
            mst_edges.push_back({parent,u,w});
        }

        for(auto& neighbour: adj[u]){
            int v=neighbour.second;
            ll w2=neighbour.first;
            if(!visited[v]){
                pq.push({w2,{v,u}});
            }
        }
    }

    if(mst_edges.size()==N-1){
        cout<<"Total weight "<<total_weight<<nl;
        cout<<"Root node "<<root<<nl;
        for(auto& e:mst_edges){
            cout<<e.u<<" "<<e.v<<nl;
        }
    }
    else{
        cout<<"No MST Possible"<<nl;
    }
}


class DSU{
    int* parent;
    int *sz;
public:
    DSU(int n){
        parent=new int[n];
        sz=new int[n];
        for(int i=0;i<n;i++){
            parent[i]=i;
            sz[i]=1;
        }
    }

    ~DSU(){
        delete[] parent;
        delete[] sz;
    }

    int find(int i){
        if(i==parent[i]) return i;
        return parent[i]=find(parent[i]);
    }

    bool unionSet(int i,int j){
        int root_i=find(i);
        int root_j=find(j);
        if(root_i!=root_j){
            if(sz[root_i]<sz[root_j]){
                swap(root_i,root_j);
            }
            parent[root_j]=root_i;
            sz[root_i]+=sz[root_j];
            return true;
        }
        return false;
    }
};

void kruskal(vector<Edge>& edges,int N){
    sort(edges.begin(),edges.end());
    DSU dsu(N);
    vector<Edge> mst_list;
    ll total_weight=0;
    for(auto& e:edges){
        if(dsu.unionSet(e.u,e.v)){
            total_weight+=e.w;
            mst_list.push_back(e);
        }
    }

    if(mst_list.size()==N-1){
        cout<<"Total weight "<<total_weight<<nl;
        for(auto& e:mst_list){
            cout<<e.u<<" "<<e.v<<nl;
        }
    }
    else{
        cout<<"No MST Possible"<<nl;
    }
}

int main() {
    FAST_IO;
    int N,M;
    cin>>N>>M;
    vector<vector<pair<ll,int>>>adj(N);
    vector<Edge>edges;
    for(int i=0;i<M;i++){
        int u,v;
        ll w;
        cin>>u>>v>>w;
        adj[u].push_back({w,v});
        adj[v].push_back({w,u});
        edges.push_back({u,v,w});
    }
    int root;
    cin>>root;
    cout<<"Prim :"<<nl;
    prim(adj,N,root);
    cout<<"Kruskal :"<<nl;
    kruskal(edges,N);
    return 0;
}