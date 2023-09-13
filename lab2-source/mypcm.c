// general purpose standard C lib
#include <stdio.h>
#include <stdlib.h> // includes malloc(),free()
// Add any necessary headers here

// user-defined header files
#include "mypcm.h" // do not modify this file

// put your function prototypes for additional helper functions below:
#include <math.h>

// implementation
// use the aignal as a global variable

asignal *temp_signal;
int *size;

float analog_signal_generator(asignal signal, int t)
{
	float x = signal.A * sin(signal.omega * t + signal.sigma);

	return x;
}

void sampler(float *samples, int interval, asignal signal)
{
	temp_signal = &signal;

	int i = 0;
	int count = signal.duration / interval + 1;
	int *y = malloc(4);
	*y = count;
	size = y;
	for (i = 0; i < count; i++)
	{
		float x = analog_signal_generator(signal, i * interval);

		samples[i] = x;
	}
}

void quantizer(float *samples, int *pcmpulses, int levels, float A)
{

	float A_min = -A;
	float A_max = A;
	
	for (int i = 0; i < *size; i++)
	{

		// int x = floor((samples[i]-A_min)/(A_max-A_min)*levels);
		float x = (samples[i] - A_min) / (A_max - A_min) * levels;
		// printf("number is == %f\n", x);
		pcmpulses[i] = floor(x);
	}
}

int decimal_binary(int num)
{

	int binary_num = 0;
	int rem, temp = 1;

	while (num != 0)
	{
		rem = num % 2;
		num = num / 2;
		binary_num = binary_num + rem * temp;
		temp = temp * 10;
	}

	return binary_num;
}
void encoder(int *pcmpulses, int *dsignal, int encoderbits)
{

	for (int i = 0; i < *size; i++)
	{
		if (encoderbits > 0)
		{
			dsignal[i] = decimal_binary(pcmpulses[i]);
		}
	}
}
