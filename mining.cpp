
#include <vector>
#include <string>
#include <assert.h>

using namespace std;

#define INFINITE       0x7000000
#define MIN2(_A,_B)     ((_A) < (_B) ? (_A) : (_B))
#define MIN3(_A,_B,_C)  (((_C) < MIN(_A, _B)) ? (_C) : (MIN((_A), (_B) )))

int tired_rate[3][3] =
{
    {1, 1, 1},
    {5, 1, 1},
    {25, 5, 1}
};

int best_mine(int pick_type, vector<int> picks, vector<string> minerals, int index) {
    int tired = 0;
    //printf("index: %d, pick_type: %d\n", index, pick_type);

    picks[pick_type]--; // consume one pick
    for (int count = 0; count < 5; count++, index++) {
        if (minerals.size() <= index) { // no more minerals
            break;
        }
        switch (minerals[index][0]) {
        case 'd': tired += tired_rate[pick_type][0]; break;
        case 'i': tired += tired_rate[pick_type][1]; break;
        case 's': tired += tired_rate[pick_type][2]; break;
        default: assert(false);
        }
    }

    if (minerals.size() <= index) {
        return tired;
    }

    int min = INFINITE;
    for (pick_type = 0; pick_type < 3; pick_type++) {
        if (picks[pick_type] <= 0) {
            continue;
        }
        int temp = best_mine(pick_type, picks, minerals, index);
        if (min > temp) {
            min = temp;
        }
    }
    if (min != INFINITE)
        tired += min;
    return tired;
}

int solution(vector<int> picks, vector<string> minerals) {
    int pick_type;
    int min = INFINITE;
    for (pick_type = 0; pick_type < 3; pick_type++) {
        if (picks[pick_type] <= 0) {
            continue;
        }
        int temp = best_mine(pick_type, picks, minerals, 0);
        if (min > temp) {
            min = temp;
        }
    }
    return min;
}

int main(void) {
    #if 1
    // sample 1
    vector<int> picks = {1, 3, 2};
    vector<string> minerals = {"diamond", "diamond", "diamond", "iron", "iron", "diamond", "iron", "stone"};
    #else
    // sample 2
    vector<int> picks = {0, 1, 1};
    vector<string> minerals = {"diamond", "diamond", "diamond", "diamond", "diamond", "iron", "iron", "iron", "iron", "iron", "diamond"};
    #endif

    int ret = solution(picks, minerals);
    printf("%d\n", ret);

    return 0;
}
