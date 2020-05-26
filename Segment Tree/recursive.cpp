#include <iostream>
using namespace std;

#define MAX_LEN 1000

void build_tree(int arr[], int start, int end, int tree[], int node) {
    if (start == end)
        tree[node] = arr[start];
    else {
        int mid = (start + end) / 2;
        int left_node  = node * 2 + 1;
        int right_node = node * 2 + 2;
        build_tree(arr, start, mid, tree, left_node);
        build_tree(arr, mid+1, end, tree, right_node);
        tree[node] = tree[left_node] + tree[right_node];
    }
}

void update_tree(int arr[], int start, int end, int tree[], int node, int idx, int val) {
    if (start == end) {
        arr[idx] = val;
        tree[node] = val;
    }
    else {
        int mid = (start + end) / 2;
        int left_node  = node * 2 + 1;
        int right_node = node * 2 + 2;
        if (start <= idx && idx <= mid)
            update_tree(arr, start, mid, tree, left_node, idx, val);
        else
            update_tree(arr, mid+1, end, tree, right_node, idx, val);
        tree[node] = tree[left_node] + tree[right_node];
    }
}

int query_tree(int arr[], int start, int end, int tree[], int node, int L, int R) {
    if (R < start || L > end)
        return 0;
    else if ((start >= L && end <= R) || start == end)
        return tree[node];
    else {
        int mid = (start + end) / 2;
        int left_node  = node * 2 + 1;
        int right_node = node * 2 + 2;
        int left_sum  = query_tree(arr, start, mid, tree, left_node, L, R);
        int right_sum = query_tree(arr, mid+1, end, tree, right_node, L, R);
        return left_sum + right_sum;
    }
}

int main() {
    int arr[] = {1, 3, 5, 7, 9, 11};
    int tree[MAX_LEN] = {0};
    int size = 6;
    build_tree(arr, 0, size-1, tree, 0);
    update_tree(arr, 0, size-1, tree, 0, 4, 6);
    for (int i=0; i<14; ++i)
        cout << tree[i] << ' ';
    cout << query_tree(arr, 0, size-1, tree, 0, 2, 5);
    return 0;
}
