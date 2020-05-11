#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
#include <ctime>

typedef std::pair<int, int> cord;

int getTurn(cord a, cord b, cord c) {
    int val = (b.second-a.second)*(c.first-b.first)
              -(b.first-a.first)*(c.second-b.second);
    return (val==0)? 0: (val>0? 1:2); // 1:left-turn, 2:right-turn
}

int distance(cord a, cord b) {
    return (a.first-b.first)*(a.first-b.first)
           +(a.second-b.second)*(a.second-b.second);
}

cord belowTop(std::stack<cord> &S) {
    cord temp = S.top();
    S.pop();
    cord res = S.top();
    S.push(temp);
    return res;
}

void process(std::vector<cord> &Q, int N) {
    int yMin = Q[0].second, py = 0;
    for (int i=0; i<N; ++i) {
        if (Q[i].second==yMin && Q[i].first<Q[py].first)
            py = i;
        else if (Q[i].second<yMin) {
            yMin = Q[i].second;
            py = i;
        }
    }
    swap(Q[0], Q[py]);
    cord P = Q[0];
    // sort by polar coordinates with original point
    sort(Q.begin()+1, Q.end(), [P](cord a, cord b)->bool{
        int res = getTurn(P, a, b); return res==0?
        distance(a, P)<distance(b, P): res==2;});
    int arrSize = 1;
    for (int i=1; i<N; ++i) {
        // keep farthest
        while (i<N-1 && getTurn(P, Q[i], Q[i+1]) == 0)
            ++i;
        Q[arrSize++] = Q[i];
    }
    if (arrSize < 3) return;
    std::stack<cord> S;
    S.push(Q[0]), S.push(Q[1]), S.push(Q[2]);
    for (int i=3; i<arrSize; ++i) {
        // drop right-turn
        while (getTurn(belowTop(S), S.top(), Q[i]) != 2)
            S.pop();
        S.push(Q[i]);
    }
    while (!S.empty()) {
        std::cout << "[" << S.top().first << ", " << S.top().second << "]";
        S.pop();
    }
}

int main()
{
    int N = 100;
    clock_t tik, tok;
    std::vector<cord> setQ(N, cord());
    for (int i=0; i<N; ++i) {
        setQ[i].first = rand()%100;
        setQ[i].second = rand()%100;
    }
    tik = clock();
    process(setQ, N);
    tok = clock();
    std::cout << "\nConsumed Time: " << 1000*(double)(tok-tik)/CLOCKS_PER_SEC << "ms";
}