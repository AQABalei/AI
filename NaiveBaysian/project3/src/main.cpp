#include <iostream>
#include <vector>
#include <map>
#include "mnist_reader.hpp"
#include "mnist_utils.hpp"
#include "bitmap.hpp"
#include <sstream>
#include <cmath>
#include <climits>
#include <fstream>
#define MNIST_DATA_DIR "../mnist_data"

using namespace std;
int main(int argc, char* argv[]) {
    ofstream network;
    ofstream summary;
    //Read in the data set from the files
    mnist::MNIST_dataset<std::vector, std::vector<uint8_t>, uint8_t> dataset =
    mnist::read_dataset<std::vector, std::vector, uint8_t, uint8_t>(MNIST_DATA_DIR);
    //Binarize the data set (so that pixels have values of either 0 or 1)
    mnist::binarize_dataset(dataset);
    // get training images
    vector<std::vector<unsigned char>> trainImages = dataset.training_images;
    // get training labels
    vector<unsigned char> trainLabels = dataset.training_labels;
    // get test images
    vector<std::vector<unsigned char>> testImages = dataset.test_images;
    // get test labels
    vector<unsigned char> testLabels = dataset.test_labels;
    double ten[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    for(int i=0; i<trainLabels.size(); ++i){
        ten[static_cast<int>(trainLabels[i])]++;
    }
    //get the prior probabilities for each class 1,2,3....10
    double prior_probability[10];
    for(int i=0; i<10; ++i){
        prior_probability[i] = ten[i]/trainLabels.size();
    }
    double t = 0;
    for(int i=0; i<10; ++i){
        t += prior_probability[i];
    }
    //For each pixelFj for j∈{0,...,783} and for each class 
    //c ∈ {0,1,2,3,4,5,6,7,8,9}, determine P (Fj = 1|C = c), 
    //the probability that pixel Fj is white given that it is an image of digit c:
    double Laplace[10][784];
    for(int i=0; i<10; ++i){
        for(int j=0; j<784; ++j){
            Laplace[i][j] = 0;
        }
    }
    for(int i=0; i<60000; ++i){
        for(int j=0; j<784; ++j){
            if(static_cast<int>(trainImages[i][j]) == 1){
                Laplace[static_cast<int>(trainLabels[i])][j] += 1;
            }
        }
    }
    for(int i=0; i<10; ++i){
        for(int j=0; j<784; ++j){
            Laplace[i][j] = (Laplace[i][j] + 1) / (ten[i] + 2); 
        }
    }
    //-----------------------------------------------------------------------------------
    int numLabels = 10;
    int numFeatures = 784;
    for (int c=0; c<numLabels; c++) {
       std::vector<unsigned char> classFs(numFeatures);
       for (int f=0; f<numFeatures; f++) {
        //TODO: get probability of pixel f being white given class c
        double p = Laplace[c][f];
           uint8_t v = 255*p;
           classFs[f] = (unsigned char)v;
       }
       std::stringstream ss;
       ss << "../output/digit" <<c<<".bmp";
       Bitmap::writeBitmap(classFs, 28, 28, ss.str(), false);
    }
    //-----------------------------------------------------------------------------------
    //argmax
    double c = 0;
    int test[10000];
    for(int i=0; i<10000; ++i){
        double argmax[10] = {0,0,0,0,0,0,0,0,0,0};
        for(int j=0; j<10; ++j){
            for(int k=0; k<784; ++k){
                if(static_cast<int>(testImages[i][k]) == 1){
                    argmax[j] += log2(Laplace[j][k]);
                }
                else{
                    argmax[j] += log2(1 - Laplace[j][k]);
                }
            }
            argmax[j] += prior_probability[j];
        }
        double record = -10000;
        int index = -1;
        for(int j=0; j<10; ++j){
            if(argmax[j] >= record){
                record = argmax[j];
                index = j;
            }
        }
        test[i] = index;
    }
    for(int i=0; i<testLabels.size(); ++i){
        if(static_cast<int>(testLabels[i]) == test[i]){
            c++;
        }
    }
    network.open("../output/network.txt");
    for(int i=0; i<10; ++i){
        for(int j=0; j<784; ++j){
            network << Laplace[i][j] << endl;
        }
    }
    for(int i=0; i<10; ++i){
        network << prior_probability[i] << endl;
    }
    network.close();
    int matrix[10][10];
    for(int i=0; i<10; ++i){
        for(int j=0; j<10; ++j){
            matrix[i][j] = 0;
        }
    }
    for(int i=0; i<10000; ++i){
        matrix[testLabels[i]][test[i]]++;
    }
    summary.open("../output/classification-summary.txt");
    for(int i=0; i<10; ++i){
        for(int j=0; j<10; ++j){
            summary << matrix[i][j] << " ";
        }
        summary << endl;
    }
    summary << c/testLabels.size()*100 << "%" << endl;
    summary.close();
}
