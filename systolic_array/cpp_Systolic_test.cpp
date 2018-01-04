/*******************************************************************************
Vendor: Xilinx 
Associated Filename: cpp_FIR_test.cpp
Purpose:Vivado HLS Coding Style example 
Device: All 
Revision History: May 30, 2008 - initial release
                                                
*******************************************************************************
#-  (c) Copyright 2011-2017 Xilinx, Inc. All rights reserved.
#-
#-  This file contains confidential and proprietary information
#-  of Xilinx, Inc. and is protected under U.S. and
#-  international copyright and other intellectual property
#-  laws.
#-
#-  DISCLAIMER
#-  This disclaimer is not a license and does not grant any
#-  rights to the materials distributed herewith. Except as
#-  otherwise provided in a valid license issued to you by
#-  Xilinx, and to the maximum extent permitted by applicable
#-  law: (1) THESE MATERIALS ARE MADE AVAILABLE "AS IS" AND
#-  WITH ALL FAULTS, AND XILINX HEREBY DISCLAIMS ALL WARRANTIES
#-  AND CONDITIONS, EXPRESS, IMPLIED, OR STATUTORY, INCLUDING
#-  BUT NOT LIMITED TO WARRANTIES OF MERCHANTABILITY, NON-
#-  INFRINGEMENT, OR FITNESS FOR ANY PARTICULAR PURPOSE; and
#-  (2) Xilinx shall not be liable (whether in contract or tort,
#-  including negligence, or under any other theory of
#-  liability) for any loss or damage of any kind or nature
#-  related to, arising under or in connection with these
#-  materials, including for any direct, or any indirect,
#-  special, incidental, or consequential loss or damage
#-  (including loss of data, profits, goodwill, or any type of
#-  loss or damage suffered as a result of any action brought
#-  by a third party) even if such damage or loss was
#-  reasonably foreseeable or Xilinx had been advised of the
#-  possibility of the same.
#-
#-  CRITICAL APPLICATIONS
#-  Xilinx products are not designed or intended to be fail-
#-  safe, or for use in any application requiring fail-safe
#-  performance, such as life-support or safety devices or
#-  systems, Class III medical devices, nuclear facilities,
#-  applications related to the deployment of airbags, or any
#-  other applications that could lead to death, personal
#-  injury, or severe property or environmental damage
#-  (individually and collectively, "Critical
#-  Applications"). Customer assumes the sole risk and
#-  liability of any use of Xilinx products in Critical
#-  Applications, subject only to applicable laws and
#-  regulations governing limitations on product liability.
#-
#-  THIS COPYRIGHT NOTICE AND DISCLAIMER MUST BE RETAINED AS
#-  PART OF THIS FILE AT ALL TIMES. 
#- ************************************************************************


This file contains confidential and proprietary information of Xilinx, Inc. and 
is protected under U.S. and international copyright and other intellectual 
property laws.

DISCLAIMER
This disclaimer is not a license and does not grant any rights to the materials 
distributed herewith. Except as otherwise provided in a valid license issued to 
you by Xilinx, and to the maximum extent permitted by applicable law: 
(1) THESE MATERIALS ARE MADE AVAILABLE "AS IS" AND WITH ALL FAULTS, AND XILINX 
HEREBY DISCLAIMS ALL WARRANTIES AND CONDITIONS, EXPRESS, IMPLIED, OR STATUTORY, 
INCLUDING BUT NOT LIMITED TO WARRANTIES OF MERCHANTABILITY, NON-INFRINGEMENT, OR 
FITNESS FOR ANY PARTICULAR PURPOSE; and (2) Xilinx shall not be liable (whether 
in contract or tort, including negligence, or under any other theory of 
liability) for any loss or damage of any kind or nature related to, arising under 
or in connection with these materials, including for any direct, or any indirect, 
special, incidental, or consequential loss or damage (including loss of data, 
profits, goodwill, or any type of loss or damage suffered as a result of any 
action brought by a third party) even if such damage or loss was reasonably 
foreseeable or Xilinx had been advised of the possibility of the same.

CRITICAL APPLICATIONS
Xilinx products are not designed or intended to be fail-safe, or for use in any 
application requiring fail-safe performance, such as life-support or safety 
devices or systems, Class III medical devices, nuclear facilities, applications 
related to the deployment of airbags, or any other applications that could lead 
to death, personal injury, or severe property or environmental damage 
(individually and collectively, "Critical Applications"). Customer asresultes the 
sole risk and liability of any use of Xilinx products in Critical Applications, 
subject only to applicable laws and regulations governing limitations on product 
liability. 

THIS COPYRIGHT NOTICE AND DISCLAIMER MUST BE RETAINED AS PART OF THIS FILE AT 
ALL TIMES.

*******************************************************************************/
#include "cpp_Systolic.h"

//#define L	PE_SIZE*2

int main()
  {
    ofstream result;
    data_t output;
	int retval=0;

	data_t data[(L+2*PE_SIZE-1)*PE_SIZE];     // reshaped data [L+2*PE_SIZE-1,PE_SIZE]
	coef_t weight[PE_SIZE*PE_SIZE];           // weight[PE_SIZE,PE_SIZE]
	data_t gold_data[L*PE_SIZE];        // gold_data[L,PE_SIZE]
	acc_t  gold_result[L*PE_SIZE];      // gold_result[L,PE_SIZE]
	acc_t  cal_result[(L+2*PE_SIZE-1)*PE_SIZE]; // reshaped result [L,L+2*PE_SIZE-1]

	int val = 0;
	for (int j = 0; j < PE_SIZE; ++j) {
		for (int i = 0; i < L+2*PE_SIZE-1; ++i) {
			if (i<j) {
				data[i*PE_SIZE+j] = 0;
			} else if (j<=i && (i-j)<L) {
				data[i*PE_SIZE+j] = ++val;
			} else {
				data[i*PE_SIZE+j] = 0;
			}
		}
	}

	printf("test_data[] = \n");
	for (int i = 0; i < L+2*PE_SIZE-1; ++i) {
		for (int j = 0; j < PE_SIZE; ++j) {
			printf("%08d ", data[i*PE_SIZE+j]);
		}
		printf("\n");
	}
	printf("\n\n");

	for (int i = 0; i < L+2*PE_SIZE-1; ++i) {
		for (int j = 0; j < PE_SIZE; ++j) {
			cal_result[i*PE_SIZE+j] = 0;
		}
	}

	val = 0;
	for (int j = 0; j < PE_SIZE; ++j) {
		for (int i = 0; i < L; ++i) {
			gold_data[i*PE_SIZE+j] = ++val;
		}
	}
	printf("gold_data[] = \n");
	for (int i = 0; i < L; ++i) {
		for (int j = 0; j < PE_SIZE; ++j) {
			printf("%08d ", gold_data[i*PE_SIZE+j]);
		}
		printf("\n");
	}
	printf("\n\n");

	for (int i = 0; i < PE_SIZE; ++i) {
		for (int j = 0; j < PE_SIZE; ++j) {
			weight[i*PE_SIZE+j] = 1;
		}
	}

	for (int i = 0; i < L; ++i) {
		for (int j = 0; j < PE_SIZE; ++j) {
			gold_result[i*PE_SIZE+j] = 0;
		}
	}

	for (int i = 0; i < L; ++i) {
		for (int j = 0; j < PE_SIZE; ++j) {
			for (int k = 0; k < PE_SIZE; ++k) {
				gold_result[i*PE_SIZE+j] += gold_data[i*PE_SIZE+k]*weight[k*PE_SIZE+j];
			}
		}
	}

	printf("gold_result[] = \n");
	for (int i = 0; i < L; ++i) {
		for (int j = 0; j < PE_SIZE; ++j) {
			printf("%08d ", gold_result[i*PE_SIZE+j]);
		}
		printf("\n");
	}
	printf("\n\n");

	cpp_Systolic(data, weight, cal_result, L, false, false);

	printf("result[] = \n");
	for (int i = 0; i < L+2*PE_SIZE-1; ++i) {
		for (int j = 0; j < PE_SIZE; ++j) {
			printf("%08d ", cal_result[i*PE_SIZE+j]);
		}
		printf("\n");
	}
	printf("\n\n");
	printf("Total estimated cycles = %d\n", L+2*PE_SIZE);

	if (retval != 0) {
		printf("Test failed  !!!\n"); 
		retval=1;
	} else {
		printf("Test passed !\n");
  }

	// Return 0 if the test passes
  return retval;
  }

