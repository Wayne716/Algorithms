#include <iostream>
#include <vector>
#include <unordered_set>
#include <ctime>

void shuffle(std::vector<int> &nums) {
    int size = nums.size();
    for (int i=size-1; i>=0; --i)
        std::swap(nums[rand()%(i+1)], nums[i]);
}

std::vector<std::vector<int>> randomSet(int N) {
    std::vector<int> source;
    source.reserve(N);
    for (int i=0; i<N; ++i)
        source.emplace_back(i);
    shuffle(source);
    // ensured answer
    std::vector<std::vector<int>> res;
    res.emplace_back(std::vector<int>(source.end()-20, source.end()));
    source.resize(source.size()-20);
    while (source.size()>=20) {
        int size = rand()%20+1;
        int pick = rand()%size+1;
        std::vector<int> temp(source.end()-pick, source.end());
        source.resize(source.size()-pick);
        pick = size - pick;
        while (pick--) {
            int roll = rand()%res.size();
            temp.push_back(res[roll][res[roll].size()-1]);
            res[roll].pop_back();
            if (res[roll].empty())
                res.erase(res.cbegin()+roll);
        }
        res.emplace_back(temp);
    }
    res.emplace_back(source);
    // additional set
    while (res.size() < N) {
        int size = rand()%N+1;
        std::unordered_set<int> lib;
        while (size--)
            lib.insert(rand()%N);
        std::vector<int> temp (lib.begin(), lib.end());
        res.emplace_back(temp);
    }
    return res;
}

std::vector<std::vector<int>> greedyCover(std::vector<std::vector<int>>& nums, int target) {
    std::unordered_set<int> owned;
    std::vector<std::vector<int>> res;
    int total = 0;
    while (total<target) {
        int index = 0, maxDif = 0;
        for (int i=0; i<nums.size(); ++i) {
            int count = 0;
            for (int j=0; j<nums[i].size(); ++j) {
                if (owned.find(nums[i][j])==owned.end()) {
                    ++count;
                }
            }
            if (count > maxDif) {
                index = i;
                maxDif = count;
            }
        }
        owned.insert(nums[index].begin(), nums[index].end());
        total += maxDif;
        res.push_back(nums[index]);
    }
    return res;
}

void print(std::vector<std::vector<int>> &nums) {
    for (auto& v: nums) {
        std::cout << "( ";
        for (auto& i: v) {
            std::cout << i << " ";
        }
        std::cout << ")\n";
    }
}

void print(time_t t) {
    std::cout << "Consumed Time: " << 1000*(double)(t)/CLOCKS_PER_SEC << "ms\n\n";
}


int main()
{
    time_t tik, tok;

    std::vector<std::vector<int>> S1 = randomSet(100);
    tik = clock();
    std::vector<std::vector<int>> res1 = greedyCover(S1, 100);
    tok = clock();
    print(res1);
    print(tok-tik);

    std::vector<std::vector<int>> S2 = randomSet(1000);
    tik = clock();
    std::vector<std::vector<int>> res2 = greedyCover(S2, 1000);
    tok = clock();
    print(res2);
    print(tok-tik);

    std::vector<std::vector<int>> S3 = randomSet(5000);
    tik = clock();
    std::vector<std::vector<int>> res3 = greedyCover(S3, 5000);
    tok = clock();
    print(res3);
    print(tok-tik);
}