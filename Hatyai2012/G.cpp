/// Author: Wang, Yen-Jen
#pragma GCC optimize "-O3"
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 100 + 7;
const int MAX_M = 1000 + 7;
const int INF = 0x3f3f3f3f;

int N;
vector<int> vs;
int A[MAX_N][MAX_N];
int B[MAX_M][MAX_N];
int C[MAX_N][MAX_N];
int dp[MAX_M][MAX_N];

void print_path(int lev , int u) {
	if(lev == 1) {
		cout << u << '\n';
		return;
	}
	else {
		int t = 0;
		if(lev == (int)vs.size() + 1) t = 0;
		else t = B[vs[lev - 1]][u];
		if(lev - 1 > 0) {
			for(int i = 1; i < N; i++) {
				if(dp[lev - 1][i] + C[u][i] + t == dp[lev][u]) {
					if(lev != (int)vs.size() + 1) cout << u << ' ';
					print_path(lev - 1 , i);
					break;
				}
			}
		}
		else {
			cout << u << ' ';
			print_path(lev - 1 , 0);
		}
	}
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	int M;
	cin >> N >> M;
	for(int i = 0; i < N; i++) {
		for(int j = 0; j < N; j++) {
			cin >> A[j][i];
			C[i][j] = A[j][i];
		}
	}
	for(int i = 0; i < N; i++) {
		for(int j = 0; j < M; j++) cin >> B[j][i];
	}
	cin.ignore();
	cin.ignore();
	string str;
	while(getline(cin , str)) {
		if(str == "") break;
		stringstream ss(str);
		int num;
		vs.clear();
		while(ss >> num) vs.push_back(num);
		reverse(vs.begin() , vs.end());
		int n = (int)vs.size();
		memset(dp , 0x3f , sizeof(dp));
		dp[0][0] = 0;
		for(int i = 0; i <= n; i++) {
			int ii = vs[i];
			for(int j = 0; j < N; j++) {
				if(dp[i][j] == INF) continue;
				int st = 1;
				int ed = 0;
				if(i + 1 <= n) ed = N - 1;
				else st = 0;
				for(int k = st; k <= ed; k++) {
					int dpt = dp[i][j] + A[j][k] + (i < n ? B[ii][k] : 0);
					if(dp[i + 1][k] > dpt) dp[i + 1][k] = dpt;
				}
			}
		}
		cout << dp[n + 1][0] << '\n';
		print_path(n + 1 , 0);
	}
	return 0;
}
