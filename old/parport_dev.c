#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> /* For open() */
#include <fcntl.h> /* For O_RDWR */
#include <errno.h>
#include <linux/ppdev.h>
#include <linux/parport.h>
#include <sys/ioctl.h> /* For PPWDATA */
#include "mex.h"

#define ppdev "/dev/parport0"/* parport in the motherboard */


void
        mexFunction (int nlhs, mxArray *plhs[],
        int nrhs, const mxArray *prhs[])
{
    
    /* Check input arguments */
    if (nrhs != 1 || ! mxIsDouble (prhs[0]) || mxGetNumberOfElements(prhs[0]) != 1 )
        mexErrMsgTxt ("input must be a double(1,1)");
    
    /* Declare variables */
    int pport = open(ppdev, O_RDWR);  /* Open the device/file */
    unsigned char trigger;            /* Message to send */
    int input = mxGetScalar(prhs[0]); /* Fetch the input value */
    
    /* Change input to 'trigger' */
    trigger = (unsigned char)input;
    
    /* File opened ? */
    if (pport < 0)
        mexErrMsgTxt("Couldn't open parallel port (user have permission on the device ? user in the good group ?) \n");
    
    /* Claim access */
    if (ioctl(pport, PPCLAIM) < 0)
    {
        mexPrintf("PPCLAIM ioctl Error : %s (%d)\n",strerror(errno),errno);
        mexErrMsgTxt("PPCLAIM ioctl Error");
    }
    
    /* Send the message */
    if (ioctl (pport, PPWDATA, &trigger) < 0)
    {
        mexPrintf("PPWDATA ioctl Error : %s (%d)\n",strerror(errno),errno);
        mexErrMsgTxt("PPWDATA ioctl Error \n");
    }
    
    /* Release access */
    if (ioctl(pport, PPRELEASE) < 0)
    {
        mexPrintf("PPRELEASE ioctl Error : %s (%d)\n",strerror(errno),errno);
        mexErrMsgTxt("PPRELEASE ioctl Error\n");
    }
    
    /* Close file */
    if(close(pport) < 0)
    {
        mexPrintf("Close Error : %s (%d)\n",strerror(errno),errno);
        mexErrMsgTxt("Close Error\n");
    }
    
}
