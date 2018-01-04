/* To compile in MATLAB/Octave command windows "mex -O ppmex.c" */

/* On my computer, "ppmex('w',msg)" takes between 10µs and 40µs to be executed => checked at the oscilloscope.
 * So yes, there is a jitter...
 */

#include <unistd.h> /* For open() */
#include <fcntl.h> /* For O_RDWR */
#include <errno.h>
#include <linux/ppdev.h>
#include <linux/parport.h>
#include <sys/ioctl.h> /* For PPWDATA */
#include "mex.h"

/* Here you define the adress (file location lin linux) of the device you want to write */
#define ppdev "/dev/parport0" /* default parport on the motherboard is "/dev/parport0" */

/* Here, I prefer to define a global scope variable for the output of
 * open() function, it's very easy to store it and use it with multiple
 * functions */
extern int pport = 0;

/*************************************************************************/
/* Print help */
/*************************************************************************/
void PrintHelp() {
    mexPrintf("ppmex usage : \n");
    mexPrintf("ppmex('open')          : opens  the device, and get it ready to send messages \n");
    mexPrintf("ppmex('write',message) : sends  the message = {0, 1, 2, ..., 255} uint8 \n");
    mexPrintf("ppmex('close')         : closes the device \n");
    mexPrintf("\n");
}


/*************************************************************************/
/* Open the device/file, then claim access, so we are ready to send messages */
/*************************************************************************/
void Open() {
    
    /* Declare variables */
    pport = open(ppdev, O_RDWR);  /* Open the device/file */
    
    /* File opened ? */
    if (pport < 0)
        mexErrMsgTxt("Couldn't open parallel port (user have permission on the device ? user in the good group ?) \n");
    
    /* Claim access */
    if (ioctl(pport, PPCLAIM) < 0)
    {
        mexPrintf("PPCLAIM ioctl Error : %s (%d)\n",strerror(errno),errno);
        mexErrMsgTxt("PPCLAIM ioctl Error");
    }
    
    mexPrintf("Parallel opened successfully \n");
    
}

/*************************************************************************/
/* Send message */
/*************************************************************************/
void Write(const unsigned char *message) {
    if (pport > 0)
    {
        /* Send the message */
        if (ioctl (pport, PPWDATA, message) < 0)
        {
            mexPrintf("PPWDATA ioctl Error : %s (%d)\n",strerror(errno),errno);
            mexErrMsgTxt("PPWDATA ioctl Error \n");
        }
    }
    else
        mexErrMsgTxt("Parallel port was not opened \n");
}

/*************************************************************************/
/* Cleans up on exit */
/*************************************************************************/
void onUnload() {
    if (pport > 0)
    {
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
        
        pport = 0;
        mexPrintf("Parallel port has been closed \n");
    }
    else
        mexPrintf("Parallel port was not opened \n");
}

/*************************************************************************/
/* Entry point of the MEX-function */
/*************************************************************************/
void mexFunction (int nlhs, mxArray *plhs[],
        int nrhs, const mxArray *prhs[]) {
    
    char *action;
    
    /* Check inputs */
    if (nrhs==0) {
        PrintHelp();
        return;
    }
    
    /* Determine what user is requesting */
    action = mxArrayToString(prhs[0]);
    
    switch (action[0]) {
        
        case 'o': /* open */
            if (pport!=0) onUnload(); /* close, then re-open */
            Open();
            break;
            
        case 'w': /* write */
            if (nrhs!=2) mexErrMsgTxt("You need to specify the message to send [0-255]");
            unsigned char message;            /* Message to send         */
            int input = mxGetScalar(prhs[1]); /* Fetch the input value   */
            message = (unsigned char)input;   /* Change input to message */
            Write(&message);
            break;
            
        case 'c': /* close */
            onUnload();
            break;
            
        default:
            mexErrMsgTxt("No valid action specified : o / w / c");
            
    }
    
    /* Make sure device is released when MEX-file is cleared */
    mexAtExit(onUnload);
    
}

