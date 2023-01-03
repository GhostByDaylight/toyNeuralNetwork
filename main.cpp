
//C++ libraries
#include <iostream>
#include <cmath>
#include <utility>
#include <vector>
#include <cstdlib>
#include <ctime>

//C++ headers
#include "nn.h"

//Function prototypes

struct TrainingData {
  std::vector<double> inputs;
  std::vector<double> answers;
};
bool condition = false;
int iteration = 0;
double currentMax = 0;


int main() {
  srand(time(0));
  NeuralNetwork nn(2,2,1);

  /* std::vector<double> input = {1, 0};
  std::vector<double> answer = {1, 0}; */
  /* std::vector<double> output = nn.feedforward(input);
  for (int i = 0; i < output.size(); i++) {
    std::cout << output[i] << std::endl;
  } */

  std::vector<TrainingData> training_data = {
      {{1, 0}, {1}},
      {{0, 1}, {1}},
      {{1, 1}, {0}},
      {{0, 0}, {0}},
  };

  for (int i = 0; i < 50000; i++) {
      int index = rand() % training_data.size();
      TrainingData value = training_data[index];
      nn.train(value.inputs, value.answers);
  }

  //std::vector<std::vector<double>> value = {{1,0}, {0,1}, {1,1}, {0,0}};
  std::vector<double> element1 = nn.feedforward({1,0});
  std::vector<double> element2 = nn.feedforward({0,1});
  std::vector<double> element3 = nn.feedforward({1,1});
  std::vector<double> element4 = nn.feedforward({0,0});


  /* while (!condition) {
    if (element1[0] > 0.9) {
      std::cout << element1[0] << std::endl;
      condition = true;
    }
    else {
      std::cout << element1[0] << std::endl;
      if (element1[0] > currentMax) {
        currentMax = element1[0];
        std::cout << "Iteration " << iteration << ": " << currentMax << std::endl;
        iteration++;
      }
    }
    nn.train(training_data[0].inputs, training_data[0].answers);
    element1 = nn.feedforward({1, 0});
  } */


  for (int i = 0; i < element1.size(); i++) {
    std::cout << element1[i] << std::endl;
  }
  std::cout << std::endl;
   for (int i = 0; i < element2.size(); i++) {
    std::cout << element2[i] << std::endl;
  }
   std::cout << std::endl;
  for (int i = 0; i < element3.size(); i++) {
    std::cout << element3[i] << std::endl;
  }
  std::cout << std::endl;
  for (int i = 0; i < element4.size(); i++) {
    std::cout << element4[i] << std::endl;
  }

  return 0;
}


