/// Author: Wang, Yen-Jen
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 20000 + 10;

vector<int> G[MAX_N];
int dfn[MAX_N] , low[MAX_N] , dfs_clock;

bool dfs(int u , int fa) {
    dfn[u] = low[u] = ++dfs_clock;
    for(int v : G[u]) {
        if(v == fa) continue;
        if(!dfn[v]) {
            if(!dfs(v , u)) return 0;
            if(low[v] > dfn[u]) return 0;
            low[u] = min(low[u] , low[v]);
        }
        else low[u] = min(low[u] , dfn[v]);
    }
    return 1;
}

bool vis[MAX_N];
int fa[MAX_N] , dep[MAX_N] , deg[MAX_N];
vector<vector<int> > ans;

void dfs2(int u , int _fa , int _dep) {
	vis[u] = 1;
	fa[u] = _fa;
	dep[u] = _dep;
	for(int v : G[u]) {
        if(!vis[v]) {
            dfs2(v , u , _dep + 1);
            continue;
        }
        if(dep[v] > dep[u]) {
            vector<int> vec;
            vec.push_back(u);
            vec.push_back(v);
            int p = v;
            while(deg[p] == 2) {
                p = fa[p];
                if(!~p) break;
                vec.push_back(p);
            }
            deg[vec.front()]--;
            deg[vec.back()]--;
            ans.push_back(vec);
        }
	}
}

int main() {
    freopen("ear.in" , "r" , stdin);
    freopen("ear.out" , "w" , stdout);
    int n , m;
    scanf("%d%d",&n,&m);
    while(m--) {
        int a , b;
        scanf("%d%d",&a,&b);
        G[a].push_back(b);
        G[b].push_back(a);
    }
    if(!dfs(1 , -1)) {
        puts("-1");
        return 0;
    }
    for(int i = 1; i <= n; i++) deg[i] = (int)G[i].size();
    dfs2(1 , -1 , 0);
    printf("%d\n",(int)ans.size());
    for(vector<int> vec : ans) {
        printf("%d",(int)vec.size() - 1);
        for(int x : vec) printf(" %d",x);
        puts("");
    }
    return 0;
}
