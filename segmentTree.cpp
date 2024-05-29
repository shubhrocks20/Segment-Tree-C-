#include <bits/stdc++.h>
using namespace std;
void build(int ind, int low, int high, vector<int> &arr, vector<int> &seg)
{
    if (low == high)
    {
        seg[ind] = arr[low];
        return;
    }
    int mid = (low + high) >> 1;
    build(2 * ind + 1, low, mid, arr, seg);
    build(2 * ind + 2, mid + 1, high, arr, seg);

    seg[ind] = min(seg[2 * ind + 1], seg[2 * ind + 2]);
}

int query(int ind, int low, int high, int l, int r, vector<int> &seg)
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
    int mid = (low + high) >> 1;
    return min(query(2 * ind + 1, low, mid, l, r, seg), query(2 * ind + 2, mid + 1, high, l, r, seg));
}

void update(int ind, int low, int high, int i, int val, vector<int> &seg)
{
    if (low == high)
    {
        seg[ind] = val;
        return;
    }
    int mid = (low + high) >> 1;

    if (i <= mid)
    {
        update(2 * ind + 1, low, mid, i, val, seg);
    }
    else
    {
        update(2 * ind + 2, mid + 1, high, i, val, seg);
    }
    seg[ind] = min(seg[2 * ind + 1], seg[2 * ind + 2]);
}

void printSegmentTree(vector<int>& seg)
    {
        for (auto it : seg)
        {
            cout << it << " ";
        }
        cout << endl;
    }
int main()
{
    int n;
    cin >> n;

    vector<int> arr(n);

    for (int i = 0; i < n; i++)
    {
        cin >> arr[i];
    }
    vector<int> seg(4 * n, 0);
    build(0, 0, n - 1, arr, seg);
    printSegmentTree(seg);
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

            cout << query(0, 0, 0, l, r, seg) << endl;
        }
        else
        {
            int i, val;
            cin >> i >> val;
            update(0, 0, n - 1, i, val, seg);
        }
    }
    return 0;
}