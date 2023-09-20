#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define FS 10000
#define LENGTH 10000
#define Fsig 2000  // frequency of the sine wave
#define SIG_LEN 10000
#define COEFF_LEN 72
#define OUT_LEN 10071

double sig[SIG_LEN];
double coeff[COEFF_LEN] = {
    0.01240525973487,  0.02019739079583,0.0004927645702503,-0.007131393375741,
  0.002824762975422, 0.005217401433515,-0.007028060763173,-0.0002100978117079,
  0.007416038416151,-0.004366837233082,-0.005695336784211, 0.008807979939495,
 0.0006737956143654, -0.01041634762392, 0.005873843564751, 0.008233996709034,
  -0.01210144277752,-0.001702987999631,  0.01512635534557,-0.007773728975137,
  -0.01268464956713,  0.01739212466242, 0.003694001656421, -0.02319218099424,
   0.01081238910808,  0.02114014631142, -0.02752879197083,-0.008078699653726,
   0.04105613571903, -0.01780317869842, -0.04411310292265,  0.05843292311194,
   0.02481531577559,  -0.1268643349931,  0.06857665238362,   0.5130452651755,
    0.5130452651755,  0.06857665238362,  -0.1268643349931,  0.02481531577559,
   0.05843292311194, -0.04411310292265, -0.01780317869842,  0.04105613571903,
 -0.008078699653726, -0.02752879197083,  0.02114014631142,  0.01081238910808,
  -0.02319218099424, 0.003694001656421,  0.01739212466242, -0.01268464956713,
 -0.007773728975137,  0.01512635534557,-0.001702987999631, -0.01210144277752,
  0.008233996709034, 0.005873843564751, -0.01041634762392,0.0006737956143654,
  0.008807979939495,-0.005695336784211,-0.004366837233082, 0.007416038416151,
 -0.0002100978117079,-0.007028060763173, 0.005217401433515, 0.002824762975422,
 -0.007131393375741,0.0004927645702503,  0.02019739079583,  0.01240525973487
}; 
double out[OUT_LEN] = {0};

void generate_sin_signal() {
    for(int i = 0; i < LENGTH; i++) {
        double t = (double)i / FS;
        sig[i] = sin(2 * M_PI * Fsig * t);
    }
}

void save_to_file(const char* filename, double data[], int len) {
    FILE *fp = fopen(filename, "w");
    if (fp == NULL) {
        perror("Error opening file");
        return;
    }

    for(int i = 0; i < len; i++) {
        fprintf(fp, "%f\n", data[i]);
    }

    fclose(fp);
}

int main() {
    // Generate the sine signal
    generate_sin_signal();

    // Convolution logic
    for(int i = 0; i < OUT_LEN; i++) {
        int k = 0;
        while(!(i-k < SIG_LEN)) {
            k++;
        }
        
        while(i-k >= 0) {
            if (k >= COEFF_LEN) {
                break;
            }
            out[i] += sig[i-k] * coeff[k];
            k++;
        }
    }

    // Save input signal to "input_signal.txt"
    save_to_file("input_signal.txt", sig, SIG_LEN);

    // Save filter output to "filter_output.txt"
    save_to_file("filter_output.txt", out, OUT_LEN);

    return 0;
}

