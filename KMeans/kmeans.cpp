/*
    Learned from : https://reasonabledeviations.com/2019/10/02/k-means-in-cpp/

*/

#include <ctime>     // for a random seed
#include <fstream>   // for file-reading
#include <iostream>  // for file-reading
#include <sstream>   // for file-reading
#include <limits.h>
#include <cfloat>
#include <vector>

using namespace std;

struct Point
{

    Point():x(0.0),
           y(0.0),
           minDist(DBL_MAX),
           cluster(-1)
    {
        
    }
      Point(double x,double y):x(x),
      y(y),
      minDist(DBL_MAX),
      cluster(-1)
    {
        
    }
    double distance(Point p)
    {
        return (((p.x-x)*(p.x-x)) + ((p.y-y)*(p.y-y)));
    }

double x,y,minDist,cluster;
};
vector<Point> readcsv();
void kMeansClustering(vector<Point>* points, int epochs,int k);

void kMeansClustering(vector<Point>* points, int epochs,int k)
{
    int n=points->size();
    //initalize clusters
    vector<Point> centroids;
    srand(time(0));
    for(int i=0;i<k;i++)
        centroids.push_back(points->at(rand() % n));

    for(int i= 0; i<epochs; i++)
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
        for(int j=0;j<k;j++)
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
    ofstream myfile;
    myfile.open("output.csv");
    myfile << "x,y,c" << endl;
    for(vector<Point>::iterator it=points->begin();it!=points->end();it++)
    {
        myfile << it->x <<"," << it->y << "," << it->cluster << endl;
    }
    myfile.close();
  
}
//read excel sheet
vector<Point> readcsv()
{
    vector<Point> points;
    string line;
    ifstream file("D:/work/Practice/ML_Algorithms/Mall_Customers.csv");
    string header;
    getline(file,header);
    while(getline(file,line))
    {
        stringstream linestream(line);      
        string bit;
        double x,y;
        getline(linestream,bit,',');
        x=stof(bit);
        getline(linestream,bit,'\n');
        y=stof(bit);
        points.push_back(Point(x,y));

    }
       
    return points;
}

int main()
{
    int epochs =100,k=5;
    vector<Point> points = readcsv();  // read from file
 

    kMeansClustering(&points,epochs,k);          // pass values to function
    
    return 0;
}