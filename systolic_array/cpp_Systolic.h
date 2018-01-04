#ifndef _CPP_FIR_H_
#define _CPP_FIR_H_

#include <fstream>
#include <iostream>
#include <iomanip>
#include <cstdlib>
using namespace std;

typedef short coef_t;
typedef short data_t;
typedef short acc_t;

#define PE_SIZE	4
#define L 		PE_SIZE*2

// Class CPe definition
template<class coef_T, class data_T, class acc_T>
class CPe {
protected:
  data_T data_reg;
  coef_T weight_reg[2];
  coef_T act_weight_reg;
  acc_T  acc_reg;
  bool 	 weight_sel;
private:
public:
  CPe():data_reg(0), acc_reg(0), weight_sel(false) {
	  weight_reg[0] = 1;
	  weight_reg[1] = 2;
  }
  void output(data_T &data_out, coef_T &weight_out, acc_T &acc_out);
  void update(data_T data_in, coef_T weight_in, acc_T acc_in, bool switch_weight, bool update_weight);

};

// PE output function
template<class coef_T, class data_T, class acc_T>
void CPe<coef_T, data_T, acc_T>::output(data_T &data_out, coef_T &weight_out, acc_T &acc_out) {
#pragma HLS INLINE
	data_out = data_reg;
	weight_out = act_weight_reg;
	acc_out = acc_reg;
}

// PE update function
template<class coef_T, class data_T, class acc_T>
void CPe<coef_T, data_T, acc_T>::update(data_T data_in, coef_T weight_in, acc_T acc_in, bool switch_weight, bool update_weight) {
#pragma HLS INLINE
#pragma HLS RESOURCE variable=data_reg core=DSP48
	coef_T tmp_weight;
	if (weight_sel) {
		tmp_weight = act_weight_reg = weight_reg[1];
	} else {
		tmp_weight = act_weight_reg = weight_reg[0];
	}
	acc_reg = acc_in + data_in*tmp_weight;
	data_reg = data_in;
	if (update_weight) {
		if (weight_sel) // weight_reg[1] is being used for computation
			weight_reg[0] = weight_in;
		else
			weight_reg[1] = weight_in;
	}
	if (switch_weight) {
		weight_sel = !weight_sel;
	}
#ifndef __SYNTHESIS__
	//cout << "data_in=" << data_in << ", weight=" << act_weight_reg << ", acc_in=" << acc_in << ", acc_reg=" << acc_reg << endl;
#endif
}

//data_t cpp_Systolic(data_t data_in, coef_t weight_in, bool switch_weight, bool update_weight);
//data_t cpp_Systolic(data_t data_in[], coef_t weight_in[], int length);
void cpp_Systolic(const data_t data_in[PE_SIZE*(L+2*PE_SIZE-1)], const coef_t weight_in[PE_SIZE*PE_SIZE], acc_t result_out[PE_SIZE*(L+2*PE_SIZE-1)], int length, bool switch_weight, bool update_weight);

#endif

