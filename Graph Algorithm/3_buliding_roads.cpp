#include<bits/stdc++.h>
using namespace std;
 
void dfs(int node, vector<int> adj[], vector<bool>& vis) {
    vis[node] = true;
    for (int i : adj[node]) {
        if (!vis[i]) dfs(i, adj, vis);
    }
}
 
int main() {
    int n, m;
    cin >> n >> m;
    vector<int> adj[n+1]; 
 
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
 
    vector<bool> vis(n, false); 
    vector<int> r; 
 
    for (int i = 1; i <= n; i++) {
        if (vis[i]==false){
            dfs(i, adj, vis);
            r.push_back(i);
        } 
    }
    cout<<r.size()-1<<endl;
 
    for(int i=0;i<r.size()-1;i++){
        cout<<r[i]<<" "<<r[i+1]<<endl;
    }
}
