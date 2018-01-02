#include "map.h"
#include <vector>
#include <cmath>
#include <queue>
#include <tuple>
#include <unordered_map>
#include <algorithm>
#include <iostream>

Map::Map(int width, int height, int lives, int money): width(width), height(height), lives(lives), money(money), map(width,std::vector<Tile>(height, Tile(TileType::GROUND))) {
//    makeMap();
}

int Map::getWidth() const {
    return width;
}

int Map::getHeight() const {
    return height;
}

int Map::getLives() const {
    return lives;
}

int Map::getMoney() const {
    return money;
}

void Map::setMoney(int x) {
    money += x;
}

void Map::setLives(int x) {
    lives = x;
}

void Map::decrementLives() {
    lives -= 1;
}

Tile & Map::operator[](Position pos) {
    return map[pos.first][pos.second];
}

//const Tile & Map::operator[](Position pos) const {
//   return map[pos.first][pos.second];
//}

Tile Map::getTile(Position pos) const {
    return map[pos.first][pos.second];
}

void Map::setTile(Tile tile, Position pos) {
    map[pos.first][pos.second] = tile;
}

void Map::renderTile(float x, float y, float z) {
    glPushMatrix();

    glTranslated(x, y, z);

    glBegin(GL_TRIANGLES);
    glNormal3d(0.10,1,0);
    glVertex3d(0,1.10,0);
    glVertex3d(1,1,1);
    glVertex3d(1,1,-1);

    glNormal3d(0,1,-0.10);
    glVertex3d(0,1.10,0);
    glVertex3d(1,1,-1);
    glVertex3d(-1,1,-1);

    glNormal3d(-0.10,1,0);
    glVertex3d(0,1.10,0);
    glVertex3d(-1,1,-1);
    glVertex3d(-1,1,1);

    glNormal3d(0,1,0.10);
    glVertex3d(0,1.10,0);
    glVertex3d(-1,1,1);
    glVertex3d(1,1,1);
    glEnd();

    glPopMatrix();
}

void Map::render() {
    glPushMatrix();
    glTranslated(-width,0,-height+2);

    for (int i = 0; i < getWidth(); ++i) {
        for (int j = 0; j < getHeight(); ++j) {
            renderTile(i * 2, 0, j * 2);
        }
    }
    glPopMatrix();

    glColor3f(0.8,0.4,0.4);
    float emission[4] = {0.4,0.0,0.0,1.0};
    glMaterialfv(GL_FRONT, GL_EMISSION, emission);
    cube(8.0, 1.5, -8.0, 0, 1.0);
    glColor3f(0.4,0.8,0.4);
    emission[0] = 0.0;
    emission[1] = 0.4;
    glMaterialfv(GL_FRONT, GL_EMISSION, emission);
    cube(-10.0, 1.5, -8.0, 0, 1.0);

    if (getLives() <= 0) {
        bool pixels[7][53] = {{0,1,1,1,0, 0, 0,1,1,1,0, 0, 0,1,0,1,0, 0, 1,1,1,1,1, 0, 0,0,0,0,0, 0, 0,1,1,1,0, 0, 1,0,0,0,1, 0, 1,1,1,1,1, 0, 1,1,1,1,0},
                                     {1,0,0,0,1, 0, 1,0,0,0,1, 0, 1,0,1,0,1, 0, 1,0,0,0,0, 0, 0,0,0,0,0, 0, 1,0,0,0,1, 0, 1,0,0,0,1, 0, 1,0,0,0,0, 0, 1,0,0,0,1},
                                     {1,0,0,0,0, 0, 1,0,0,0,1, 0, 1,0,1,0,1, 0, 1,0,0,0,0, 0, 0,0,0,0,0, 0, 1,0,0,0,1, 0, 1,0,0,0,1, 0, 1,0,0,0,0, 0, 1,0,0,0,1},
                                     {1,0,1,1,1, 0, 1,1,1,1,1, 0, 1,0,1,0,1, 0, 1,1,1,1,0, 0, 0,0,0,0,0, 0, 1,0,0,0,1, 0, 1,0,0,0,1, 0, 1,1,1,1,0, 0, 1,1,1,1,0},
                                     {1,0,0,0,1, 0, 1,0,0,0,1, 0, 1,0,1,0,1, 0, 1,0,0,0,0, 0, 0,0,0,0,0, 0, 1,0,0,0,1, 0, 1,0,0,0,1, 0, 1,0,0,0,0, 0, 1,0,1,0,0},
                                     {1,0,0,0,1, 0, 1,0,0,0,1, 0, 1,0,1,0,1, 0, 1,0,0,0,0, 0, 0,0,0,0,0, 0, 1,0,0,0,1, 0, 0,1,0,1,0, 0, 1,0,0,0,0, 0, 1,0,0,1,0},
                                     {1,1,1,1,1, 0, 1,0,0,0,1, 0, 1,0,1,0,1, 0, 1,1,1,1,1, 0, 0,0,0,0,0, 0, 0,1,1,1,0, 0, 0,0,1,0,0, 0, 1,1,1,1,1, 0, 1,0,0,0,1}};
        glColor3f(0.9,0.9,0.9);
        glPushMatrix();
        for (float th=0.0; th <= 271.0; th += 90) {
            glRotated(th, 0,1,0);
            for (int i=0; i<53; ++i) {
                for (int j=0; j<7;++j) {
                    if (pixels[j][i])
                        cube(2.5-0.1*i,4-0.1*j,9.0, 0, 0.1/sqrt(2.0));
                }
            }
        }
        glPopMatrix();
    }
}

int Map::spawnEnemy() {
    if (spawncount > 0 && currentwave >= 0) {
        currentwavetime += 16;
        if (currentwavetime >= wavetime) {
            currentwavetime -= wavetime;
            spawncount -= 1;
            return waves[currentwave][9-spawncount];
        }
    }
    return 0;
}

void Map::spawnWave()
{
    if (spawncount <= 0)
    {
        if (currentwave < 8)
            currentwave += 1;
        spawncount = 10;
    }
}

bool Map::isEmpty(Position pos) {
    if (pos.first >= width || pos.first < 0 || pos.second >= height || pos.second < 0) {
        return false;
    }
    return map[pos.first][pos.second].tileType == TileType::GROUND;
}

bool Map::setTower(TileType tower, Position pos) {
    if (isEmpty(pos)) {
        map[pos.first][pos.second].tileType = tower;
        return true;
    }
    return false;
}

Position Map::getGoal()
{
    return goal;
}

std::vector<Position> Map::getNeighbors(Position pos) {
    std::vector<Position> neighbors;
    Position up = Position(pos.first - 1, pos.second);
    Position down = Position(pos.first + 1, pos.second);
    Position left = Position(pos.first, pos.second - 1);
    Position right = Position(pos.first, pos.second + 1);
    if (isEmpty(up)) {
        neighbors.push_back(up);
    }
    if (isEmpty(down)) {
        neighbors.push_back(down);
    }
    if (isEmpty(left)) {
        neighbors.push_back(left);
    }
    if (isEmpty(right)) {
        neighbors.push_back(right);
    }
    return neighbors;
}

float Map::getHValue(Position cur, Position end) {
    int dx = cur.first - end.first;
    int dy = cur.second - end.second;
    return sqrt(dx * dx + dy * dy);
}

namespace std {

  template <>
  struct hash<Position>
  {
    std::size_t operator()(const Position& k) const
    {
      using std::size_t;
      using std::hash;

      // Compute individual hash values for first,
      // second and third and combine them using XOR
      // and bit shifting:

      return ((hash<int>()(k.first)
               ^ (hash<int>()(k.second) << 1)) >> 1);
    }
  };

}

std::vector<Position> Map::AStar(Position start, Position end) {
    //std::vector<Position> closed;
    PriorityQueue<Position, float> open;
    open.put(start, getHValue(start, end));
    std::unordered_map<Position, Position> came_from;
    std::unordered_map<Position, float> cost_so_far;
    came_from[start] = start;
    cost_so_far[start] = 0;
    std::vector<Position> path;

    while (!open.empty()) {
        auto cur = open.get();
        //std::cout << cur.first << "\t" << cur.second << std::endl;
        if (cur == end) {
            path.push_back(cur);
            while (cur != start) {
                cur = came_from[cur];
                path.push_back(cur);
            }
            //path.push_back(start);
            std::reverse(path.begin(), path.end());
            return path;
        }
        for (auto& next : getNeighbors(cur)) {
              float new_cost = cost_so_far[cur] + 1;
              if (!cost_so_far.count(next) || new_cost < cost_so_far[next]) {
                cost_so_far[next] = new_cost;
                float priority = new_cost + getHValue(next, end);
                open.put(next, priority);
                came_from[next] = cur;
              }
        }
    }
    return path;
}

void Map::makeMap() {
    for(int i = 0; i < width; i++) {
        for(int j = 0; j < height; j++) {
            map[i][j].tileType = TileType::GROUND;
            // if(i == 0 || i == width - 1 || j == 0 || j == height - 1) {
            //     map[i][j].tileType = TileType::NOTHING;
            // }
            // else {
            //     map[i][j].tileType = TileType::GROUND;
            // }
        }
    }
}


// Score functions
int Map::getScore() {
    return score;
}

void Map::incrementScore(int points) {
    score += points;
}
