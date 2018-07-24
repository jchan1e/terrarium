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
    for (int i = 0; i < getW(); ++i)
        grid[i] = new std::vector<Ant*>[getH()];
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
    findClusters();
    updateCenterofMass();
    std::cout<<allClusters.size();
    resetAntFound();

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


void Map::findClusters(){
    for(Ant* ant : ants){
        ant->getNeighbors(1);
    }
    for(Ant* ant : ants){
        if(!ant->neighbors.empty()){//ant has neighbors
            if(allClusters.empty()){//case where there are not yet any Clusters
                Cluster* firstCluster = newCluster(ant);
                allClusters.push_back(firstCluster);
            }
            else{//there are clusters
                int size = allClusters.size();
                n = size;
                int *counter = new int[size];
                bool *bCounter = new bool[size];
                
                for(Ant* neighbor : ant->neighbors){
                    int i = 0;
                    for(Cluster* clust : allClusters){

                        if(std::find((clust->clusAnt).begin(), (clust->clusAnt).end(), neighbor) != (clust->clusAnt).end()){
                            counter[i]++;
                        }
                        i++;
                    }
                }
                for(Cluster* clust : allClusters){
                        if(std::find((clust->clusAnt).begin(), (clust->clusAnt).end(), ant) != (clust->clusAnt).end()){
                            ant->setFound(true);
                        }
                    }
                int count = 0;
                bool noCluster = false;
                bool oneCluster = false;
                bool multiCluster = false;
                int k;
                for(int j = 0; j < allClusters.size(); j++){//iterate through our array to see where the neighbors are
                    //count += counter[i];
                    if(counter[j] == (ant->neighbors).size()){//all neighbors are in one cluster,
                        oneCluster = true;
                        k = j;
                    }
                    else if(counter[j] != 0){//not all ants are in one cluster
                        bCounter[j] = true;
                        multiCluster = true;
                    }
                    else{//none of neighbors are in any cluster
                        noCluster = true;
                    }
                }
                if(oneCluster){
                    if(!ant->found){
                        allClusters[k]->clusAnt.push_back(ant);//put our current ant in the cluster with its neighbors
                        ant->setFound(true);
                    }

                }else if(noCluster){
                    if(!ant->found){
                        Cluster* ithCluster = newCluster(ant);//create a new cluster and put ant and neighbors in it
                        allClusters.push_back(ithCluster);
                        ant->setFound(true);
                    }

                }else if(multiCluster){
                    if(!ant->found){
                        Cluster* merged = mergeCluster(bCounter, size);//maybe should be two cases some of the neighbors are in one cluster but not necessarily all have been put in a cluster yet
                        merged->clusAnt.push_back(ant);//however this might take care of this albeit in a slow manner
                        allClusters.push_back(merged);
                        ant->setFound(true);
                    }
                    else{
                        Cluster* merged = mergeCluster(bCounter, size);
                        allClusters.push_back(merged);
                    }

                }
            
                delete[] counter;
                delete[] bCounter;
            }
        }

    }
}

Cluster* Map::newCluster(Ant* ant){
    Cluster* aClus = new Cluster;
    for(Ant* neighbor : ant->neighbors){
        aClus->clusAnt.push_back(neighbor);
    }
    aClus->clusAnt.push_back(ant);
    return aClus;

}

Cluster* Map::mergeCluster(bool *arr, int n){
    Cluster* clus = new Cluster;
    Cluster* temp;
    Ant* temp2;
    for(int i = 0; i < n; i++){
        if(arr[i] == true){//ant has neighbors in the ith cluster
            temp = allClusters[i];
            while(!temp->clusAnt.empty()){
                temp2 = temp->clusAnt.back();
                temp->clusAnt.pop_back();
                clus->clusAnt.push_back(temp2);
            }
             allClusters.erase(allClusters.begin() + i);
            delete temp;
        }
    }

    return clus;
}

void Map::resetAntFound(){
    for(Ant* ant : ants){
        ant->setFound(false);
    }
}

void Map::updateCenterofMass(){
    for(Cluster* cluster : allClusters){
        float xSum = 0;
        float ySum = 0;
        float zSum = 0;
        for(Ant* ant : cluster->clusAnt){
            xSum += ant->getX();
            ySum += ant->getY();
            zSum += ant->getZ();
        }
        int n = cluster->clusAnt.size();
        cluster->x = xSum/n;
        cluster->y = ySum/n;
        cluster->z = zSum/n;
    }
}




