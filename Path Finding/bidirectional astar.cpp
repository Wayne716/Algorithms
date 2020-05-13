#include <iostream>
#include <vector>
#include <cmath>
#define WATER 2
#define SAND 4
#define STRAIGHT 1
#define CORNER 1.414
#define WEIGHT 1

struct Node {
    int x, y;
    double GF, HF, FF;
    double GB, HB, FB;
    Node *prevF, *prevB;
    bool pass;
    double cost = 0;
};

class PathFinding {
    Node *_map;
    int height, width;
    Node *_start, *_end, *_mid;
    std::vector<std::vector<char>> visual;
    std::vector<Node*> openForward, openBackward;
    std::vector<Node*> closeForward, closeBackward;
    Node *nodeF, *nodeB;

public:
    PathFinding() = delete;
    explicit PathFinding(const std::vector<std::vector<char>> &map) {
        height = map.size();
        width = map[0].size();
        assert(height!=0 && width!=0);
        visual = map;
        _map = new Node[height*width];
        // import map as an array
        for (int i=0; i<height; ++i) {
            for (int j=0; j<width; ++j) {
                Node &node = _map[i*width+j];
                node.x = j;
                node.y = i;
                node.GF = std::numeric_limits<double>::infinity();
                node.FF = std::numeric_limits<double>::infinity();
                node.GB = std::numeric_limits<double>::infinity();
                node.FB = std::numeric_limits<double>::infinity();
                switch (map[i][j]) {
                    case 'W': node.pass = true; node.cost = WATER; break;
                    case 'S': node.pass = true; node.cost = SAND; break;
                    case 'O': node.pass = true; break;
                    case 'X': node.pass = false; break;
                    case 'A': node.pass = true; _start = &node; break;
                    case 'B': node.pass = true; _end = &node; node.cost = SAND; break;
                    default: exit(-1);
                }
            }
        }
        if (_start==nullptr || _end==nullptr)
            exit(-1);
        for (int i=0; i<height; ++i) {
            for (int j=0; j<width; ++j) {
                Node &node = _map[i*width+j];
                // heuristic function: euclidean
                node.HF = sqrt((_end->x - node.x)*(_end->x - node.x) + (_end->y - node.y)*(_end->y - node.y));
                node.HB = sqrt((_start->x - node.x)*(_start->x - node.x) + (_start->y - node.y)*(_start->y - node.y));
            }
        }
    }

    bool forwardFind() {
        std::vector<int> dirX = {-1, 0, 1};
        std::vector<int> dirY = {-1, 0, 1};
        nodeF = openForward[0];
        int size = openForward.size();
        // pick node which has least F
        for (int i=1; i<size; ++i)
            if (openForward[i]->FF < nodeF->FF)
                nodeF = openForward[i];

        openForward.erase(std::find(openForward.begin(), openForward.end(), nodeF));
        closeForward.push_back(nodeF);

        if (nodeF==_end)
            return true;
        int x = nodeF->x, y = nodeF->y;
        Node *adj;
        for (int i=0; i<3; ++i) {
            for (int j=0; j<3; ++j) {
                int dir = abs(dirX[i]) + abs(dirY[j]);
                int newX = x + dirX[i];
                int newY = y + dirY[j];
                if (dir==0 || newX<0 || newX==width || newY<0 || newY==height)
                    continue;
                double distance = (dir==1)? STRAIGHT: CORNER;
                adj = &_map[newY*width+newX];
                if (adj->pass && std::find(closeForward.begin(), closeForward.end(), adj)==closeForward.end()) {
                    // better way
                    if (nodeF->GF + distance + adj->cost < adj->GF) {
                        adj->prevF = nodeF;
                        adj->GF = nodeF->GF + distance + adj->cost;
                        adj->FF = adj->GF * WEIGHT + adj->HF;
                        if (std::find(openForward.begin(), openForward.end(), adj)==openForward.end())
                            openForward.push_back(adj);
                    }
                }
            }
        }

        return false;
    }

    bool backwardFind() {
        std::vector<int> dirX = {-1, 0, 1};
        std::vector<int> dirY = {-1, 0, 1};
        nodeB = openBackward[0];
        int size = openBackward.size();
        // pick node which has least F
        for (int i=1; i<size; ++i)
            if (openBackward[i]->FB < nodeB->FB)
                nodeB = openBackward[i];

        openBackward.erase(std::find(openBackward.begin(), openBackward.end(), nodeB));
        closeBackward.push_back(nodeB);

        if (nodeB==_start)
            return true;
        int x = nodeB->x, y = nodeB->y;
        Node *adj;
        for (int i=0; i<3; ++i) {
            for (int j=0; j<3; ++j) {
                int dir = abs(dirX[i]) + abs(dirY[j]);
                int newX = x + dirX[i];
                int newY = y + dirY[j];
                if (dir==0 || newX<0 || newX==width || newY<0 || newY==height)
                    continue;
                double distance = (dir==1)? STRAIGHT: CORNER;
                adj = &_map[newY*width+newX];
                if (adj->pass && std::find(closeBackward.begin(), closeBackward.end(), adj)==closeBackward.end()) {
                    // better way
                    if (nodeB->GB + distance + adj->cost < adj->GB) {
                        adj->prevB = nodeB;
                        adj->GB = nodeB->GB + distance + adj->cost;
                        adj->FB = adj->GB * WEIGHT + adj->HB;
                        if (std::find(openBackward.begin(), openBackward.end(), adj)==openBackward.end())
                            openBackward.push_back(adj);
                    }
                }
            }
        }


        return false;
    }

    bool Find() {
        openForward.push_back(_start);
        openBackward.push_back(_end);
        _start->GF = 0;
        _end->GB = 0;
        _start->FF = _start->HF;
        _end->FB = _end->HB;
        while (!forwardFind() && !backwardFind()) {
            for (int i=0; i<openForward.size(); ++i) {
                for (int j=0; j<openBackward.size(); ++j) {
                    if (openForward[i] == openBackward[j]) {
                        nodeF = openForward[i];
                        nodeB = openBackward[j];
                        return true;
                    }

                }
            }
        }
        return false;
    }

    void visualize() {
        // trace back from end to start
        while (nodeF!=_start) {
            visual[nodeF->y][nodeF->x] = '.';
            nodeF = nodeF->prevF;
        }
        while (nodeB!=_end) {
            visual[nodeB->y][nodeB->x] = '.';
            nodeB = nodeB->prevB;
        }


        for (int i=0; i<height; ++i) {
            for (int j=0; j<width; ++j)
                std::cout << visual[i][j] << " ";
            std::cout << std::endl;
        }
    }

    ~PathFinding() {
        delete []_map;
    }
};



int main() {
    std::vector<std::vector<char>> map
            {{'O','O','O','X','O','O','O','X','O','O','O','O','X','O','O','O','O','O','O','O','O','O','O','O','S','S','S','S','S','S','S','S','S','S','S','B','S','S','S','S'},
             {'O','O','O','O','O','O','O','X','O','O','O','O','X','O','O','O','O','O','O','O','O','O','O','O','O','S','S','S','S','S','S','S','S','S','W','S','S','S','S','S'},
             {'X','X','X','X','X','X','O','X','X','X','X','O','X','O','O','O','O','O','O','O','O','O','O','O','O','O','S','S','S','S','S','S','S','W','S','S','S','S','S','S'},
             {'O','O','O','O','O','O','O','O','X','O','O','O','X','O','O','O','O','O','O','O','O','O','O','O','O','O','S','S','S','S','S','S','W','S','S','S','S','O','O','O'},
             {'O','O','O','O','O','O','O','O','O','O','O','O','X','O','O','O','O','O','O','O','O','O','O','O','O','O','S','S','S','S','S','S','S','W','S','S','O','O','O','O'},
             {'O','O','O','O','O','O','O','X','X','O','O','O','X','O','O','O','O','O','O','O','O','O','O','O','O','O','O','S','S','S','S','S','S','W','W','O','O','O','O','O'},
             {'O','O','X','X','X','X','X','X','O','O','O','O','X','O','O','O','O','O','O','O','O','O','O','O','O','O','O','S','S','S','S','S','S','W','W','O','O','O','O','O'},
             {'O','O','X','O','O','X','O','X','O','O','O','O','X','O','O','O','O','O','O','O','O','O','O','O','O','O','O','O','O','S','S','S','S','W','W','W','X','O','O','O'},
             {'O','O','O','O','O','X','O','O','O','O','O','O','O','O','O','O','O','O','O','O','O','O','O','O','O','O','O','O','O','O','O','O','W','W','W','W','O','O','O','O'},
             {'O','O','O','O','O','X','O','X','O','O','O','O','O','O','O','O','O','O','O','O','O','O','O','O','O','O','O','O','O','O','O','O','W','W','W','O','X','O','O','O'},
             {'O','O','X','O','A','X','O','X','X','O','O','O','O','O','O','O','O','O','O','X','X','X','O','O','O','O','O','O','X','O','O','O','W','W','O','W','W','O','O','O'},
             {'O','O','X','X','X','X','O','O','X','O','O','O','O','O','O','O','O','O','O','X','X','X','O','O','O','O','O','O','O','O','O','X','W','O','W','W','O','O','O','O'},
             {'O','O','O','X','O','O','O','O','X','O','O','O','X','O','O','O','O','O','O','X','X','X','O','O','O','O','O','O','O','O','O','O','O','W','W','O','O','O','O','O'},
             {'O','O','O','X','O','O','O','O','X','X','O','X','X','O','O','O','O','O','O','O','O','O','O','O','O','O','O','O','O','O','O','X','W','W','W','O','O','O','O','O'},
             {'O','O','O','X','O','O','O','O','X','O','O','O','X','O','O','O','O','O','O','O','O','O','O','O','O','O','O','O','O','O','O','O','W','W','W','O','O','O','O','O'},
             {'O','O','O','X','X','X','X','X','X','O','O','O','X','O','O','O','O','O','O','O','O','O','O','O','X','X','O','O','O','O','O','W','W','W','O','O','O','O','O','O'},
             {'O','O','O','X','O','O','O','O','O','O','O','O','X','O','O','O','O','O','O','O','O','O','O','O','X','X','O','O','O','O','O','W','W','W','O','O','O','O','O','O'},
             {'O','O','O','O','O','O','O','X','O','O','O','O','X','O','O','O','O','O','O','O','O','O','O','O','O','O','O','O','O','O','W','W','W','O','O','O','O','O','O','O'},
             {'O','O','O','X','O','O','O','X','O','O','O','O','X','O','O','O','O','O','O','O','O','O','O','O','O','O','O','O','O','W','W','W','O','O','O','O','O','O','O','O'},
             {'O','O','O','X','O','O','O','X','O','O','O','O','X','O','O','O','O','O','O','O','O','O','O','O','O','O','O','O','W','W','W','O','O','O','O','O','O','O','O','O'},
            };

    PathFinding A(map);
    if (A.Find())
        A.visualize();
    else exit(-1);
}