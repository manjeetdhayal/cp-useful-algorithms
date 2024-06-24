#include <bits/stdc++.h> 
using namespace std; 
#define IO_operations freopen("input.txt","r",stdin); freopen("output.txt","w",stdout);
unordered_map<int, vector<int>> adj; 
vector<int> ap; //articulation point true, false 
vector<int> disc; // discovery time of u
vector<int> low; //low node of 'u' 
int time_discovered = 0; 
//Articulation point 

//graph ex: 
// n = no of nodes 
// m = no of edges 
// n = 9, m = 9
//next m lines contains (u, v) which denotes edges btw u and v 
// 9 9
// 1 3
// 1 2
// 2 3
// 2 4
// 4 5
// 4 6
// 2 7
// 7 8
// 8 9
//Condition for Articulation point 
// Now we need to know if some vertex 𝑈
//  is an articulation point. So, for that we will check the following conditions:

// If there is NO way to get to a node 𝑉
//  with strictly smaller discovery time than the discovery time of 𝑈
//  following the DFS traversal, then 𝑈
//  is an articulation point. (it has to be strictly because if it is equal it means that 𝑈
//  is the root of a cycle in the DFS traversal which means that 𝑈
//  is still an articulation point).

// If 𝑈
//  is the root of the DFS tree and it has at least 2 children subgraphs disconnected from each other, then 𝑈
//  is an articulation point.


int dfsAP(int u, int p) {
    int children = 0; // req for condition 2 
    disc[u] = low[u] = ++time_discovered; //add discovery time of node u and low[u] when first discovered
    for(int &to: adj[u]) {
        if(to == p) continue; // we do not go back to the same path again or already discovered
        if(!disc[to]) {
            children++; 
            dfsAP(to, u); 
            if(disc[u] <= low[to]) { // means there is a no node which is ancestor of both u and to coz 
                ap[u] = 1; //u is a articulation point 
            } // if the condition do not hold then low[to] < disc[u] => low[to] is reachablve from some already discovered node
            low[u] = min(low[u], low[to]); // low[v] might be an ancestor of u
        } else {
            //if already discovered 
            low[u] = min(low[u], disc[to]); 
        }
    }
    return children; 
}

int main() {
    #ifndef ONLINE_JUDGE
        IO_operations;
    #endif
    int n, m; cin>>n>>m; 
    time_discovered = 0; 
    for(int i = 0; i < m; i++) {
        int u, v; cin>>u>>v; 
        adj[u].push_back(v); 
        adj[v].push_back(u); 
    }

    ap = low = disc = vector<int> (n + 1, 0); 

    for(int i = 1; i <= n; i++) {
        if(!disc[i]) {
            ap[i] = dfsAP(i, i) > 1; //condition 2 if i is root and atleast 2 subgraphs connected to it 
        }
    }

    cout<<"Articulation points are: "; 
    for(int i = 1; i <= n; i++) if(ap[i]) cout<<i<<" "; 
    return 0; 
}