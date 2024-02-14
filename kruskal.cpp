
#include <stdio.h>
#include <vector>
#include <bits/stdc++.h>

#include <assert.h>

using namespace std;

int UF_find(vector<int>& parent, int index)
{
    if (index != parent[index])
    {
        int temp = UF_find(parent, parent[index]);
        parent[index] = temp;
    }

#ifdef DEBUG
    printf("FIND(%d): %d\n", index, parent[index]);
#endif // DEBUG
    return parent[index];
}

void UF_union(vector<int>& parent, int index1, int index2)
{
    assert(index1 != index2);

    // with their parents.
    index1 = UF_find(parent, index1);
    index2 = UF_find(parent, index2);

    // update with smaller index.
    if (index1 < index2)
    {
        parent[index2] = index1;
    }
    else
    {
        parent[index1] = index2;
    }
}

vector<vector<int>> kruskal(vector<vector<int>>& data)
{
    vector<vector<int>> tree;

    // TODO: Count vertices
    int COUNT = 8; // modify this value when data size is changed or write code to count them.

    vector<int> parents;

    // Initialize parent table entries with their own index numbers.
    for (int index = 0; index < COUNT; index++) { parents.push_back(index); }

    // TODO: Sort by cost
    sort(data.begin(), data.end(), [](auto v1, auto v2) { return v1[2] < v2[2]; });

    // TODO: iterate data item
    for (auto& item : data)
    {
        // TODO: Check edge is part of circular using find(union-find) function.
#ifdef DEBUG
        printf("> %d %d\n", item[0], item[1]);
#endif // DEBUG
        if (UF_find(parents, item[0]) == UF_find(parents, item[1]))
        {
            printf("%d and %d are circular.\n", item[0], item[1]);
            continue;
        }

        // TODO: Add to tree and call union(union-find) function.
        UF_union(parents, item[0], item[1]);
        tree.emplace_back(item);
    }

#ifdef DEBUG
    printf("PARENTS: ");
    for (auto item : parents)
    {
        printf("%d ", item);
    }
    printf("\n");
#endif // DEBUG

    return tree;
}

void PrintTable(vector<vector<int>>& table)
{
    // Print return table.
    for (auto iter : table)
    {
        for (auto item : iter)
        {
            printf("%d ", item);
        }
        printf("\n");
    }
}

int main(void)
{
    vector<vector<int>> data = {{1, 2, 29}, {1, 5, 75}, {2, 3, 35}, {2, 6, 34}, {3, 4, 7}, {4, 6, 23}, {4, 7, 13}, {5, 6, 53}, {6, 7, 25}};

    auto ret = kruskal(data);
    PrintTable(ret);

    return 0;
}
