#include "map.h"
#include "objects.h"
#include "ant.h"
#include <iostream>


//Ctor and helper
Map::Map(int W, int H) {
    setW(W);
    setH(H);
    elevationmap = new float*[getW()];

    for(int i=0; i < getW(); ++i)
        elevationmap[i] = new float[getH()];

    grid = new std::vector<Ant*>*[getW()];
    topoMap = new int*[getW()];
    foundMap = new bool*[getW()];
    for (int i = 0; i < getW(); ++i){
        grid[i] = new std::vector<Ant*>[getH()];
        topoMap[i] = new int[getH()];
        foundMap[i] = new bool[getH()];
    }
    generate();
}

void Map::generate() {
    for (int i=0; i < getW(); ++i) {
        for (int j=0; j < getH(); ++j) {
            elevationmap[i][j] = 0.0;
        }
    }
    elevationmap[getW()/2][getH()/2] = 50;
    elevationmap[getW()/2+1][getH()/2] = 50;
    elevationmap[getW()/2][getH()/2+1] = 50;
    elevationmap[getW()/2+1][getH()/2+1] = 50;
    return;
}


//Dtor
Map::~Map() {
    for(int i=0; i < getW(); ++i) {
        delete elevationmap[i];
        delete grid[i];
    }
    delete[] elevationmap;
    delete[] grid;
}




//Interface Methods and helper
void Map::animate() {
    updateTopo();
    resetFound();
}

void Map::render() {
    glPushMatrix();
    //glScalef(1,1,3);
    for (int i=0; i < getW(); ++i) {
        for (int j=0; j < getH(); ++j) {
            float corners[4];
            corners[0] = elevationmap[i][j];
            float n = 1.0;
            if (i > 0 && j > 0) {
                corners[0] = (corners[0]*n + elevationmap[i-1][j-1]) / (n+1.0);
                n += 1.0;
            }
            if (i > 0) {
                corners[0] = (corners[0]*n + elevationmap[i-1][j]) / (n+1.0);
                n += 1.0;
            }
            if (j > 0) {
                corners[0] = (corners[0]*n + elevationmap[i][j-1]) / (n+1.0);
            }

            corners[1] = elevationmap[i][j];
            n = 1.0;
            if (i > 0 && j < getH()-1) {
                corners[1] = (corners[1]*n + elevationmap[i-1][j+1]) / (n+1.0);
                n += 1.0;
            }
            if (i > 0) {
                corners[1] = (corners[1]*n + elevationmap[i-1][j]) / (n+1.0);
                n += 1.0;
            }
            if (j < getH()-1) {
                corners[1] = (corners[1]*n + elevationmap[i][j+1]) / (n+1.0);
            }

            corners[2] = elevationmap[i][j];
            n = 1.0;
            if (i < getW()-1 && j < getH()-1) {
                corners[2] = (corners[2]*n + elevationmap[i+1][j+1]) / (n+1.0);
                n += 1.0;
            }
            if (i < getW()-1) {
                corners[2] = (corners[2]*n + elevationmap[i+1][j]) / (n+1.0);
                n += 1.0;
            }
            if (j < getH()-1) {
                corners[2] = (corners[2]*n + elevationmap[i][j+1]) / (n+1.0);
            }

            corners[3] = elevationmap[i][j];
            n = 1.0;
            if (i < getW()-1 && j > 0) {
                corners[3] = (corners[3]*n + elevationmap[i+1][j-1]) / (n+1.0);
                n += 1.0;
            }
            if (i < getW()-1) {
                corners[3] = (corners[3]*n + elevationmap[i+1][j]) / (n+1.0);
                n += 1.0;
            }
            if (j > 0) {
                corners[3] = (corners[3]*n + elevationmap[i][j-1]) / (n+1.0);
            }

            float centerw = -getW()/2;
            float centerh = -getH()/2;
            //float centerd = (corners[0]+corners[1]+corners[2]+corners[3])/4;
            float normx = (corners[0]+corners[1]-corners[2]-corners[3])/4;
            float normy = (corners[0]-corners[1]-corners[2]+corners[3])/4;
            float normz = 1.0;
            glColor3f(0.53, 0.73, 0.64);
            glBegin(GL_TRIANGLE_FAN);
            glNormal3f(0.0, 0.0, 1.0);
            glVertex3f(i+centerw,     j+centerh,     0.0);
            glVertex3f(i+centerw-0.5, j+centerh-0.5, 0.0);
            glVertex3f(i+centerw+0.5, j+centerh-0.5, 0.0);
            glVertex3f(i+centerw+0.5, j+centerh+0.5, 0.0);
            glVertex3f(i+centerw-0.5, j+centerh+0.5, 0.0);
            glVertex3f(i+centerw-0.5, j+centerh-0.5, 0.0);

            // //glNormal3f(normx, normy, normz);
            // //glVertex3f(i+centerw,     j+centerh,     centerd);
            // //glVertex3f(i+centerw-0.5, j+centerh-0.5, corners[0]);
            // //glVertex3f(i+centerw+0.5, j+centerh-0.5, corners[3]);
            // //glVertex3f(i+centerw+0.5, j+centerh+0.5, corners[2]);
            // //glVertex3f(i+centerw-0.5, j+centerh+0.5, corners[1]);
            // //glVertex3f(i+centerw-0.5, j+centerh-0.5, corners[0]);
            glEnd();
            //std::cout << i+centerw << " " << j+centerh << std::endl;
        }
    }

    glPopMatrix();
}

float lerp(float x0, float x1, float w) {
    return (1-w)*x0 + w*x1;
}



//Getters
int Map::getH() { return Height; }
int Map::getW() { return Width; }

float Map::getElevation(float x, float y) {
    if (x < 0 || y < 0 || x >= getW()-2 || y >= getH()-2) return 0.0;
    int x0 = floor(x);
    int y0 = floor(y);
    return elevationmap[x0][y0];
    // int x1 = ceil(x);
    // int y1 = ceil(y);
    // float h0 = lerp(elevationmap[x0][y0], elevationmap[x0][y1], y-y0);
    // float h1 = lerp(elevationmap[x1][y0], elevationmap[x1][y1], y-y0);
    // return lerp(h0, h1, x-x0);
}


//Setters
void Map::setH(int H) { Height = H; }
void Map::setW(int W) { Width = W; }


//For interacting with ants
void Map::getNeighbors(float x, float y, float z, float radius, std::vector<Ant*>* neighbors){
    //Check if ant is near any of the sides
    bool top = false, bottom = false, left = false, right = false;
    float leftRight, topBottom;
    float h = getH();
    float w = getW();
    if (h - x < radius) {
        top = true;
        topBottom = h - x;
    } else if ( x < radius) {
        bottom = true;
        topBottom = x;
    } if ( w - y < radius) {
        left = true;
        leftRight = w - y;
    } else if ( y < radius ) {
        right = true;
        leftRight = y;
    }

    float difx, dify, difz, dist;

    for (Ant* ant : ants) {
        if (top && ant->getX() < radius - topBottom) {
            difx = topBottom + ant->getX();
        } else if (bottom && h - ant->getX() < radius - topBottom) {
            difx = topBottom + h - ant->getX();
        } else {
            difx = x - ant->getX();
        } if (left && ant->getY() < radius - leftRight) {
            dify = leftRight + ant->getY();
        } else if (right && w - ant->getY() < radius - leftRight) {
            dify = leftRight + w - ant->getY();
        } else {
            dify = y - ant->getY();
        }
        difz = z - ant->getZ();
        dist = sqrt(difx*difx + dify*dify + difz*difz);

        if ( dist <= radius && dist != 0 ) {
            neighbors->push_back(ant);
        }
    }
}

void Map::addAnt(Ant* ant) {
    ants.push_back(ant);
}

void Map::setTile(Ant* ant, float antsize, bool lock) {
    int x = floor(ant->getX());
    int y = floor(ant->getY());

    if (lock) {
        ant->lock();
        //grid[x][y].push_back(ant);
        grid[x][y].insert(grid[x][y].begin(), ant);
        elevationmap[x][y] = grid[x][y].size() * antsize;
    } else {
        if (!grid[x][y].empty()){
            Ant* target = grid[x][y].front();
            // grid[x][y].pop_back();
            grid[x][y].erase(grid[x][y].begin());
            elevationmap[x][y] = grid[x][y].size() * antsize;
            target->unlock();
            target->setZ(getElevation(x,y));

        }
    }
    elevationmap[getW()/2][getH()/2] = 50;
    elevationmap[getW()/2+1][getH()/2] = 50;
    elevationmap[getW()/2][getH()/2+1] = 50;
    elevationmap[getW()/2+1][getH()/2+1] = 50;
}

void Map::updateTopo(){
    for(int i = 0; i < getW(); ++i){
        for(int j = 0; j < getH(); ++j){
            topoMap[i][j] = grid[i][j].size();
        }
    }
}

void Map::resetFound(){
    for(int i = 0; i < getW(); ++i){
        for(int j = 0; j < getH(); ++j){
            foundMap[i][j] = false;
        }
    }
}

point* Map::findTallest(){
    point* max = new point;
    int maxH = 0;
    for(int i = 0; i < getW(); ++i){
        for(int j = 0; j < getH(); ++j){
            if(topoMap[i][j]>maxH && !foundMap[i][j]){
                max->x = i;
                max->y = j;
                maxH = topoMap[i][j];
            }
        }
    }
    return max;
}

void Map::updateFound(point* val){
    foundMap[val->x][val->y] = true;
}

void Map::bfsTowers(point* maxTower, std::queue<point*> towerFound){//bfs implementation for searching topoMap
    towerFound.push(maxTower);
    updateFound(maxTower);
    while(!towerFound.empty()){
        towerFound.pop();
        towerVec.push_back(maxTower); //add to growing vector of single ant towers

        bool top = false, bottom = false, left = false, right = false;
        int h = getH();
        int w = getW();
        point* t1 = new point;
        point* t2 = new point; 
        point* t3 = new point;
        point* t4 = new point;
        if (maxTower->y >= h-1) {
            top = true;
        } else if ( maxTower->y <= 0) {
            bottom = true;
        } if ( maxTower->x <= 0) {
            left = true;
        } else if ( maxTower->x >= w-1) {
            right = true;
        }
        t1->x = maxTower->x;
        t1->y = maxTower->y += 1;
        t2->x = maxTower->x += 1;
        t2->y = maxTower->y;
        t3->x = maxTower->x;
        t3->y = maxTower->y -= 1;
        t4->x = maxTower->x -= 1;
        t4->y = maxTower->y;
        if(top){
            t1->y = 0;
        }else if(bottom){
            t3->y = h-1;
        }
        if(left){
            t4->x = w-1;
        }else if(right){ //not sure if we want if and elseif staments
            t2->x = 0;
        }
        if(!foundMap[t1->x][t1->y] && topoMap[t1->x][t1->y]>0) //do you think there is a better way to do this other than 4 ifs
            bfsTowers(t1, towerFound);
        if(!foundMap[t2->x][t2->y] && topoMap[t2->x][t2->y]>0)
            bfsTowers(t2, towerFound);
        if(!foundMap[t3->x][t3->y] && topoMap[t3->x][t3->y]>0)
            bfsTowers(t3, towerFound);
        if(!foundMap[t4->x][t4->y] && topoMap[t4->x][t4->y]>0)
            bfsTowers(t4, towerFound);
    }
}
