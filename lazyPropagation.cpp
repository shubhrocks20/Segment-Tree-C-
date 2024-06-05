#include <bits/stdc++.h>
using namespace std;

class SgTee
{
    vector<int> seg, lazy;

public:
    SgTee(int n)
    {
        seg.resize(4 * n);
        lazy.resize(4 * n);
    }
    void build(int ind, int low, int high, int arr[])
    {
        if (low == high)
        {
            seg[ind] = arr[low];
            return;
        }
        int mid = (low + high) >> 1;
        build(2 * ind + 1, low, mid, arr);
        build(2 * ind + 2, mid + 1, high, arr);

        seg[ind] = seg[2 * ind + 1] + seg[2 * ind + 2];
    }

    int query(int ind, int low, int high, int l, int r)
    {
        // If any update remaining

        if (lazy[ind] != 0)
        {
            seg[ind] += (high - low + 1) * lazy[ind];
            // Propogate
            if (low != high)
            {
                lazy[2 * ind + 1] += lazy[ind];
                lazy[2 * ind + 2] += lazy[ind];
            }
            lazy[ind] = 0;
        }
        // no overlap
        if (l > high or r < low)
            return 0;
        // complete overlap
        if (l <= low and r >= high)
            return seg[ind];

        int mid = (high + low) >> 1;
        return query(2 * ind + 1, low, mid, l, r) + query(2 * ind + 2, mid + 1, high, l, r);
    }
    void update(int ind, int low, int high, int l, int r, int val)
    {
        // If any update remaining

        if (lazy[ind] != 0)
        {
            seg[ind] += (high - low + 1) * lazy[ind];
            // Propogate
            if (low != high)
            {
                lazy[2 * ind + 1] += lazy[ind];
                lazy[2 * ind + 2] += lazy[ind];
            }
            lazy[ind] = 0;
        }
        // no overlap
        // l r low high or low high l r
        if (r < low or l > high)
            return;

        // total overlap
        // l low high r
        if (l <= low and high <= r)
        {
            // First update
            seg[ind] += (high - low + 1) * val;
            // Propogate downwards
            if (low != high)
            {
                lazy[2 * ind + 1] += val;
                lazy[2 * ind + 2] += val;
            }
            return;
        }

        int mid = (high + low) >> 1;
        update(2 * ind + 1, low, mid, l, r, val);
        update(2 * ind + 2, mid + 1, high, l, r, val);
        seg[ind] = seg[2 * ind + 1] + seg[2 * ind + 2];
    }

    void printSeg()
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
    int n;
    cin >> n;

    int arr[n];
    for (int i = 0; i < n; i++)
    {
        cin >> arr[i];
    }

    SgTee s1(n);
    s1.build(0, 0, n - 1, arr);
    // s1.printSeg();
    int q;
    cin >> q;

    while (q--)
    {
        int type;
        cin >> type;

        if (type == 1)
        {
            int l, r;
            cin >> l >> r;

            cout << s1.query(0, 0, n - 1, l, r) << endl;
        }
        else
        {
            int l, r, val;
            cin >> l >> r >> val;
            s1.update(0, 0, n - 1, l, r, val);
        }
    }
    return 0;
}