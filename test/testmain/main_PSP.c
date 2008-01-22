/*/////////////////////////////////////////////////////////////////////////////

 Copyright (c) 2007,2008 Daniel Adler <dadler@uni-goettingen.de>, 
                         Tassilo Philipp <tphilipp@potion-studios.com>

 Permission to use, copy, modify, and distribute this software for any
 purpose with or without fee is hereby granted, provided that the above
 copyright notice and this permission notice appear in all copies.

 THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.

/////////////////////////////////////////////////////////////////////////////*/

/*/////////////////////////////////////////////////////////////////////////////

  main_PSP.c

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

