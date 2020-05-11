#include <iostream>
#include <vector>
#include <ctime>
#include <set>

typedef std::pair<int, int> cord;
cord operator-(const cord& A, const cord& B) {
    return {A.first-B.first, A.second-B.second};
}

std::vector<cord> bruteForce(std::vector<cord> Q)
{
    int size = Q.size();
    std::set<cord> S;
    for (int i=0; i<size; i++)
    {
        for (int j=i+1; j<size; j++) {
            int x1 = Q[i].first, y1 = Q[i].second;
            int x2 = Q[j].first, y2 = Q[j].second;
            int a = y2 - y1;
            int b = x1 - x2;
            int c = x1 * y2 - x2 * y1;
            // plane : ax + by - c = 0
            int side1 = 0, side2 = 0;
            for (const cord &p : Q) {
                if ((a * p.first + b * p.second - c) <= 0)
                    ++side1;
                if ((a * p.first + b * p.second - c) >= 0)
                    ++side2;
            }
            if (side1 == size || side2 == size)
            {
                S.insert(Q[i]);
                S.insert(Q[j]);
            }
        }
    }
    std::vector<cord> res;
    for (auto& e:S)
        res.emplace_back(e);
    return res;
}

int main()
{
    int N = 100;
    clock_t tik, tok;
    srand(time(NULL));
    std::vector<cord> setQ(N, cord());
    for (int i=0; i<N; ++i) {
        setQ[i].first = rand()%100;
        setQ[i].second = rand()%100;
    }
    tik = clock();
    std::vector<cord> res = bruteForce(setQ);
    tok = clock();
    for (const auto &e : res)
        std::cout << "[" << e.first << "," << e.second << "]";
    std::cout << "\nConsumed time: "<< 1000*(double)(tok-tik)/CLOCKS_PER_SEC << "ms";
}