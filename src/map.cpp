#include "map.h"

Map::Map(int Width, int Height) {
  width = Width;
  height = Height;
  grid = new float*[width];
  for(int i=0; i < width; ++i)
    grid[i] = new float[height];
  generate();
}

Map::~Map() {
  for(int i=0; i < width; ++i)
    delete grid[i];
  delete[] grid;
}

void Map::generate(int seed) {
  srand(seed);
  generate();
}

void Map::generate() {
  // Initialize and set all values to 0.0
  float ** delta = new float*[width];
  for(int i=0; i < width; ++i) {
    delta[i] = new float[height];
    for(int j=0; j < height; ++j) {
      grid[i][j] = 0.0;
      delta[i][j] = 0.0;
    }
  }

  // Generate 16-scale noise
  for(int i=0; i < width; i += 16) {
    for(int j=0; j < height; j += 16) {
      delta[i][j] = (float)rand()/RAND_MAX - 0.5;
    }
  }
  for(int i=0; i < width; ++i) {
    for(int j=0; j < height; ++j) {
      int li = 16*(i/16);
      int hi = li+16;
      int lj = 16*(j/16);
      int hj = lj+16;
      float LL = delta[li][lj];
      float LH = 0.0;
      float HL = 0.0;
      float HH = 0.0;
      if (hj < height)
        LH = delta[li][hj];
      if (hi < width)
        HL = delta[hi][lj];
      if (hi < width && hj < height)
        HH = delta[hi][hj];
      float M1 = LL + (i%16)/(float)16 * (LH-LL);
      float M2 = HL + (i%16)/(float)16 * (HH-HL);
      delta[i][j] = M1 + (j%16)/(float)16 * (M2-M1);
    }
  }
  for(int i=0; i < width; ++i) {
    for(int j=0; j < height; ++j) {
      grid[i][j] += delta[i][j];
    }
  }

  // Generate 8-scale noise
  for(int i=0; i < width; i += 8) {
    for(int j=0; j < height; j += 8) {
      delta[i][j] = ((float)rand()/RAND_MAX - 0.5)/2.0;
    }
  }
  for(int i=0; i < width; ++i) {
    for(int j=0; j < height; ++j) {
      int li = 8*(i/8);
      int hi = li+8;
      int lj = 8*(j/8);
      int hj = lj+8;
      float LL = delta[li][lj];
      float LH = 0.0;
      float HL = 0.0;
      float HH = 0.0;
      if (hj < height)
        LH = delta[li][hj];
      if (hi < width)
        HL = delta[hi][lj];
      if (hi < width && hj < height)
        HH = delta[hi][hj];
      float M1 = LL + (i%8)/(float)8 * (LH-LL);
      float M2 = HL + (i%8)/(float)8 * (HH-HL);
      delta[i][j] = M1 + (j%8)/(float)8 * (M2-M1);
    }
  }
  for(int i=0; i < width; ++i) {
    for(int j=0; j < height; ++j) {
      grid[i][j] += delta[i][j];
    }
  }

  // Generate 4-scale noise
  for(int i=0; i < width; i += 4) {
    for(int j=0; j < height; j += 4) {
      delta[i][j] = ((float)rand()/RAND_MAX - 0.5)/4.0;
    }
  }
  for(int i=0; i < width; ++i) {
    for(int j=0; j < height; ++j) {
      int li = 4*(i/4);
      int hi = li+4;
      int lj = 4*(j/4);
      int hj = lj+4;
      float LL = delta[li][lj];
      float LH = 0.0;
      float HL = 0.0;
      float HH = 0.0;
      if (hj < height)
        LH = delta[li][hj];
      if (hi < width)
        HL = delta[hi][lj];
      if (hi < width && hj < height)
        HH = delta[hi][hj];
      float M1 = LL + (i%4)/(float)4 * (LH-LL);
      float M2 = HL + (i%4)/(float)4 * (HH-HL);
      delta[i][j] = M1 + (j%4)/(float)4 * (M2-M1);
    }
  }
  for(int i=0; i < width; ++i) {
    for(int j=0; j < height; ++j) {
      grid[i][j] += delta[i][j];
    }
  }

  // Generate 2-scale noise
  for(int i=0; i < width; i += 2) {
    for(int j=0; j < height; j += 2) {
      delta[i][j] = ((float)rand()/RAND_MAX - 0.5)/4.0;
    }
  }
  for(int i=0; i < width; ++i) {
    for(int j=0; j < height; ++j) {
      int li = 2*(i/2);
      int hi = li+2;
      int lj = 2*(j/2);
      int hj = lj+2;
      float LL = delta[li][lj];
      float LH = 0.0;
      float HL = 0.0;
      float HH = 0.0;
      if (hj < height)
        LH = delta[li][hj];
      if (hi < width)
        HL = delta[hi][lj];
      if (hi < width && hj < height)
        HH = delta[hi][hj];
      float M1 = LL + (i%2)/(float)2 * (LH-LL);
      float M2 = HL + (i%2)/(float)2 * (HH-HL);
      delta[i][j] = M1 + (j%2)/(float)2 * (M2-M1);
    }
  }
  for(int i=0; i < width; ++i) {
    for(int j=0; j < height; ++j) {
      grid[i][j] += delta[i][j];
    }
  }

  for(int i=0; i < width; ++i)
    delete delta[i];
  delete[] delta;
}

//void Map::renderTile(float x, float y, float z) {
//   glPushMatrix();
//
//   glTranslated(x, y, z);
//
//   glBegin(GL_TRIANGLES);
//   glNormal3d(0.10,1,0);
//   glVertex3d(0,1.10,0);
//   glVertex3d(1,1,1);
//   glVertex3d(1,1,-1);
//
//   glNormal3d(0,1,-0.10);
//   glVertex3d(0,1.10,0);
//   glVertex3d(1,1,-1);
//   glVertex3d(-1,1,-1);
//
//   glNormal3d(-0.10,1,0);
//   glVertex3d(0,1.10,0);
//   glVertex3d(-1,1,-1);
//   glVertex3d(-1,1,1);
//
//   glNormal3d(0,1,0.10);
//   glVertex3d(0,1.10,0);
//   glVertex3d(-1,1,1);
//   glVertex3d(1,1,1);
//   glEnd();
//
//   glPopMatrix();
//}
//
//void Map::render() {
//   glPushMatrix();
//   glTranslated(-width,0,-height+2);
//
//   for (int i = 0; i < getWidth(); ++i) {
//      for (int j = 0; j < getHeight(); ++j) {
//        renderTile(i * 2, 0, j * 2);
//      }
//   }
//   glPopMatrix();
//
//   glColor3f(0.8,0.4,0.4);
//   float emission[4] = {0.4,0.0,0.0,1.0};
//   glMaterialfv(GL_FRONT, GL_EMISSION, emission);
//   cube(8.0, 1.5, -8.0, 0, 1.0);
//   glColor3f(0.4,0.8,0.4);
//   emission[0] = 0.0;
//   emission[1] = 0.4;
//   glMaterialfv(GL_FRONT, GL_EMISSION, emission);
//   cube(-10.0, 1.5, -8.0, 0, 1.0);
//
//   if (getLives() <= 0) {
//      bool pixels[7][53] = {{0,1,1,1,0, 0, 0,1,1,1,0, 0, 0,1,0,1,0, 0, 1,1,1,1,1, 0, 0,0,0,0,0, 0, 0,1,1,1,0, 0, 1,0,0,0,1, 0, 1,1,1,1,1, 0, 1,1,1,1,0},
//                         {1,0,0,0,1, 0, 1,0,0,0,1, 0, 1,0,1,0,1, 0, 1,0,0,0,0, 0, 0,0,0,0,0, 0, 1,0,0,0,1, 0, 1,0,0,0,1, 0, 1,0,0,0,0, 0, 1,0,0,0,1},
//                         {1,0,0,0,0, 0, 1,0,0,0,1, 0, 1,0,1,0,1, 0, 1,0,0,0,0, 0, 0,0,0,0,0, 0, 1,0,0,0,1, 0, 1,0,0,0,1, 0, 1,0,0,0,0, 0, 1,0,0,0,1},
//                         {1,0,1,1,1, 0, 1,1,1,1,1, 0, 1,0,1,0,1, 0, 1,1,1,1,0, 0, 0,0,0,0,0, 0, 1,0,0,0,1, 0, 1,0,0,0,1, 0, 1,1,1,1,0, 0, 1,1,1,1,0},
//                         {1,0,0,0,1, 0, 1,0,0,0,1, 0, 1,0,1,0,1, 0, 1,0,0,0,0, 0, 0,0,0,0,0, 0, 1,0,0,0,1, 0, 1,0,0,0,1, 0, 1,0,0,0,0, 0, 1,0,1,0,0},
//                         {1,0,0,0,1, 0, 1,0,0,0,1, 0, 1,0,1,0,1, 0, 1,0,0,0,0, 0, 0,0,0,0,0, 0, 1,0,0,0,1, 0, 0,1,0,1,0, 0, 1,0,0,0,0, 0, 1,0,0,1,0},
//                         {1,1,1,1,1, 0, 1,0,0,0,1, 0, 1,0,1,0,1, 0, 1,1,1,1,1, 0, 0,0,0,0,0, 0, 0,1,1,1,0, 0, 0,0,1,0,0, 0, 1,1,1,1,1, 0, 1,0,0,0,1}};
//      glColor3f(0.9,0.9,0.9);
//      glPushMatrix();
//      for (float th=0.0; th <= 271.0; th += 90) {
//        glRotated(th, 0,1,0);
//        for (int i=0; i<53; ++i) {
//           for (int j=0; j<7;++j) {
//              if (pixels[j][i])
//                cube(2.5-0.1*i,4-0.1*j,9.0, 0, 0.1/sqrt(2.0));
//           }
//        }
//      }
//      glPopMatrix();
//   }
//}
//
//int Map::spawnEnemy() {
//   if (spawncount > 0 && currentwave >= 0) {
//      currentwavetime += 16;
//      if (currentwavetime >= wavetime) {
//        currentwavetime -= wavetime;
//        spawncount -= 1;
//        return waves[currentwave][9-spawncount];
//      }
//   }
//   return 0;
//}
//
//void Map::spawnWave()
//{
//   if (spawncount <= 0)
//   {
//      if (currentwave < 8)
//        currentwave += 1;
//      spawncount = 10;
//   }
//}
//
//bool Map::isEmpty(Position pos) {
//   if (pos.first >= width || pos.first < 0 || pos.second >= height || pos.second < 0) {
//      return false;
//   }
//   return map[pos.first][pos.second].tileType == TileType::GROUND;
//}
//
//bool Map::setTower(TileType tower, Position pos) {
//   if (isEmpty(pos)) {
//      map[pos.first][pos.second].tileType = tower;
//      return true;
//   }
//   return false;
//}
//
//Position Map::getGoal()
//{
//   return goal;
//}
//
//std::vector<Position> Map::getNeighbors(Position pos) {
//   std::vector<Position> neighbors;
//   Position up = Position(pos.first - 1, pos.second);
//   Position down = Position(pos.first + 1, pos.second);
//   Position left = Position(pos.first, pos.second - 1);
//   Position right = Position(pos.first, pos.second + 1);
//   if (isEmpty(up)) {
//      neighbors.push_back(up);
//   }
//   if (isEmpty(down)) {
//      neighbors.push_back(down);
//   }
//   if (isEmpty(left)) {
//      neighbors.push_back(left);
//   }
//   if (isEmpty(right)) {
//      neighbors.push_back(right);
//   }
//   return neighbors;
//}
//
//float Map::getHValue(Position cur, Position end) {
//   int dx = cur.first - end.first;
//   int dy = cur.second - end.second;
//   return sqrt(dx * dx + dy * dy);
//}
//
//namespace std {
//
//  template <>
//  struct hash<Position>
//  {
//   std::size_t operator()(const Position& k) const
//   {
//    using std::size_t;
//    using std::hash;
//
//    // Compute individual hash values for first,
//    // second and third and combine them using XOR
//    // and bit shifting:
//
//    return ((hash<int>()(k.first)
//          ^ (hash<int>()(k.second) << 1)) >> 1);
//   }
//  };
//
//}
//
//std::vector<Position> Map::AStar(Position start, Position end) {
//   //std::vector<Position> closed;
//   PriorityQueue<Position, float> open;
//   open.put(start, getHValue(start, end));
//   std::unordered_map<Position, Position> came_from;
//   std::unordered_map<Position, float> cost_so_far;
//   came_from[start] = start;
//   cost_so_far[start] = 0;
//   std::vector<Position> path;
//
//   while (!open.empty()) {
//      auto cur = open.get();
//      //std::cout << cur.first << "\t" << cur.second << std::endl;
//      if (cur == end) {
//        path.push_back(cur);
//        while (cur != start) {
//           cur = came_from[cur];
//           path.push_back(cur);
//        }
//        //path.push_back(start);
//        std::reverse(path.begin(), path.end());
//        return path;
//      }
//      for (auto& next : getNeighbors(cur)) {
//          float new_cost = cost_so_far[cur] + 1;
//          if (!cost_so_far.count(next) || new_cost < cost_so_far[next]) {
//           cost_so_far[next] = new_cost;
//           float priority = new_cost + getHValue(next, end);
//           open.put(next, priority);
//           came_from[next] = cur;
//          }
//      }
//   }
//   return path;
//}
//
//void Map::makeMap() {
//   for(int i = 0; i < width; i++) {
//      for(int j = 0; j < height; j++) {
//        map[i][j].tileType = TileType::GROUND;
//        // if(i == 0 || i == width - 1 || j == 0 || j == height - 1) {
//        //    map[i][j].tileType = TileType::NOTHING;
//        // }
//        // else {
//        //    map[i][j].tileType = TileType::GROUND;
//        // }
//      }
//   }
//}
//
//
//// Score functions
//int Map::getScore() {
//   return score;
//}
//
//void Map::incrementScore(int points) {
//   score += points;
//}
