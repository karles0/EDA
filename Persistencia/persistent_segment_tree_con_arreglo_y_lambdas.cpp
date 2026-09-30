#include <bits/stdc++.h>
#define ll long long
using namespace std;

struct ver {
    int idx;
    ver(int idx) : idx(idx) {}
};

struct node {
    ll val; int l, r;
    node(ll val, int l =-1 , int r  = -1) : val(val), l(l), r(r) {}
};

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n;
    cin >> n;
    vector<ll> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];

    vector<node> seg;
    seg.reserve(2 * n + 20 * 200000); //reservar la suficiente memoria (dependiendo del ejercicio puede que necesite mas)  


    //construccion con intervalo cerrado, es decir [l,r] y no [l,r)
    auto build = [&](auto&& build, int l, int r) -> int {
        if (l == r) {
            //porque esta 1-indexed
            seg.emplace_back(a[l - 1]);         
            return seg.size() - 1;
        }
        int mid = (l + r) / 2;
        int node_l = build(build, l, mid);
        int node_r = build(build, mid + 1, r);
        seg.emplace_back(seg[node_l].val + seg[node_r].val, node_l, node_r);
        return seg.size() - 1;
    };

    auto update = [&](auto&& update, int l, int r, int v, int pos, ll val) -> int {
        if (l == r) {
            seg.emplace_back(val);
            return seg.size() - 1;
        }
        int mid = (l + r) / 2;
        int L = seg[v].l, R = seg[v].r; //los nodos de las diferentes versiones se guardan a lo largo de seg
        if (pos <= mid) {
            L = update(update, l, mid, L, pos, val);
        }
        else{
            R = update(update, mid + 1, r, R, pos, val);
        }            
        seg.emplace_back(seg[L].val + seg[R].val, L, R);
        return seg.size() - 1;
    };

    auto query = [&](auto&& query, int l, int r, int v, int ql, int qr) -> ll {
        if (qr < l || r < ql) return 0;
        if (ql <= l && r <= qr) return seg[v].val;
        int mid = (l + r) / 2;
        return query(query, l, mid, seg[v].l, ql, qr)
             + query(query, mid + 1, r, seg[v].r, ql, qr);
    };

    vector<ver> roots{build(build, 1, n)};

    int q;
    cin >> q;
    while (q--) {
        string s;
        cin >> s;
        if (s == "create") {
            int i, j; ll x;
            cin >> i >> j >> x;
            roots.emplace_back(update(update, 1, n, roots[i - 1].idx, j, x));
        } else {
            int i, j;
            cin >> i >> j;
            cout << query(query, 1, n, roots[i -1].idx, j, j) << '\n';
        }
    }
}
