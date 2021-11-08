#pragma once
#define DATASET_FILE_PATH "D:/work/Practice/ML_Algorithms/KMeans/Mall_Customers.csv"
#include <vector>
#include <string>

struct Point;
class Dataset
{
public:
    Dataset();
   
   
   void setPath(std::string path);
   std::string getPath() const;
    //read excel sheet
std::vector<Point> readcsv();

private:
    std::string m_path;

};
