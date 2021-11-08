#include "data.hpp"
#include <cfloat>
#include <ctime>     // for a random seed
#include <fstream>   // for file-reading
#include <iostream>  // for file-reading
#include <sstream>   // for file-reading
#include <vector>
#include "point.hpp"
Dataset::Dataset():m_path("")
    {

    }
   
   
void Dataset::setPath(std::string path)
{
     this->m_path = path;
}
std::string Dataset::getPath() const
{
    return this->m_path;
}
std::vector<Point> Dataset::readcsv()
{
    std::vector<Point> points;
    std::string line;
    std::ifstream file(getPath());
    std::string header;
    getline(file,header);
    while(getline(file,line))
    {
        std::stringstream linestream(line);      
        std::string bit;
        double x,y;
        getline(linestream,bit,',');
        x=stof(bit);
        getline(linestream,bit,'\n');
        y=stof(bit);
        points.push_back(Point(x,y));

    }
    return points;
}
       