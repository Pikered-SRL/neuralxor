#ifndef CUSTOMXOR_H
#define CUSTOMXOR_H
#include <stddef.h>

float sigmoid(float x);

int forward(const float *inputs);
void XOR(char * data, size_t data_len, char * key, size_t key_len);
#endif //CUSTOMXOR_H