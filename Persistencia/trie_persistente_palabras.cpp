#include <bits/stdc++.h>

using namespace std;
struct version{
    int idx;

    version(int idx) : idx(idx) {};
};

struct node {
        int child[26];
        int val;

        node() {
        for(int i = 0; i < 26; i++)
                child[i] = 0;

                val = 0;
            }
};



signed main(){
    cin.tie(0) -> sync_with_stdio(0);

        int n,q;
        cin >> n >> q;

        vector<node> trie;

        trie.reserve(2e6);

        trie.emplace_back();

        vector<string> s(n);

        for(int i = 0; i < n ;i++) cin >> s[i];

        auto insert = [&](auto&& insert, int old,const string&  s, int pos) ->int{

            int cur = trie.size();
                trie.emplace_back(trie[old]) ;
                trie[cur].val++;
                if(pos == s.size()){
                    return cur;
                }
                
                int c = s[pos] - 'a';

                trie[cur].child[c] = insert(insert, trie[old].child[c], s, pos + 1);
                return cur;
            };

            auto query = [&](auto&& query, int rt, const string& s  )->int{
                int cur = rt;

                for(char ch: s){
                    int c = ch-'a';
                    if(trie[cur].child[c] == 0) return 0;
                    cur = trie[cur].child[c];


                }

                return trie[cur].val;   
            };

            vector<version> root;
            root.emplace_back(0);

            for(int  i = 0; i < n;i++){
                root.emplace_back(insert(insert, root.back().idx,s[i],0));
            }

            while(q--){
                int l,r;
                string t;

                cin >> l >> r >> t;

                cout << query(query, root[r].idx,t) - query(query, root[l-1].idx,t) << '\n';

            }

        }
