#include <cmath>
#include <functional>
#include <vector>

#include "matrix.h"

class NeuralNetwork {
private:
  int inputNodes, hiddenNodes, outputNodes;
  double learning_rate;
  Matrix weights_ih, weights_ho, biasHidden, biasOutput;

public:
  auto sigmoid(double x) { return 1 / (1 + exp(-x)); }
  auto dsigmoid(double y) { return y * (1 - y); }

  NeuralNetwork(int input, int hidden, int output) {
    this->inputNodes = input;
    this->hiddenNodes = hidden;
    this->outputNodes = output;

    this->weights_ih = Matrix(this->hiddenNodes, this->inputNodes);
    this->weights_ho = Matrix(this->outputNodes, this->hiddenNodes);
    this->weights_ih.randomize();
    this->weights_ho.randomize();

    this->biasHidden = Matrix(this->hiddenNodes, 1);
    this->biasOutput = Matrix(this->outputNodes, 1);

    this->biasHidden.randomize();
    this->biasOutput.randomize();

    this->learning_rate = 10.0;
  }

  std::vector<double> feedforward(std::vector<double> value) {

    Matrix inputs = Matrix::fromArray(value);
    Matrix hidden = Matrix::multiply(this->weights_ih, inputs);
    hidden.add(this->biasHidden);
    hidden.map([this](double x) { return this->sigmoid(x); });
    Matrix output = Matrix::multiply(this->weights_ho, hidden);
    output.add(this->biasOutput);
    output.map([this](double x) { return this->sigmoid(x); });

    return output.toArray();
  }

  void train(std::vector<double> inputs, std::vector<double> answers) {

    Matrix inputMatrix = Matrix::fromArray(inputs);

    Matrix hidden = Matrix::multiply(this->weights_ih, inputMatrix);
    hidden.add(this->biasHidden);
    hidden.map([this](double x) { return this->sigmoid(x); });

    Matrix output = Matrix::multiply(this->weights_ho, hidden);
    output.add(this->biasOutput);
    output.map([this](double x) { return this->sigmoid(x); });

    Matrix answersMatrix = Matrix::fromArray(answers);
    Matrix output_errors = Matrix::subtract(answersMatrix, output);

    Matrix gradients = Matrix::map(output, [this](double x) { return this->dsigmoid(x); });
    gradients.multiply(output_errors);
    gradients.multiply(this->learning_rate);

    // Calculate Deltas
    Matrix hidden_T = Matrix::transpose(hidden);
    Matrix weights_hiddenOutput_deltas = Matrix::multiply(gradients, hidden_T);

    // Adjust the weights by deltas
    this->weights_ho.add(weights_hiddenOutput_deltas);

    // Adjust the biases by its deltas (just the gradients)
    this->biasOutput.add(gradients);

    // Calculate the hidden layer errors
    Matrix weights_hiddenOutput_transposed = Matrix::transpose(this->weights_ho);

    Matrix hidden_errors = Matrix::multiply(weights_hiddenOutput_transposed, output_errors);

    Matrix hidden_gradient = Matrix::map(hidden, [this](double x) { return this->dsigmoid(x); });


    hidden_gradient.multiply(hidden_errors);


    hidden_gradient.multiply(this->learning_rate);


    // Calculate the input->hidden deltas
    Matrix inputs_T = Matrix::transpose(inputMatrix);

    Matrix weights_inputHidden_deltas =
    Matrix::multiply(hidden_gradient, inputs_T);


    this->weights_ih.add(weights_inputHidden_deltas);
    this->biasHidden.add(hidden_gradient);
  }
};
