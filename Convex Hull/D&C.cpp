#include <iostream>
#include <vector>
#include <ctime>
#include <algorithm>
#include <set>

using namespace std;
typedef std::pair<int, int> cord;
cord operator+(const cord& A, const cord &B) {
    return {A.first+B.first, A.second+B.second};
}
cord operator-(const cord& A, const cord &B) {
    return {A.first-B.first, A.second-B.second};
}

int getQuadrant(cord P) {
    if (P.first>=0 && P.second>=0) return 1;
    else if (P.first<=0 && P.second>=0) return 2;
    else if (P.first<=0 && P.second<=0) return 3;
    else return 4;
}

std::vector<cord> bruteForce(std::vector<cord> Q)
{
    int size = Q.size();
    std::set<cord> S;
    for (int i=0; i<size; ++i)
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
        res.push_back(e);
    cord center = {0,   0};
    size = res.size();
    for (int i=0; i<size; ++i) {
        center.first += res[i].first;
        center.second += res[i].second;
    }
    center.first /= size;
    center.second /= size;
    // sort in anti-clock-wise order
    sort(res.begin(), res.end(), [center](cord a, cord b)->bool{
        cord da = a-center, db = b-center;
        int quadA = getQuadrant(da), quadB = getQuadrant(db);
        if (quadA != quadB) return (quadA<quadB);
        return (da.first*db.second>da.second*db.first);
    });
    return res;
}

int getTurn(cord a, cord b, cord c) {
    int val = (b.second-a.second)*(c.first-b.first) -(b.first-a.first)*(c.second-b.second);
    return (val==0)? 0: (val>0? 1:-1); // right:left
}

std::vector<cord> merge(std::vector<cord> L, std::vector<cord> R) {
    int sizeL = L.size(), sizeR = R.size();
    int rightMost = 0, leftMost = 0;
    for (int i=1; i<sizeL; ++i)
        if (L[i].first>L[rightMost].first)
            rightMost = i;
    for (int i=1; i<sizeR; ++i)
        if (R[i].first<R[leftMost].first)
            leftMost = i;
    bool flag = false;
    int rightTop = leftMost, leftTop = rightMost;
    // top tangent
    while (!flag) {
        flag = true;
        // drop right-turn in left hull
        while (getTurn(R[rightTop], L[leftTop], L[(leftTop+1)%sizeL])>0)
            leftTop = (leftTop+1)%sizeL;
        // drop left-turn in right hull
        while (getTurn(L[leftTop], R[rightTop], R[(sizeR+rightTop-1)%sizeR])<0) {
            rightTop = (sizeR+rightTop-1)%sizeR;
            flag = false;
        }
    }
    flag = false;
    int rightBottom = leftMost, leftBottom = rightMost;
    // bottom tangent
    while (!flag) {
        // drop right-turn in right hull
        flag = true;
        while (getTurn(L[leftBottom], R[rightBottom], R[(rightBottom+1)%sizeR])>0)
            rightBottom = (rightBottom+1)%sizeR;
        // drop left-turn in left hull
        while (getTurn(R[rightBottom], L[leftBottom], L[(sizeL+leftBottom-1)%sizeL])<0) {
            leftBottom = (sizeL+leftBottom-1)%sizeL;
            flag = false;
        }
    }
    std::vector<cord> res;
    res.push_back(L[leftTop]);
    while (leftTop != leftBottom) {
        leftTop = (leftTop+1)%sizeL;
        res.push_back(L[leftTop]);
    }
    res.push_back(R[rightBottom]);
    while (rightBottom != rightTop) {
        rightBottom = (rightBottom+1)%sizeR;
        res.push_back(R[rightBottom]);
    }
    return res;
}


std::vector<cord> divide(std::vector<cord> Q) {
    int size = Q.size();
    if (size <= 5)
        return bruteForce(Q);
    std::vector<cord> left, right;
    for (int i=0; i<size/2; ++i)
        left.push_back(Q[i]);
    for (int i=size/2; i<size; ++i)
        right.push_back(Q[i]);
    std::vector<cord> L = divide(left);
    std::vector<cord> R = divide(right);
    return merge(L, R);
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
    sort(setQ.begin(), setQ.end());
    std::vector<cord> res = divide(setQ);
    tok = clock();
    for (const auto &e : res)
        std::cout << "[" << e.first << "," << e.second << "]";
    std::cout << "\nConsumed time: "<< 1000*(double)(tok-tik)/CLOCKS_PER_SEC << "ms";
}