#include "map.h"

Map::Map()
{
//    int newarr[81] = {0, 0, 0, 0, 0, 0, 0, 0, 0,  // it's a 2nd order Hilbert curve
//                          -1,-1,-1,-1, 0,-1,-1,-1,-1,
//                            0, 0, 0,-1, 0,-1, 0, 0, 0,
//                            0,-1,-1,-1, 0,-1,-1,-1, 0,
//                            0,-1, 0, 0, 0, 0, 0,-1, 0,
//                            0,-1, 0,-1,-1,-1, 0,-1, 0,
//                            0,-1, 0,-1, 0,-1, 0,-1, 0,
//                            0,-1,-1,-1, 0,-1,-1,-1, 0,
//                            0, 0, 0, 0, 0, 0, 0, 0, 0};
//    arr = newarr;

}

void Map::renderTile(float x, float y, float z)
{
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
    glTranslated(-8,0,-8);

    for (int i = 0; i < map.getWidth(); ++i) {
        for (int j = 0; j < map.getHeight(); ++j) {
            renderTile(i * 2, 0, j * 2);
        }
    }
    glPopMatrix();

    if (getLives() > 0) {
        glColor3f(0.4,0.8,0.4);
        float emission[4] = {0.0,0.4,0.0,1.0};
        glMaterialfv(GL_FRONT, GL_EMISSION, emission);
        for (int i = 0; i < lives; ++i) {
            if (i < 2) {
                cube(8.5, 1.5*i, -6.0, 0, 1.0);
            }
            else {
                cube(10.0, 1.5*(i%2), -6.0 + 1.5*((i-2)/2), 0, 1.0);
            }
        }
    }
    else {
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

int Map::getlocation(float ex, float ey)
{
    int ix = (int)ex/2 + 4;
    int iy = -(int)ey/2 + 4;
    if (iy > 8 || iy < 0 || ix > 8 || ix < 0)
        return -1;
    return arr[9*iy + ix];
}
