/*
 * https://school.programmers.co.kr/learn/courses/30/lessons/42892
 */

#include <algorithm>
#include <string>
#include <vector>
#include <stdio.h>

using namespace std;

typedef struct tagNode {
    int number;
    int x;
    int y;
    struct tagNode* left;
    struct tagNode* right;
} Node;

bool compare1 (Node a1, Node a2) {
    return (a1.x < a2.x);
}

// ArgMax
int findMax(vector<Node>& arr, int start, int end) {
    int pos = start;
    int val = arr[start].y;
    for (int temp = start + 1; temp <= end; temp++) {
        if (val < arr[temp].y) {
            pos = temp;
            val = arr[temp].y;
        }
    }
    return pos;
}

Node* getTopNode(vector<Node>& nodes, int start, int end) {
    if (start > end) {
        return 0;
    }
    int m = findMax(nodes, start, end);
    Node* left = getTopNode(nodes, start, m - 1);
    Node* right = getTopNode(nodes, m + 1, end);
    nodes[m].left = left;
    nodes[m].right = right;
    return &nodes[m];
}

void traverse_prefix(vector<int>& visited, Node* node) {
    visited.insert(visited.end(), node->number);
    if (node->left) {
        traverse_prefix(visited, node->left);
    }
    if (node->right) {
        traverse_prefix(visited, node->right);
    }
}

void traverse_postfix(vector<int>& visited, Node* node) {
    if (node->left) {
        traverse_postfix(visited, node->left);
    }
    if (node->right) {
        traverse_postfix(visited, node->right);
    }
    visited.insert(visited.end(), node->number);
}

vector<vector<int>> solution(vector<vector<int>> nodeinfo) {
    vector<vector<int>> answer;
    vector<Node> _nodes = vector<Node>(nodeinfo.size());
    int index = 0;
    for (auto& n : nodeinfo) {
        _nodes[index].number = index + 1;
        _nodes[index].x = n[0];
        _nodes[index].y = n[1];
        _nodes[index].left = 0;
        _nodes[index].right = 0;
        index++;
    }
    sort(_nodes.begin(), _nodes.end(), compare1);

    Node* root = getTopNode(_nodes, 0, _nodes.size() - 1);
    vector<int> prefix;
    vector<int> postfix;
    traverse_prefix(prefix, root);
    traverse_postfix(postfix, root);
    answer.insert(answer.end(), prefix);
    answer.insert(answer.end(), postfix);

    return answer;
}
