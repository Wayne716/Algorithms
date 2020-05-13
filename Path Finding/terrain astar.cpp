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
    double G, H, F;
    Node* prev;
    bool pass;
    double cost = 0;
};

class PathFinding {
    Node *_map = nullptr;
    int height, width;
    Node *_start, *_end;
    std::vector<std::vector<char>> visual;

public:
    PathFinding() = delete;
    explicit PathFinding(const std::vector<std::vector<char>> &map) {
        height = map.size();
        width = map[0].size();
        assert(height!=0 && width!=0);
        visual = map;
        _map = new Node[height*width];
        for (int i=0; i<height; ++i) {
            for (int j=0; j<width; ++j) {
                // import map as an array
                Node &node = _map[i*width+j];
                node.x = j;
                node.y = i;
                node.G = std::numeric_limits<double>::infinity();
                node.F = std::numeric_limits<double>::infinity();
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
                node.H = sqrt((_end->x - node.x)*(_end->x - node.x) + (_end->y - node.y)*(_end->y - node.y));
            }
        }
    }

    bool Find() {
        std::vector<Node*> OPEN;
        std::vector<Node*> CLOSE;
        std::vector<int> dirX = {-1, 0, 1};
        std::vector<int> dirY = {-1, 0, 1};
        OPEN.push_back(_start);
        _start->G = _start->cost;
        _start->F = _start->H;

        while (!OPEN.empty()) {
            Node *node = OPEN[0];
            int size = OPEN.size();
            // pick node which has least F
            for (int i=1; i<size; ++i)
                if (OPEN[i]->F < node->F)
                    node = OPEN[i];
            if (node==_end)
                return true;
            int x = node->x, y = node->y;
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
                    if (adj->pass && std::find(CLOSE.begin(), CLOSE.end(), adj)==CLOSE.end()) {
                        // better way
                        if (node->G + distance + adj->cost < adj->G) {
                            adj->prev = node;
                            adj->G = node->G + distance + adj->cost;
                            adj->F = adj->G * WEIGHT + adj->H;
                            if (std::find(OPEN.begin(), OPEN.end(), adj)==OPEN.end())
                                OPEN.push_back(adj);
                        }
                    }
                }
            }
            OPEN.erase(std::find(OPEN.begin(), OPEN.end(), node));
            CLOSE.push_back(node);
        }
        return false;
    }

    void visualize() {
        Node *node = _end->prev;
        // trace back from end to start
        while (node!=_start) {
            visual[node->y][node->x] = '.';
            node = node->prev;
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