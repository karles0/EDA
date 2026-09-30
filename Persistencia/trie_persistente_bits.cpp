#include <bits/stdc++.h>
#define ll long long
using namespace std;
struct version{
    int idx;

    version(int idx) : idx(idx) {};
};

struct node {
    int child[2];
    int val;

    node() {
    for(int i = 0; i < 2; i++)
        child[i] = 0;

        val = 0;
    }
};



signed main(){
    cin.tie(0) -> sync_with_stdio(0);
    int t;
    cin >> t;

    while(t--){
        int n, q;
        cin >> n >> q;
        vector<ll> a(n);
        for(int i = 0; i < n; i++) cin >> a[i];

        vector<node> trie;

        trie.reserve(1+ n * 18);

        trie.emplace_back();

        auto insert = [&](auto&& insert, int last, int val, int b, int delta) -> int {
            node tmp = trie[last];
            trie.emplace_back(tmp);
            int cur = trie.size() - 1;
            trie[cur].val += delta;
            if (b < 0) return cur;
            int c = (val >> b) & 1;
            int nxt = insert(insert, trie[last].child[c], val, b - 1, delta);
            trie[cur].child[c] = nxt;
            return cur;
        };


        auto max_xor = [&](int R, int L, int a) -> ll {
            ll ans = 0;
            for (int i = 17 - 1; i >= 0; i--) {
                int c = (a >> i) & 1;
                int d = c ^ 1;
                int cnt = trie[trie[R].child[d]].val - trie[trie[L].child[d]].val;
                if (cnt > 0) {
                    ans |= (1LL << i);
                    R = trie[R].child[d];
                    L = trie[L].child[d];
                } else {
                    R = trie[R].child[c];
                    L = trie[L].child[c];
                }
            }
            return ans;
        };


        vector<version> root;
        root.emplace_back(0);

        for(int i = 0; i < n;i++){
            root.emplace_back(insert(insert, root.back().idx, a[i], 17-1, 1));
        }

        for(int i = 0; i < q; i++){
            int x, l, r;
            cin >> x >> l >> r;
            cout << max_xor(root[r].idx, root[l-1].idx, x) << '\n';
        }
    }
}
