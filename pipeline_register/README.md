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

## How to create a N-stage pipeline registers
```
template<T, int num_stages>
T Reg(T val) {
#pragma HLS inline self off
#pragma HLS pipeline
#pragma HLS interface ap_ctrl_none register port=return
  if (num_stages == 1)
    return val;
  else 
    return Reg<T,num_stages-1>(val);
}
```

## Reference from include/hls/utils/x_hls_utils.h
```
template<class T>
T reg(T in)
{
    //#ifndef NO_FORCING
#pragma HLS INLINE self off
#pragma HLS INTERFACE ap_none port=return register
    //#endif
    return in;
}
```
