#include "cpp_Systolic.h"

void systolic_array(const data_t data_in[PE_SIZE], acc_t result_out[PE_SIZE], bool switch_weight, bool update_weight)
{
#pragma HLS PIPELINE
	static CPe<coef_t, data_t, acc_t> pe_array[PE_SIZE][PE_SIZE];
#pragma HLS ARRAY_PARTITION variable=pe_array complete dim=0

	static data_t data[PE_SIZE+1][PE_SIZE+1];
#pragma HLS ARRAY_PARTITION variable=data complete dim=0
	static coef_t weight[PE_SIZE+1][PE_SIZE+1];
#pragma HLS ARRAY_PARTITION variable=weight complete dim=0
	static acc_t  acc[PE_SIZE+1][PE_SIZE+1];
#pragma HLS ARRAY_PARTITION variable=acc complete dim=0

	for (int n = 0; n < PE_SIZE; ++n) {
		acc[0][n] = 0;
		data[n][0] = data_in[n];
	}

#ifndef __SYNTHESIS__
	/*
	static int m = 0;
	printf("data[][%d]=\n", m);
	for (int i = 0; i < PE_SIZE; ++i) {
		printf("%08d ", data[i][0]);
	}
	printf("\n\n");
	*/
#endif

	for (int i = 0; i < PE_SIZE; ++i) {
		for (int j = 0; j < PE_SIZE; ++j) {
			pe_array[i][j].output(data[i][j+1], weight[i+1][j], acc[i+1][j]);
		}
	}

	for (int i = 0; i < PE_SIZE; ++i) {
		for (int j = 0; j < PE_SIZE; ++j) {
			pe_array[i][j].update(data[i][j], weight[i][j], acc[i][j], switch_weight, update_weight);
		}
	}

	for (int i = 0; i < PE_SIZE; ++i) {
		result_out[i] = acc[PE_SIZE][i];
	}
#ifndef __SYNTHESIS__
	/*
	printf("acc[]=\n");
	for (int i = 0; i < PE_SIZE; ++i) {
		printf("%08d ", acc[PE_SIZE][i]);
	}
	printf("\n\n");
	*/
#endif
}

void cpp_Systolic(const data_t data_in[PE_SIZE*(L+2*PE_SIZE-1)], const coef_t weight_in[PE_SIZE*PE_SIZE], acc_t result_out[PE_SIZE*(L+2*PE_SIZE-1)], int length, bool switch_weight, bool update_weight)
{
//#pragma HLS ARRAY_PARTITION variable=result_out complete dim=1
//#pragma HLS ARRAY_PARTITION variable=data_in complete dim=1
	for (int m = 0; m < length/*PE_SIZE*/+PE_SIZE*2-1; ++m) {
#pragma HLS PIPELINE
		systolic_array(&data_in[m*PE_SIZE], &result_out[m*PE_SIZE], switch_weight, update_weight);
	}
}
