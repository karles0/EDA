#include <bits/stdc++.h>
using namespace std;

template<typename data_type>
struct Range_tree{
    int n;
    vector<int> xs;                 
    vector<data_type> arr;          
    vector<vector<data_type>> order_by_level;
    vector<vector<int>> ref_left_child, ref_right_child;

    
   void init(vector<pair<int,data_type>> pts){   
    sort(pts.begin(), pts.end());
    n = (int)pts.size();

    xs.resize(n);
    arr.resize(n);
    for(int i = 0; i < n; i++){
        xs[i]  = pts[i].first;
        arr[i] = pts[i].second;
    }

    order_by_level.assign(4*n, {});
    ref_left_child.assign(4*n, {});
    ref_right_child.assign(4*n, {});

    build(0, n-1, 1);
}
    
    void merge(int nodo){
        
        const vector<data_type>& L = order_by_level[2*nodo];
        const vector<data_type>& R = order_by_level[2*nodo +1];
        int leght_left = L.size();
        int leght_right = R.size();
        order_by_level[nodo].resize(leght_left + leght_right);
        ref_right_child[nodo].resize(leght_left+ leght_right + 1);
        ref_left_child[nodo].resize(leght_left + leght_right + 1);
        
        int i = 0; int j = 0 ;int idx_arr = 0;
        
        while( i < leght_left && j< leght_right){
            ref_left_child[nodo][idx_arr] = i;
            ref_right_child[nodo][idx_arr] = j;
            if(L[i] < R[j]){
                order_by_level[nodo][idx_arr] = L[i];
                i++;
                idx_arr++;
            }else{
                order_by_level[nodo][idx_arr] = R[j];
                j++;
                idx_arr++;
            }
        }
        
        while( i < leght_left){
            ref_left_child[nodo][idx_arr] = i;
            ref_right_child[nodo][idx_arr] = j;
            order_by_level[nodo][idx_arr] = L[i];
            i++;
            idx_arr++;
        }
        
        
        while( j < leght_right){
            ref_left_child[nodo][idx_arr] = i;
            ref_right_child[nodo][idx_arr] = j;
            order_by_level[nodo][idx_arr] = R[j];
            j++;
            idx_arr++;
        }
        
        ref_left_child[nodo][idx_arr] = i;
        ref_right_child[nodo][idx_arr] = j;
        
    }
    
    void build(int l, int r, int nodo){
        if( l == r){
            order_by_level[nodo] = {arr[l]};
            return;
        }
        
        int mid = (l+r) /2;
    
        build(l,mid,2*nodo);
        build(mid+1,r, 2*nodo +1);
            
        merge(nodo);
    }
    
    
    data_type Recursivequery(int x1, int x2, int pos1, int pos2, int nd, int low, int high){
        if(xs[high] < x1|| xs[low] > x2) return data_type(0);
        if(xs[low] >= x1&& xs[high] <= x2)return pos2- pos1;
        int mid = (low+high) /2;
        return Recursivequery(x1,x2,ref_left_child[nd][pos1], ref_left_child[nd][pos2] ,2*nd ,low, mid) + Recursivequery(x1,x2, ref_right_child[nd][pos1], ref_right_child[nd][pos2], 2*nd +1 ,mid+1, high);
    }
    
    data_type query(int x1, int x2, int y1, int y2){
        auto lb = std::lower_bound(order_by_level[1].begin(), order_by_level[1].end(), y1); 
        auto up = std::upper_bound(order_by_level[1].begin(), order_by_level[1].end(), y2); 
        return Recursivequery(x1,x2,lb- order_by_level[1].begin(),up- order_by_level[1].begin(),1,0,n-1);
    }
};


int main() {
	ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    long long q;
    cin >> n >>q;

    vector<pair<int,int>> coords;
    
    for(int i = 0; i < n; i++){
        int x, y;
        cin >> x >> y;
        coords.push_back({x,y});
    };
    
    Range_tree<int> rg;
    rg.init(coords);
    
    while(q--){
        int l1, l2,r1,r2;
        cin >> l1 >> l2 >> r1 >> r2;
        
        cout<< rg.query(l1,l2,r1,r2) << "\n";
        
    }
    
    

}
