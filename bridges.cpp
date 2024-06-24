#include <bits/stdc++.h> 
using namespace std; 
#define IO_operations freopen("input.txt","r",stdin); freopen("output.txt","w",stdout);
//Bridges 

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

//Condition for Articulation point will be used same 
// Now we need to know if some edge (u, v)
//  is an Bridge. So, for that we will check the following conditions:

// If there is NO way to get to a node 𝑉
//  with strictly smaller discovery time than the discovery time of 𝑈
//  following the DFS traversal, then 𝑈
//  is an articulation point. (it has to be strictly because if it is equal it means that 𝑈
//  is the root of a cycle in the DFS traversal which means that 𝑈
//  is still an articulation point).


// Difference is disc[u] < low[to] instead of disc[u] <= low[to] because if disc[u] == low[to] => there is another path 
// from to to U. so it can't be a bridge. 

unordered_map<int, vector<int>> adj; 
vector<vector<int>> br; //Bridges
vector<int> disc; // discovery time of u
vector<int> low; //low node of 'u' 
int time_discovered = 0; 

void dfsBR(int u, int p) {
    disc[u] = low[u] = ++time_discovered; //mark when first discovered 

    for(int &to: adj[u] ) {
        if(to == p) continue; 
        if(!disc[to]) {
            dfsBR(to,u); 
            if(disc[u] < low[to]) {
                //this implies that there is no way to reach 'to' except crossing 'u' 
                br.push_back({u, to}); 
            }

            //update low in case there is some other ancestor which is discovered earlier than 'u' and connected to it. 
            low[u] = min(low[u], low[to]); 
        } else {
            //already discovered
            low[u] = min(low[u], disc[to]); //min of discover time of 'u' and 'to' 
        }
    }
}

//to find the no of bridges 
void BR(int n) {
    low = disc = vector<int> (n + 1, 0); 
    for(int i = 1; i <= n; i++) {
        if(!disc[i]) dfsBR(i, i);
    }
    cout<<"Bridge edges are: \n"; 
    for(auto it: br) cout<<it[0]<<" "<<it[1]<<"\n"; 
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
    BR(n); 
    return 0; 
}