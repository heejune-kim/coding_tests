
#include <stdio.h>
#include <vector>
#include <list>
#include <assert.h>

using namespace std;

#define INFINITE        0x7fffffff
#define VISITED         1
#define NOT_VISITED     0

class Node
{
    private:
        bool _is_visited;
        int _cost;
        vector<vector<int>> way_to;
        int _number;

    public:
        Node()
        {
            _is_visited = false;
            _cost = INFINITE;
        }

        virtual ~Node()
        {
        }

        void set_start(void)
        {
            _cost = 0;
        }

        int get_cost()
        {
            return _cost;
        }

        bool is_visited()
        {
            return _is_visited;
        }

        void set_visited()
        {
            _is_visited = true;
        }

        void add_way_to(vector<int>& info)
        {
            way_to.emplace_back(info);
        }

        vector<vector<int>>& get_way_to()
        {
            return way_to;
        }

        void set_cost(int cost)
        {
            _cost = cost;
        }
};

int find_minimum_cost(vector<Node>& nodes)
{
    int cost = INFINITE;
    int num = -1;

    for (int index = 0; index < nodes.size(); index++)
    {
        if (nodes[index].is_visited())
        {
            continue;
        }
        if (cost > nodes[index].get_cost())
        {
            cost = nodes[index].get_cost();
            num = index;
        }
    }

    return num;
}

void dijstra(vector<vector<int>>& data, int start, int end)
{
    int count = 0;
    for (int index = 0; index < data.size(); index++)
    {
        if (count < data[index][0])
        {
            count = data[index][0];
        }
        if (count < data[index][1])
        {
            count = data[index][1];
        }
    }
    count++;
    vector<Node> nodes(count);

    // TODO: initialize table.
    nodes[start].set_start();

    for (vector<vector<int>>::iterator iter = data.begin(); iter != data.end(); iter++)
    {
        auto& t = nodes[(*iter)[0]];
        t.add_way_to((*iter));
    }

    while (true)
    {
        // TODO: Find minimum cost
        int min = find_minimum_cost(nodes);
        if (min < 0)
        {
            printf("Cost for %d is %d.\n", end, nodes[end].get_cost());
            for (int index = 0; index < count; index++)
            {
                printf("%d - %d\n", index, nodes[index].get_cost());
            }
            break;
        }
        printf("node %d is selected.\n", min);
        int cost = nodes[min].get_cost();
        vector<vector<int>>& ways = nodes[min].get_way_to();
        for (int index = 0; index < ways.size(); index++)
        {
            int to = ways[index][1];
            int sub_cost = ways[index][2];
            if (nodes[to].get_cost() > (cost + sub_cost))
            {
                printf("Cost for %d is updated from %d to %d.\n", to, nodes[to].get_cost(), cost + sub_cost);
                nodes[to].set_cost(cost + sub_cost);
            }
        }
        nodes[min].set_visited();
    }
}

int main(void)
{
    vector<vector<int>> data = {{1, 4, 1}, {1, 2, 2}, {2, 4, 2}, {2, 3, 3}, {3, 2, 3}, {1, 3, 5}, {4, 3, 3}, {4, 5, 1}, {5, 3, 1}, {3, 6, 5}, {5, 6, 2}};

    for (vector<vector<int>>::iterator iter = data.begin(); iter != data.end(); iter++)
    {
        //printf("%d %d %d\n", (*iter)[0]);
        for (vector<int>::iterator iter1 = (*iter).begin(); iter1 != (*iter).end(); iter1++)
        {
            printf("%d ", (*iter1));
        }
        printf("\n");
    }
    dijstra(data, 1, 6);
 
    return 0;
}