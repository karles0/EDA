#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define vl vector<ll>

struct Node {
    ll data;
    ll l, r;
    Node *left, *right;

    Node(ll data, ll l, ll r, Node* left, Node* right)
        : data(data), l(l), r(r), left(left), right(right) {}
};

struct Versions{
    Node* root;
    int front, back;
    Versions(Node* root, ll front, ll back) : root(root), front(front), back(back) {}
};

auto build = [](auto&& self,Node* rt, vl& a) -> void{
    if(rt->l == rt->r){
        rt->data = a[rt->l  -1];
        return;
    }
        
    int mid = (rt->l + rt-> r)/2;
        
    rt->left = new Node(0LL, rt->l, mid, NULL, NULL);
    rt->right = new Node(0LL, mid+1, rt->r, NULL, NULL);
    self(self,rt->left,a);
    self(self,rt->right,a);
    };
;

auto Recursiveupdate = [](auto&& self, Node* curr, Node* last, ll pos, ll val) -> void{
       if(curr -> l == curr->r){
           curr-> data = val;
           return;
       }
       
       int mid = (curr->l + curr->r)/2;
       
       if(pos <= mid){
           curr-> right = last->right;
           curr-> left = new Node(last->left->data, last->l, mid, NULL, NULL);
           self(self, curr->left, last->left,pos, val);
       }else{
           curr->left = last ->left;
           curr-> right = new Node(last->right->data, mid+1,last->r , NULL, NULL);
           self(self, curr->right, last->right,pos, val);
       }
       
       curr-> data = curr->left->data + curr->right->data;
    
};


auto update = [] (auto&& self,int version,vector<Versions> & vr ,ll pos,ll val) -> Node*{
    Node* root = new Node(0LL, vr[0].root->l, vr[0].root->r, NULL, NULL);
    Recursiveupdate(Recursiveupdate, root,vr[version].root, pos, val);
    return root;
};

auto RecursiveQuery = [] (auto&& self, Node* root, ll x, ll y)-> ll{
    if(root->l > y || root->r < x|| x > y) return 0LL;
    if(root->l >= x && root-> r <= y) return root->data;
    return self(self, root->left,x,y) + self(self, root->right,x,y); 
};

auto Query = [](vector<Versions>& vr ,ll version , ll x, ll y)->ll{
    return RecursiveQuery(RecursiveQuery,vr[version].root, x, y);
};

auto push = [] (vector<Versions>& vr, ll versionn, ll val) ->void{
    ll f = vr[versionn].front;
    ll b = vr[versionn].back;
    Node* node = update(update, versionn, vr,b,val);
    vr.emplace_back(node, f, b+1);
};

auto pop = [] (vector<Versions>& vr, ll versionn) -> ll{
    ll f = vr[versionn].front;
    ll b = vr[versionn].back;
    ll valor = Query(vr, versionn, vr[versionn].front, vr[versionn].front);
    vr.emplace_back(vr[versionn].root, f+1, b);
    return valor;
};

int main() {
	cin.tie(0) -> sync_with_stdio(0);
	int n;
	cin >> n;
	vl a(n,0);

	
	vector<Versions> version_root;
	
	Node* root = new Node(0LL, 1,n,NULL,NULL);
	version_root.emplace_back(root,1,1);
	build(build,version_root[0].root,a);
	int q = n;
	while(q--){
	    int type;
	    cin >> type;
	    
	    if(type == 1){
	        int v,x;
	        cin >> v >> x;
	        push(version_root,v,x);
	    }else{
	        int v;
            cin >> v;
            
	        cout << pop(version_root,v) << "\n";
	    }
	}

	

}
