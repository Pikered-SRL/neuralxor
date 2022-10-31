#include "neuralXor.h"
#include "apprExp.h"
static const int numInputs = 2;
static const int numHiddenNodes = 2;
static const int numOutputs = 1;
float hiddenLayer[2];
float outputLayer[1];
static const float hiddenLayerBias[2] = {-2.356486f, -5.029821f};
static const float outputLayerBias[1] = {-3.136066f};
static const float hiddenWeights[2][2] = {{6.393411f, 3.357927f},{5.691278f, 3.270246f}};
static const float outputWeights[2][1] = {{7.089031f}, {-7.716286f}};
static const float myexp = 2.7182818284590452353602874713527;

float sigmoid(float x){return 1/(1+powff(myexp, -x));}

int forward(const float *inputs){
    //Hidden layer activation
    for (int j = 0; j < numHiddenNodes; j++) {
        float activation = hiddenLayerBias[j];
        for (int k = 0; k < numInputs; k++) {
            activation += inputs[k] * hiddenWeights[k][j];
        }
        hiddenLayer[j] = sigmoid(activation);
    }
    //Output layer activation
    for (int j = 0; j < numOutputs; j++) {
        float activation = outputLayerBias[j];
        for (int k = 0; k < numHiddenNodes; k++) {
            activation += hiddenLayer[k] * outputWeights[k][j];
        }
        outputLayer[j] = sigmoid(activation);
    }
    if(outputLayer[0]>=0.5)
        return 1;
    else
        return 0;
}

void XOR(char * data, size_t data_len, char * key, size_t key_len) {
    int j = 0;
    unsigned char net_outputs;
    for(int i = 0; i < data_len; i++){
        net_outputs = 0 << 7 & 0 << 6 & 0 << 5 & 0 << 4 & 0 << 3 & 0 << 2 & 0 << 1 & 0 << 0;
        if(j == key_len - 1)
            j = 0;
        for(int k = 0; k < 8; k++){
            float net_inputs[] = {(float)((data[i] >> k) & 0x01), (float)((key[j] >> k) & 0x01)};
            net_outputs |= forward(net_inputs) << k;
        }
        data[i] = net_outputs;
        j++;
    }
}
