#include<bits/stdc++.h>
using namespace std;

class SgTree{
    public: 
    vector<int> seg;

    SgTree(int n){
        seg.resize(4*n+1);
    }
    void build(int ind, int low, int high, int arr[]){
        if(low == high){
            seg[ind] = arr[low];
            return;
        }
        int mid = (low + high) >> 1;
        build(2*ind+1, low, mid, arr);
        build(2*ind+2, mid+1, high, arr);
        seg[ind] = seg[2*ind+1] + seg[2*ind+2];
    }
    int query(int ind, int low, int high, int l, int r){
        // No Overlap
        if(l > high || r < low) return 0;

        // Complete Overlap
        if(l <= low && r >= high) return seg[ind];

        int mid = (low + high) >> 1;
        return query(2*ind+1, low, mid, l, r) + query(2*ind+2, mid+1, high, l, r);
    }

    void update(int ind, int low, int high, int i, int val){
        if(low == high){
            seg[ind] = val;
            return;
        }
        int mid = (low + high) >> 1;
        if(i <= mid){
            update(2*ind+1, low, mid, i, val);
        }
        else{
            update(2*ind+2, mid+1, high, i, val);
        }
        seg[ind] = seg[2*ind+1] + seg[2*ind+2];
    }

};
int main()
{
    int n;
    cin>>n;

    int arr[n];
    for(int i = 0; i < n; i++) cin>>arr[i];

    SgTree s1(n);
    s1.build(0, 0, n-1, arr);

    int q;
    cin>>q;

    while(q--){
        int type;
        cin>>type;
        if(type == 1){
            int l, r;
            cin>>l>>r;
            l--, r--;
            cout<<s1.query(0, 0, n-1, l, r)<<endl;
        }
        else{
            int i, val;
            cin>>i>>val;
            i--;
            s1.update(0, 0, n-1, i, val);
        }
    }
    return 0;
}