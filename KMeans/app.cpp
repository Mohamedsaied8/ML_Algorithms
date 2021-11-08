#include "kmeans.hpp"
int main()
{
    int epochs =100,k=5; 
    Kmeans kmeans(DATASET_FILE_PATH,epochs,k);
    kmeans.run();
    kmeans.save();
    
    return 0;
}