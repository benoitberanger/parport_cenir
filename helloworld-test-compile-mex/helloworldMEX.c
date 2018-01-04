/* In matlab, compile this function with "mex -O helloworldMEX.c" */

#include "mex.h"

void mexFunction (int nlhs,       mxArray *plhs[] ,
                  int nrhs, const mxArray *prhs[] )
{
  mexPrintf ("Hello, World! \n");
  
  mexPrintf ("I have %d inputs and %d outputs \n", nrhs, nlhs);
}
