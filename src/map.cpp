#include "map.h"
#include "objects.h"
#include "ant.h"
#include <iostream>

Map::Map(int W, int H, int seed) {
    srand(seed);
    Width = W;
    Height = H;
    heightmap = new float*[Width];
    for(int i=0; i < Width; ++i)
    heightmap[i] = new float[Height];
    grid = new std::vector<Tile>*[Width];
    for (int i = 0; i < Width; ++i)
        grid[i] = new std::vector<Tile>[Height];
    generate();
}

Map::Map(int W, int H) {
    Width = W; //TODO Setters
    Height = H;
    heightmap = new float*[Width];
    for(int i=0; i < Width; ++i)
        heightmap[i] = new float[Height];
    grid = new std::vector<Tile>*[Width];
    for (int i = 0; i < Width; ++i)
        grid[i] = new std::vector<Tile>[Height];
    generate();
}

Map::~Map() {
    for(int i=0; i < Width; ++i) {
        delete heightmap[i];
        delete grid[i];
    }
    delete[] heightmap;
    delete[] grid;
}

void Map::generate() {
    for (int i=0; i < Width; ++i) {
        for (int j=0; j < Height; ++j) {
            heightmap[i][j] = 0.0;
        }
    }
    return;

///////////////////////////////////////////
    // generates Perlin Noise to fill grid

    // Initialize and set all values to 0.0
    float ** delta = new float*[Width];
    for(int i=0; i < Width; ++i) {
        delta[i] = new float[Height];
        for(int j=0; j < Height; ++j) {
            heightmap[i][j]= 0.0;
            delta[i][j] = 0.0;
        }
    }

    // Generate 16-scale noise
    for(int i=0; i < Width; i += 16) {
        for(int j=0; j < Height; j += 16) {
            delta[i][j] = (float)rand()/RAND_MAX - 0.5;
        }
    }
    for(int i=0; i < Width; ++i) {
        for(int j=0; j < Height; ++j) {
            int li = 16*(i/16);
            int hi = li+16;
            int lj = 16*(j/16);
            int hj = lj+16;
            float LL = delta[li][lj];
            float LH = 0.0;
            float HL = 0.0;
            float HH = 0.0;
            if (hj < Height)
            LH = delta[li][hj];
            if (hi < Width)
            HL = delta[hi][lj];
            if (hi < Width && hj < Height)
            HH = delta[hi][hj];
            // lerp
            float M1    = LL + (i-li)/16.0 * (LH-LL);
            float M2    = HL + (i-li)/16.0 * (HH-HL);
            delta[i][j] = M1 + (j-lj)/16.0 * (M2-M1);
        }
    }
    for(int i=0; i < Width; ++i) {
        for(int j=0; j < Height; ++j) {
            heightmap[i][j] += delta[i][j];
        }
    }

    // Generate 8-scale noise
    for(int i=0; i < Width; i += 8) {
        for(int j=0; j < Height; j += 8) {
            delta[i][j] = ((float)rand()/RAND_MAX - 0.5)/2.0;
        }
    }
    for(int i=0; i < Width; ++i) {
        for(int j=0; j < Height; ++j) {
            int li = 8*(i/8);
            int hi = li+8;
            int lj = 8*(j/8);
            int hj = lj+8;
            float LL = delta[li][lj];
            float LH = 0.0;
            float HL = 0.0;
            float HH = 0.0;
            if (hj < Height)
            LH = delta[li][hj];
            if (hi < Width)
            HL = delta[hi][lj];
            if (hi < Width && hj < Height)
            HH = delta[hi][hj];
            float M1 = LL + (i%8)/(float)8 * (LH-LL);
            float M2 = HL + (i%8)/(float)8 * (HH-HL);
            delta[i][j] = M1 + (j%8)/(float)8 * (M2-M1);
        }
    }
    for(int i=0; i < Width; ++i) {
        for(int j=0; j < Height; ++j) {
            heightmap[i][j] += delta[i][j];
        }
    }

    // Generate 4-scale noise
    for(int i=0; i < Width; i += 4) {
        for(int j=0; j < Height; j += 4) {
            delta[i][j] = ((float)rand()/RAND_MAX - 0.5)/4.0;
        }
    }
    for(int i=0; i < Width; ++i) {
        for(int j=0; j < Height; ++j) {
            int li = 4*(i/4);
            int hi = li+4;
            int lj = 4*(j/4);
            int hj = lj+4;
            float LL = delta[li][lj];
            float LH = 0.0;
            float HL = 0.0;
            float HH = 0.0;
            if (hj < Height)
            LH = delta[li][hj];
            if (hi < Width)
            HL = delta[hi][lj];
            if (hi < Width && hj < Height)
            HH = delta[hi][hj];
            float M1 = LL + (i%4)/(float)4 * (LH-LL);
            float M2 = HL + (i%4)/(float)4 * (HH-HL);
            delta[i][j] = M1 + (j%4)/(float)4 * (M2-M1);
        }
    }
    for(int i=0; i < Width; ++i) {
        for(int j=0; j < Height; ++j) {
            heightmap[i][j] += delta[i][j];
        }
    }

    // Generate 2-scale noise
    for(int i=0; i < Width; i += 2) {
        for(int j=0; j < Height; j += 2) {
            delta[i][j] = ((float)rand()/RAND_MAX - 0.5)/4.0;
        }
    }
    for(int i=0; i < Width; ++i) {
        for(int j=0; j < Height; ++j) {
            int li = 2*(i/2);
            int hi = li+2;
            int lj = 2*(j/2);
            int hj = lj+2;
            float LL = delta[li][lj];
            float LH = 0.0;
            float HL = 0.0;
            float HH = 0.0;
            if (hj < Height)
            LH = delta[li][hj];
            if (hi < Width)
            HL = delta[hi][lj];
            if (hi < Width && hj < Height)
            HH = delta[hi][hj];
            float M1 = LL + (i%2)/(float)2 * (LH-LL);
            float M2 = HL + (i%2)/(float)2 * (HH-HL);
            delta[i][j] = M1 + (j%2)/(float)2 * (M2-M1);
        }
    }
    for(int i=0; i < Width; ++i) {
        for(int j=0; j < Height; ++j) {
            heightmap[i][j] += delta[i][j];
            heightmap[i][j] = heightmap[i][j]*3;
        }
    }

    // Initialize tile grid
    grid = new std::vector<Tile>* ;
    for(int i=0; i < Width; ++i) {
        grid[i] = new std::vector<Tile>[Height];
    }

    //for(int i=0; i < Width; ++i)
    //  delete delta[i];
    delete[] delta;
}

void Map::animate() {
    updateHeights(.5);
}

void Map::render() {
    glPushMatrix();
    //glScalef(1,1,3);

    for (int i=0; i < Width; ++i) {
        for (int j=0; j < Height; ++j) {
            float corners[4];
            corners[0] = heightmap[i][j];
            float n = 1.0;
            if (i > 0 && j > 0) {
                corners[0] = (corners[0]*n + heightmap[i-1][j-1]) / (n+1.0);
                n += 1.0;
            }
            if (i > 0) {
                corners[0] = (corners[0]*n + heightmap[i-1][j]) / (n+1.0);
                n += 1.0;
            }
            if (j > 0) {
                corners[0] = (corners[0]*n + heightmap[i][j-1]) / (n+1.0);
            }

            corners[1] = heightmap[i][j];
            n = 1.0;
            if (i > 0 && j < Height-1) {
                corners[1] = (corners[1]*n + heightmap[i-1][j+1]) / (n+1.0);
                n += 1.0;
            }
            if (i > 0) {
                corners[1] = (corners[1]*n + heightmap[i-1][j]) / (n+1.0);
                n += 1.0;
            }
            if (j < Height-1) {
                corners[1] = (corners[1]*n + heightmap[i][j+1]) / (n+1.0);
            }

            corners[2] = heightmap[i][j];
            n = 1.0;
            if (i < Width-1 && j < Height-1) {
                corners[2] = (corners[2]*n + heightmap[i+1][j+1]) / (n+1.0);
                n += 1.0;
            }
            if (i < Width-1) {
                corners[2] = (corners[2]*n + heightmap[i+1][j]) / (n+1.0);
                n += 1.0;
            }
            if (j < Height-1) {
                corners[2] = (corners[2]*n + heightmap[i][j+1]) / (n+1.0);
            }

            corners[3] = heightmap[i][j];
            n = 1.0;
            if (i < Width-1 && j > 0) {
                corners[3] = (corners[3]*n + heightmap[i+1][j-1]) / (n+1.0);
                n += 1.0;
            }
            if (i < Width-1) {
                corners[3] = (corners[3]*n + heightmap[i+1][j]) / (n+1.0);
                n += 1.0;
            }
            if (j > 0) {
                corners[3] = (corners[3]*n + heightmap[i][j-1]) / (n+1.0);
            }

            float centerw = -Width/2;
            float centerh = -Height/2;
            //float centerd = (corners[0]+corners[1]+corners[2]+corners[3])/4;
            float normx = (corners[0]+corners[1]-corners[2]-corners[3])/4;
            float normy = (corners[0]-corners[1]-corners[2]+corners[3])/4;
            float normz = 1.0;
            glColor3f(0.5,0.6,0.6);
            glBegin(GL_TRIANGLE_FAN);
            glNormal3f(0.0, 0.0, 1.0);
            glVertex3f(i+centerw,     j+centerh,     0.0);
            glVertex3f(i+centerw-0.5, j+centerh-0.5, 0.0);
            glVertex3f(i+centerw+0.5, j+centerh-0.5, 0.0);
            glVertex3f(i+centerw+0.5, j+centerh+0.5, 0.0);
            glVertex3f(i+centerw-0.5, j+centerh+0.5, 0.0);
            glVertex3f(i+centerw-0.5, j+centerh-0.5, 0.0);
            //glNormal3f(normx, normy, normz);
            //glVertex3f(i+centerw,     j+centerh,     centerd);
            //glVertex3f(i+centerw-0.5, j+centerh-0.5, corners[0]);
            //glVertex3f(i+centerw+0.5, j+centerh-0.5, corners[3]);
            //glVertex3f(i+centerw+0.5, j+centerh+0.5, corners[2]);
            //glVertex3f(i+centerw-0.5, j+centerh+0.5, corners[1]);
            //glVertex3f(i+centerw-0.5, j+centerh-0.5, corners[0]);
            glEnd();
            //std::cout << i+centerw << " " << j+centerh << std::endl;
        }
    }
    glPopMatrix();
}

float lerp(float x0, float x1, float w) {
    return (1-w)*x0 + w*x1;
}

float Map::getHeight(float x, float y) {
    if (x < 0 || y < 0 || x >= Width-1 || y >= Height-1)
    return 0.0;
    int x0 = floor(x);
    int y0 = floor(y);
    int x1 = ceil(x);
    int y1 = ceil(y);
    float h0 = lerp(heightmap[x0][y0], heightmap[x0][y1], y-y0);
    float h1 = lerp(heightmap[x1][y0], heightmap[x1][y1], y-y0);
    return lerp(h0, h1, x-x0);
}

//int Map::getState(int x, int y) {
//}

void Map::getNeighbors(float x, float y, float radius, std::vector<Ant*>* neighbors){

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

    float difx, dify, dist;

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

        dist = sqrt(difx*difx + dify*dify);

        if ( dist <= radius && dist != 0 ) {
            neighbors->push_back(ant);
        }
    }
}

void Map::addAnt(Ant* ant) {
    ants.push_back(ant);
}

int Map::getH() { return Height; }
int Map::getW() { return Width; }

void Map::setTile(int x, int y, bool lock) {

    if (lock) {
        Tile T;
        grid[x][y].push_back(T);
    } else {
        grid[x][y].pop_back();
    }

}

void Map::updateHeights(float antsize) {
    for (int i = 0; i < getW(); i++) {
        for (int j = 0; j < getH(); j++) {
            heightmap[i][j] = grid[i][j].size() * antsize;
        }
    }
}
