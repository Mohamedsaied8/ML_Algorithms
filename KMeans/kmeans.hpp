/*
    Learned from : https://reasonabledeviations.com/2019/10/02/k-means-in-cpp/

*/
#pragma once

#include <limits.h>
#include <cfloat>
#include <vector>
#include <memory>
#include "data.hpp"
#include "point.hpp"
#include <string>
#include <time.h>

class Kmeans
{
public:
explicit Kmeans(std::string dataset_file,int epochs , int k);
void setK(int k);
void setEpochs(int epochs);
void run();
void save();
~Kmeans();
private:
    int m_epochs;
    int m_k;
    std::vector<Point> centroids;
    std::vector<Point> * points;
    std::unique_ptr<Dataset> dataset;
};
