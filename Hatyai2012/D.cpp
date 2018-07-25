/// Author: Wang, Yen-Jen
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 200000 + 7;

int ans[MAX_N];

int main() {
	int N;
	int kcase = 0;
	while(scanf("%d",&N)) {
		if(!N) break;
		printf("Case %d:\n",++kcase);
		vector<tuple<int, int, int> > vs;
		for(int i = 0; i < N; i++) {
			int x , y;
			scanf("%d%d",&x,&y);
			vs.emplace_back(0, x, y);
		}
		int ax, ay, bx, by, Q;
		scanf("%d%d%d%d%d",&ax,&ay,&bx,&by,&Q);
		for(tuple<int, int, int> &t : vs) {
			int x = get<1>(t);
			int y = get<2>(t);
			get<0>(t) = (x - ax) * (x - ax) + (y - ay) * (y - ay);
		}
		sort(vs.begin(), vs.end());
		vector<tuple<int, int, int> > qs;
		for(int i = 0; i < Q; i++) {
			int r1, r2;
			scanf("%d%d",&r1,&r2);
			qs.emplace_back(r1 * r1, r2 * r2, i);
			ans[i] = N;
		}
		sort(qs.begin(), qs.end());
		for(int i = 0, j = 0, cc = 0; i < Q; i++) {
			while(j < N && get<0>(vs[j]) <= get<0>(qs[i])) {
				cc++;
				j++;
			}
			ans[get<2>(qs[i])] -= cc;
		}
		for(tuple<int, int, int> &t : vs) {
			int x = get<1>(t);
			int y = get<2>(t);
			get<0>(t) = (x - bx) * (x - bx) + (y - by) * (y - by);
		}
		for(tuple<int, int, int> &t : qs) {
			swap(get<0>(t), get<1>(t));
		}
		sort(vs.begin(), vs.end());
		sort(qs.begin(), qs.end());
		for(int i = 0, j = 0, cc = 0; i < Q; i++) {
			while(j < N && get<0>(vs[j]) <= get<0>(qs[i])) {
				cc++;
				j++;
			}
			ans[get<2>(qs[i])] -= cc;
		}
		for(int i = 0; i < Q; i++) {
			if(ans[i] < 0) ans[i] = 0;
			printf("%d\n",ans[i]);
		}
	}
	return 0;
}
