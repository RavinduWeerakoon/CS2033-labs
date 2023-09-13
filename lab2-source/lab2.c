// general purpose standard C lib
#include <stdio.h>
#include <stdlib.h> // stdlib includes malloc() and free()

// user-defined header files
#include <math.h>
#include "mypcm.h"

// function prototypes
void run(asignal *inputsignal);

int main()
{
    asignal *inputsignal = (asignal *)malloc(sizeof(asignal));
    run(inputsignal);

    // call any other function here

    free(inputsignal);
    return 0;
}

void update_signal(asignal *inputsignal)
{
    float A, omega, sigma;
    int duration;

    scanf("%f", &A);
    scanf("%f", &omega);
    scanf("%f", &sigma);
    scanf("%d", &duration);

    inputsignal->A = A;
    inputsignal->omega = omega;
    inputsignal->sigma = sigma;
    inputsignal->duration = duration;
}

void run(asignal *inputsignal)
{

    update_signal(inputsignal);

    int interval, encoderbits;

    scanf("%d", &interval);
    scanf("%d", &encoderbits);

    int levels = pow(2, encoderbits);

    // as we need one more level
    int count = inputsignal->duration / interval + 1;

    float samples[count];
    int pcmPulses[count];
    int dsignal[count];

    sampler(samples, interval, *inputsignal);

    quantizer(samples, pcmPulses, levels, inputsignal->A);

    encoder(pcmPulses, dsignal, encoderbits);

    for (int i = 0; i < count; i++)
    {
        printf("%0*d", encoderbits, dsignal[i]);
    }
}
