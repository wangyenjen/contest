/// Author: Wang, Yen-Jen
#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 100 + 10;
const int MAX_K = 200 + 10;

struct Client {
    vector<int> in_cnt;
    int chunk_cnt;
    vector<bool> has_chunk;

    Client() : chunk_cnt(0) {
      in_cnt.clear();
      has_chunk.clear();
    }
};

int ans[MAX_N];
vector<Client> clients;
vector<int> has_chunk_id[MAX_K];
vector<pair<int, int> > request_list[MAX_N];

int main() {
    freopen("epig.in" , "r" , stdin);
    freopen("epig.out" , "w" , stdout);
    int N , K;
    scanf("%d%d",&N,&K);
    vector<int> remain_id;
    for (int i = 0; i < N; i++) {
        Client c;
        c.in_cnt = vector<int>(N , 0);
        if (!i) {
            c.chunk_cnt = K;
            c.has_chunk = vector<bool>(K , 1);
        }
        else {
            c.chunk_cnt = 0;
            c.has_chunk = vector<bool>(K , 0);
            remain_id.push_back(i);
        }
        clients.push_back(c);
        request_list[i].clear();
    }
    for (int i = 0; i < K; i++) {
        has_chunk_id[i].clear();
        has_chunk_id[i].push_back(0);
    }
    ans[0] = 0;
    int round_cnt = 0;
    while (!remain_id.empty()) {
        round_cnt++;
        for (int id : remain_id) {
            int ch_chunk_id = -1;
            for (int i = 0; i < K; i++) {
                if (!clients[id].has_chunk[i]) {
                    if (ch_chunk_id == -1 || (int)has_chunk_id[ch_chunk_id].size() > (int)has_chunk_id[i].size()) {
                        ch_chunk_id = i;
                    }
                }
            }
            int ch_request_id = -1;
            for (int i : has_chunk_id[ch_chunk_id]) {
                if (ch_request_id == -1 || clients[ch_request_id].chunk_cnt > clients[i].chunk_cnt) {
                    ch_request_id = i;
                }
                else if (clients[ch_request_id].chunk_cnt == clients[i].chunk_cnt) {
                    if (ch_request_id > i) ch_request_id = i;
                }
            }
            request_list[ch_request_id].push_back(make_pair(id , ch_chunk_id));
        }
        vector<pair<pair<int, int>, int> > receive_list;
        for (int i = 0; i < N; i++) {
            sort(request_list[i].begin() , request_list[i].end());
            pair<int, int> ch = make_pair(-1 , -1);
            for (pair<int, int> p : request_list[i]) {
                if (ch.first == -1) ch = p;
                else if (clients[i].in_cnt[ch.first] < clients[i].in_cnt[p.first]) ch = p;
                else if (clients[i].in_cnt[ch.first] == clients[i].in_cnt[p.first]) {
                    if (clients[ch.first].chunk_cnt > clients[p.first].chunk_cnt) ch = p;
                }
            }
            request_list[i].clear();
            if (ch.first != -1) receive_list.push_back(make_pair(ch , i));
        }
        for(pair<pair<int, int>, int> p : receive_list) {
            int id = p.first.first;
            int chunk = p.first.second;
            int provide_id = p.second;
            clients[id].chunk_cnt++;
            clients[id].has_chunk[chunk] = 1;
            clients[id].in_cnt[provide_id]++;
            has_chunk_id[chunk].push_back(id);
        }
        vector<int> new_remain_id;
        for (int id : remain_id) {
            if (clients[id].chunk_cnt < K) new_remain_id.push_back(id);
            else ans[id] = round_cnt;
        }
        remain_id = new_remain_id;
    }
    for (int i = 1; i < N; i++) printf("%d%c",ans[i]," \n"[i == N - 1]);
    return 0;
}
