# Using recursive template function to instantiate N-stage pipeline registers

## How to create a register using HLS:
```
template<T>
T Reg(T val) {
#pragma HLS inline self off
#pragma HLS pipeline
#pragma HLS interface ap_ctrl_none register port=return
  return val;
}
```
