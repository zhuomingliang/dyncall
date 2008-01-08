/*/////////////////////////////////////////////////////////////////////////////

  main_PSP.c
  Copyright 2008 Daniel Adler

  dyncall test suite stub for Sony PSP.

/////////////////////////////////////////////////////////////////////////////*/


#include <pspkernel.h>
#include <pspdebug.h>
PSP_MODULE_INFO("dyncall", 0, 1, 1);
#include "stdio.h"
int test_main(int argc, char* argv[]);

/*  
int exit_callback(int arg1, int arg2, void* common) 
{
  sceKernelExitGame();
  return 0;
}

int CallbackThread(SceSize args, void* argp) 
{
  int cbid;
  cbid = sceKernelCreateCallback("Exit Callback", exit_callback, NULL);
  sceKernelRegisterExitCallback(cbid);
  sceKernelSleepThreadCB();
  return 0;
}

int SetupCallbacks() 
{
  int thid = 0;
  thid = sceKernelCreateThread("update_thread", CallbackThread, 0x11, 0xFA0, 0, 0);
  if (thid >= 0) {
    sceKernelStartThread(thid,0,0);
  }
  return thid;
}
*/

int main(int argc, char* argv[])
{
  int errorcode;
  /*
  pspDebugScreenInit();
  SetupCallbacks();
  */
  errorcode = test_main(argc, argv);
  /*
  sceKernelSleepThread();
  */
  return errorcode;
}

