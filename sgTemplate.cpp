#include <bits/stdc++.h>
using namespace std;

class SGTree
{
    vector<int> seg;

public:
    SGTree(int n)
    {
        seg.resize(4 * n + 1);
    }
    void build(int ind, int low, int high, vector<int> &arr)
    {
        if (low == high)
        {
            seg[ind] = arr[low];
            return;
        }
        int mid = (low + high) / 2;
        build(2 * ind + 1, low, mid, arr);
        build(2 * ind + 2, mid + 1, high, arr);

        seg[ind] = min(seg[2 * ind + 1], seg[2 * ind + 2]);
    }

    int query(int ind, int low, int high, int l, int r)
    {
        // no Overlap
        if (r < low || l > high)
        {
            return INT_MAX;
        }
        // Complete Overlap
        if (low >= l && high <= r)
        {
            return seg[ind];
        }
        // partial Overlap
        int mid = (low + high) / 2;
        return min(query(2 * ind + 1, low, mid, l, r), query(2 * ind + 2, mid + 1, high, l, r));
    }

    void update(int ind, int low, int high, int i, int val)
    {
        if (low == high)
        {
            seg[ind] = val;
            return;
        }
        int mid = (low + high) / 2;

        if (i <= mid)
        {
            update(2 * ind + 1, low, mid, i, val);
        }
        else
        {
            update(2 * ind + 2, mid + 1, high, i, val);
        }
        seg[ind] = min(seg[2 * ind + 1], seg[2 * ind + 2]);
    }

    void printSegmentTree()
    {
        for (auto it : seg)
        {
            cout << it << " ";
        }
        cout << endl;
    }
};
int main()
{
    int n1, n2;
    cin >> n1 >> n2;

    vector<int> arr1(n1);
    vector<int>arr2(n2);
    for (int i = 0; i < n1; i++)
        cin >> arr1[i];
    for (int i = 0; i < n2; i++)
        cin >> arr2[i];


    SGTree s1(n1); // First Segment Tree
    s1.build(0, 0, n1 - 1, arr1);
    SGTree s2(n2); // Second Segment Tree
    s2.build(0, 0, n2 - 1, arr2);

    int q;
    cin >> q;

    while (q--)
    {
        int type;
        cin >> type;
        if (type == 1)
        {
            int l1, r1, l2, r2;
            cin >> l1 >> r1 >> l2 >> r2;
            int min1 = s1.query(0, 0, n1 - 1, l1, r1);
            int min2 = s2.query(0, 0, n2 - 1, l2, r2);
            cout<<min(min1, min2)<<endl;
        }
        else
        {
            int arrNo;
            cin >> arrNo;
            if (arrNo == 1)
            {
                int i, val;
                cin >> i >> val;

                s1.update(0, 0, n1 - 1, i, val);
            }
            else
            {
                int i, val;
                cin >> i >> val;

                s2.update(0, 0, n2 - 1, i, val);
            }
        }
    }

    return 0;
}