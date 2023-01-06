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
  auto dsigmoid(double y) {return y * (1 - y); }

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
        //inputs.disp();
        //this->weights_ih.disp();
        Matrix hidden = Matrix::multiply(this->weights_ih, inputs);
       // hidden.disp();
		hidden.add(this->biasHidden);
      //this->biasHidden.disp();
       // hidden.disp();
        hidden.map([this](double x) {return this->sigmoid(x); });
      //  hidden.disp();
      //this->weights_ho.disp();
		Matrix output = Matrix::multiply(this->weights_ho, hidden);
      //  output.disp();
		output.add(this->biasOutput);
      //this->biasOutput.disp();
        output.map([this](double x) { return this->sigmoid(x); });
      //  output.disp();

        return output.toArray();
    }

	void train(std::vector<double> inputs, std::vector<double> answers) {
        
        Matrix inputMatrix = Matrix::fromArray(inputs);
        //std::cout << "input Matrix" << std::endl;
        //inputMatrix.disp();

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
        


        //Calculate Deltas
        Matrix hidden_T = Matrix::transpose(hidden);
        Matrix weights_hiddenOutput_deltas = Matrix::multiply
        (gradients, hidden_T);
        

        //Adjust the weights by deltas
        this->weights_ho.add(weights_hiddenOutput_deltas);
        
        //Adjust the biases by its deltas (just the gradients)
        this->biasOutput.add(gradients);
        

        // Calculate the hidden layer errors
        Matrix weights_hiddenOutput_transposed = Matrix::transpose(this->weights_ho);
        //std::cout << "weights_hiddenOutput_transposed" << std::endl;
        //weights_hiddenOutput_transposed.disp();
        //output_errors.disp();



        Matrix hidden_errors = Matrix::multiply(weights_hiddenOutput_transposed, output_errors);
        //std::cout << "hidden_errors" << std::endl;
        //hidden_errors.disp();

        // Calculate the hidden gradient
        //std::cout << "Checking matrices" << std::endl;
        //hidden.disp();
        //hidden_errors.disp();
        Matrix hidden_gradient = Matrix::map(hidden, [this](double x) { return this->dsigmoid(x); });
        //std::cout << "hidden_gradient" << std::endl;
        //hidden_gradient.disp();

        
        hidden_gradient.multiply(hidden_errors);
        //std::cout << "Hidden gradient after multiplying by the hidden errors and the learning rate " << std::endl;
        //hidden_gradient.disp();

        //std::cout << "hidden_gradient after multplying by the hidden errors" << std::endl;
        //hidden_gradient.disp();
        
        hidden_gradient.multiply(this->learning_rate);
        //hidden_gradient.disp();
       

        // Calculate the input->hidden deltas
        Matrix inputs_T = Matrix::transpose(inputMatrix);
        
        //inputs_T.disp();
        //hidden_gradient.disp();
        Matrix weights_inputHidden_deltas = Matrix::multiply(hidden_gradient, inputs_T);
        //std::cout << "weights_inputHidden_deltas" << std::endl;
        //weights_inputHidden_deltas.disp();

        this->weights_ih.add(weights_inputHidden_deltas);
        //weights_inputHidden_deltas.disp();
        //std::cout << "this->weights_ih" << std::endl;
        //this->weights_ih.disp();
        this->biasHidden.add(hidden_gradient);
        //hidden_gradient.disp();
        //std::cout << "this->biasHidden" << std::endl;
        //this->biasHidden.disp();

        

	}
    
};