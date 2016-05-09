#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/io.h>
#include <stdint.h>

#include "mex.h"


#define base 0x378 /* standard adress for parport0, parport in the motherboard */


void
        mexFunction (int nlhs, mxArray *plhs[],
        int nrhs, const mxArray *prhs[])
{
    
    /* Check input arguments */
    if (nrhs != 1 || ! mxIsDouble (prhs[0]) || mxGetNumberOfElements(prhs[0]) != 1 )
        mexErrMsgTxt ("input must be a double(1,1)");
    
    /* Declare variables */
    unsigned char trigger; /* outb first argument */
    int input = mxGetScalar(prhs[0]);
    
    /* mexPrintf("input =  %d \n", input ); */
    
    /* Change input to 'trigger' */
    trigger = (unsigned char)input;
    
    /* Can we acces this adress ? */
    if(ioperm(base,1,1))
        mexErrMsgTxt("Couldn't open parallel port (sudo required ?) \n");
    
    
    outb(trigger,base);
    /* mexPrintf(" %d sent \n", trigger); */
    
}
