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

std::vector<std::vector<int>> Multiply(std::vector<std::vector<int>> &M, std::vector<std::vector<int>> &N) {
    std::vector<std::vector<int>> res (M.size(), std::vector<int>(N[0].size()));
    for (int i=0; i<M.size(); ++i)
        for (int j=0; j<N[0].size(); ++j)
            for (int k=0; k<M[0].size(); ++k)
                res[i][j] += M[i][k]*N[k][j];
    return res;
}

std::vector<std::vector<int>> LinearCover(std::vector<std::vector<int>>& nums) {
    int size = nums.size();
    std::vector<std::vector<int>> matrix(size, std::vector<int>(size, 0));
    std::vector<std::vector<int>> res;
    for (int i=0; i<size; ++i)
        for (int j=0; j<nums[i].size(); ++j)
            matrix[nums[i][j]][i]= 1;
    long long possibility = pow(2, size);
    for (long long i=0; i<possibility; ++i) {
        std::vector<std::vector<int>> X (size, std::vector<int>(1, 0));
        int minCount = size;
        int count = 0;
        for (int j=0; j<size; ++j) {
            count += i&1;
            X[j][0] = i&1;
            i>>=1;
        }
        std::vector<std::vector<int>> mul = Multiply(matrix, X);
        for (int i=0; i<size; ++i) {
            if (mul[i][0]==0)
                break;
            if (count<minCount) {
                minCount = count;
                res = X;
            }
        }
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

    std::vector<std::vector<int>> S = randomSet(30);
    tik = clock();
    std::vector<std::vector<int>> res = LinearCover(S);
    tok = clock();
    print(res);
    print(tok-tik);
}