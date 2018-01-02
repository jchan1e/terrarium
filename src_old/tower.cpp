#include "tower.h"

Tower::Tower(float X, float Y, bool mode)
{
    x = X;
    y = Y;
    z = 3.0;
    dx = 1.0;
    dy = 0.0;
    dz = 0.0;
    maxcooldown = 500;
    cooldown = 0;
    target = NULL;
    range = 8.0;
    wireframe = mode;
}

void Tower::animate()
{
    if (!wireframe && target != NULL)
    {
        dx = x - (*target)->x;
        dy = y - (*target)->y;
        dz = z - (*target)->z;
    }
}

void Tower::render()
{
    if (!wireframe)
    {
        float emission[] = {0.0,0.0,0.0,1.0};
        glMaterialfv(GL_FRONT, GL_EMISSION, emission);
        glColor3f(0.25,0.25,0.3);
        octahedron(x,1    ,-y, 0, 1);
        octahedron(x,1.5 ,-y, 0, 0.75);
        octahedron(x,2.0 ,-y, 0, 0.625);
        octahedron(x,2.5 ,-y, 0, 0.5);

        float W0 = sqrt(dx*dx + dy*dy + dz*dz);
        float X0 = dx/W0;
        float Y0 = dy/W0;
        float Z0 = dz/W0;

        float W2 = sqrt(Y0*Y0 + X0*X0);
        float X2 = Y0/W2;
        float Y2 = -X0/W2;
        float Z2 = 0;

        //float W1;
        float X1 = Y2*Z0 - Y0*Z2;
        float Y1 = Z2*X0 - Z0*X2;
        float Z1 = X2*Y0 - X0*Y2;

        float mat[16];
        mat[0] = X0;    mat[4] = X1;     mat[8] = X2;    mat[12] = 0;
        mat[1] = Z0;    mat[5] = Z1;     mat[9] = Z2;    mat[13] = 0;
        mat[2] =-Y0;    mat[6] =-Y1;     mat[10]=-Y2;    mat[14] = 0;
        mat[3] = 0;     mat[7] = 0;      mat[11] = 0;    mat[15] = 1;

        glPushMatrix();
        glTranslated(x,3.0,-y);
        glMultMatrixf(mat);
        glScaled(1/3.0, 1/3.0, 1/3.0);

        emission[0] = 0.5; emission[1] = 0.5; emission[2] = 0.55;
        glMaterialfv(GL_FRONT, GL_EMISSION, emission);
        glColor3f(0.6,0.6,0.6);
        //octahedron(x,3.0 ,-y, 0, 0.4);

        glBegin(GL_TRIANGLES);
        glNormal3f(1.0, 1.0, 1.0);
        glVertex3f(1,0,0);
        glVertex3f(0,1,0);
        glVertex3f(0,0,1);

        glNormal3f(-1.0/2, 1.0, 1.0);
        glVertex3f(0,1,0);
        glVertex3f(-2,0,0);
        glVertex3f(0,0,1);

        glNormal3f(-1.0/2, -1.0, 1.0);
        glVertex3f(-2,0,0);
        glVertex3f(0,-1,0);
        glVertex3f(0,0,1);

        glNormal3f(1.0, -1.0, 1.0);
        glVertex3f(0,-1,0);
        glVertex3f(1,0,0);
        glVertex3f(0,0,1);

        glNormal3f(1.0, 1.0, -1.0);
        glVertex3f(0,1,0);
        glVertex3f(1,0,0);
        glVertex3f(0,0,-1);

        glNormal3f(-1.0/2, 1.0, -1.0);
        glVertex3f(-2,0,0);
        glVertex3f(0,1,0);
        glVertex3f(0,0,-1);

        glNormal3f(-1.0/2, -1.0, -1.0);
        glVertex3f(0,-1,0);
        glVertex3f(-2,0,0);
        glVertex3f(0,0,-1);

        glNormal3f(1.0, -1.0, -1.0);
        glVertex3f(1,0,0);
        glVertex3f(0,-1,0);
        glVertex3f(0,0,-1);
        glEnd();

        glPopMatrix();
    }
    else
    {
        float emission[] = {0.0,0.0,0.0,1.0};
        glMaterialfv(GL_FRONT, GL_EMISSION, emission);
        glColor3f(0.25,0.65,0.3);
        octahedron(x,1,-y, 0, 1.05);
    }
}

Bullet* Tower::fire()
{
    Bullet* bullet = new Bullet(x, y, 3.0, target);
    return bullet;
}

float Tower::distance(Enemy** Target)
{
    return sqrt(((*Target)->x - x) * ((*Target)->x - x)
                 + ((*Target)->y - y) * ((*Target)->y - y)
                 + ((*Target)->z - 0) * ((*Target)->z - 0));
}

Bullet::Bullet(float X, float Y, float Z, Enemy** Target)
{
    x = X;
    y = Y;
    z = Z;
    target = Target;
    dmg = 4;
    speed = 0.25;
}

void Bullet::render()
{
    float W0 = sqrt(dx*dx + dy*dy + dz*dz);
    float X0 = dx/W0;
    float Y0 = dy/W0;
    float Z0 = dz/W0;

    float W2 = sqrt(Y0*Y0 + X0*X0);
    float X2 = Y0/W2;
    float Y2 = -X0/W2;
    float Z2 = 0;

    //float W1;
    float X1 = Y2*Z0 - Y0*Z2;
    float Y1 = Z2*X0 - Z0*X2;
    float Z1 = X2*Y0 - X0*Y2;

    float mat[16];
    mat[0] = X0;    mat[4] = X1;     mat[8] = X2;    mat[12] = 0;
    mat[1] = Z0;    mat[5] = Z1;     mat[9] = Z2;    mat[13] = 0;
    mat[2] =-Y0;    mat[6] =-Y1;     mat[10]=-Y2;    mat[14] = 0;
    mat[3] = 0;     mat[7] = 0;      mat[11] = 0;    mat[15] = 1;

    float emission[] = {0.0, 0.0, 0.0, 1.0};
    glColor3f(0.9,0.9,0.3);
    emission[0] = 0.6; emission[1] = 0.6; emission[2] = 0.0;
    glMaterialfv(GL_FRONT, GL_EMISSION, emission);
    //ball(x, z, -y, 0.125);
    
    glPushMatrix();
    glTranslatef(x, z, -y);
    glMultMatrixf(mat);
    glScaled(0.25,0.25,0.25);

    glBegin(GL_TRIANGLES);
    glNormal3f(1.0/2, 1.0, 1.0);
    glVertex3f(2,0,0);
    glVertex3f(0,1,0);
    glVertex3f(0,0,1);

    glNormal3f(-1.0/2, 1.0, 1.0);
    glVertex3f(0,1,0);
    glVertex3f(-2,0,0);
    glVertex3f(0,0,1);

    glNormal3f(-1.0/2, -1.0, 1.0);
    glVertex3f(-2,0,0);
    glVertex3f(0,-1,0);
    glVertex3f(0,0,1);

    glNormal3f(1.0/2, -1.0, 1.0);
    glVertex3f(0,-1,0);
    glVertex3f(2,0,0);
    glVertex3f(0,0,1);

    glNormal3f(1.0/2, 1.0, -1.0);
    glVertex3f(0,1,0);
    glVertex3f(2,0,0);
    glVertex3f(0,0,-1);

    glNormal3f(-1.0/2, 1.0, -1.0);
    glVertex3f(-2,0,0);
    glVertex3f(0,1,0);
    glVertex3f(0,0,-1);

    glNormal3f(-1.0/2, -1.0, -1.0);
    glVertex3f(0,-1,0);
    glVertex3f(-2,0,0);
    glVertex3f(0,0,-1);

    glNormal3f(1.0/2, -1.0, -1.0);
    glVertex3f(2,0,0);
    glVertex3f(0,-1,0);
    glVertex3f(0,0,-1);
    glEnd();

    glPopMatrix();
}

void Bullet::animate()
{
    normalizeV();
    dx *= speed;
    dy *= speed;
    dz *= speed;
    x += dx;
    y += dy;
    z += dz;
}

void Bullet::collide()
{
    (*target)->damage(dmg);
}

float Bullet::distance()
{
    return sqrt(((*target)->x - x) * ((*target)->x - x)
                 + ((*target)->y - y) * ((*target)->y - y)
                 + ((*target)->z - z) * ((*target)->z - z));
}

void Bullet::normalizeV()
{
    float a = distance();
    dx = ((*target)->x - x)/a;
    dy = ((*target)->y - y)/a;
    dz = ((*target)->z - z)/a;
}

