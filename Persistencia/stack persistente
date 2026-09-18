#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define vl vector<ll>

struct Node{
    ll data;
    Node* next;

    Node(ll data, Node* next): data(data), next(next) {}
};

auto push = [] (vector<Node*>& vr,ll versionn, ll val) -> void{
    vr.emplace_back(new Node(val,vr[versionn]));
};

auto pop = [] (vector<Node*>& vr,ll versionn) -> void{
    vr.emplace_back(vr[versionn]->next);
};

auto top = [] (vector<Node*>& vr, ll versionn) ->ll{
    return vr[versionn] == NULL ? 0LL : vr[versionn] -> data;
};

int main() {
	cin.tie(0) -> sync_with_stdio(0);
	int q;
	cin >> q;
	
	vector<Node*> version_root;
	
	
	version_root.emplace_back(nullptr);
	ll acum = 0;
	
	for(int i =  1; i <= q;i++){
	    int t, m;
	    cin >> t >> m;
	    
	    if(m == 0){
	        pop(version_root,t);
	    }else{
	        push(version_root, t, top(version_root,t) + m);
	    }
	    
	    acum += top(version_root,i);
	}
	


	
    cout<< acum << "\n";
}
