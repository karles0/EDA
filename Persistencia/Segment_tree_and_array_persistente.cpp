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


auto update = [] (auto&& self,int version,vector<Node*> & vr ,ll pos,ll val) -> void{
    Node* root = new Node(0LL, vr[0]->l, vr[0]->r, NULL, NULL);
    vr.emplace_back(root);
    return Recursiveupdate(Recursiveupdate, root,vr[version], pos, val);
};

auto RecursiveQuery = [] (auto&& self, Node* root, ll x, ll y)-> ll{
    if(root->l > y || root->r < x|| x > y) return 0LL;
    if(root->l >= x && root-> r <= y) return root->data;
    return self(self, root->left,x,y) + self(self, root->right,x,y); 
};

auto Query = [](vector<Node*> vr ,ll version , ll x, ll y)->ll{
    return RecursiveQuery(RecursiveQuery,vr[version], x, y);
};

int main() {
	cin.tie(0) -> sync_with_stdio(0);
	int n;
	cin >> n;
	vl a(n);
	
	for(int i = 0; i < n; i++){
	    cin >> a[i];
	}
	
	vector<Node*> version_root;
	
	Node* root = new Node(0LL, 1,n,NULL,NULL);
	version_root.emplace_back(root);
	build(build,version_root[0],a);
	
	
	int q;
	cin >> q;
	
	while(q--){
	    string s;
	    cin >>s;
	    if(s == "create"){
	        int i,j,x;
	        cin >> i>> j>> x;
	        update(update,i-1,version_root,j,x);
	    }else{
	        int i,j;
	        cin >>i>>j;
	        cout<< Query(version_root, i-1,j,j)<< "\n";
	    }
	}
	

}
