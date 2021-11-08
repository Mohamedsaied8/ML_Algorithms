/*
    Learned from : https://reasonabledeviations.com/2019/10/02/k-means-in-cpp/

    My Review:
        Save function shouldn't be in the Kmeans class
        Use dependency injection with dataset handler inside Kmeans 
        Apply SOLID principles 
        Kmeans.run is too big, should be split into several functions such as:
            initialize()
            update()


*/

#include <limits.h>
#include <cfloat>
#include <vector>
#include <memory>
#include "data.hpp"
#include <string>
#include "kmeans.hpp"
#include <fstream>   // for file-reading
#include <iostream>
using namespace std;

Kmeans::Kmeans(string dataset_file,int epochs , int k):m_epochs(epochs),m_k(k)
{
    dataset = make_unique<Dataset>();
    dataset->setPath(dataset_file);
    *points = dataset->readcsv();
    int n=points->size();
    //initalize clusters
   srand(time(0));
    for(int i=0;i<m_k;i++)
    {

       centroids.push_back(points->at(rand() % n));

    }
}
Kmeans::~Kmeans()
{

}
 void Kmeans::setK(int k)
 {
     this->m_k = k;
 }
 void Kmeans::setEpochs(int epochs)
 {
     this->m_epochs = epochs;
 }
 void Kmeans::run()
 {
    for(int i= 0; i < m_epochs; i++)
    {
        for(vector<Point>::iterator c = begin(centroids); c!=end(centroids); ++c )
        {
            int clusterId = c - begin(centroids);
            for(vector<Point>::iterator it=points->begin(); it!=points->end();++it)
            {
                Point p = *it;
                double dist = c->distance(p);
                if(dist<p.minDist)
                {
                    p.minDist = dist;
                    p.cluster = clusterId;
                }
                *it = p;
            }
        
        }  
        vector<int> nPoints;
        vector<double> sumX,sumY;
        for(int j=0;j<m_k;j++)
        {
            nPoints.push_back(0);
            sumX.push_back(0);
            sumY.push_back(0);
        }  

        for(vector<Point>::iterator it= points->begin(); it!=points->end();
                                    it++)
            {
                int clusterId = it->cluster;
                nPoints[clusterId] += 1;
                sumX[clusterId] += it->x;
                sumY[clusterId] += it->y;
                it->minDist = DBL_MAX; //reset distance
            }
            //Compute new centroids
        for(vector<Point>::iterator c = begin(centroids); c!=end(centroids);c++)
        {
            int clusterId = c - begin(centroids);
            
            c->x = sumX[clusterId] / nPoints[clusterId];
            c->y = sumY[clusterId] / nPoints[clusterId];
        }
    }  
 }

 void Kmeans::save()
 {
    ofstream myfile;
    myfile.open("output_c.csv");
    myfile << "Income,Spend,Cluster" << endl;
    for(vector<Point>::iterator it=points->begin();it!=points->end();it++)
    {
        myfile << it->x <<"," << it->y << "," << it->cluster << endl;
    }
    myfile.close();
  
 }
