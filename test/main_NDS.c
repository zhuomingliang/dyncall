/*/////////////////////////////////////////////////////////////////////////////

  main_NDS.c
  Copyright 2008 Tassilo Philipp

  dyncall test suite stub for Nintendo DS.

/////////////////////////////////////////////////////////////////////////////*/

#include <nds.h>
#include <stdio.h>


int test_main(int argc, char* argv[]);


int main(int argc, char* argv[])
{
	powerON(POWER_ALL);

	/* Interrupt handlers. */
	/*irqInit();*/
	/*irqSet(IRQ_VBLANK, OnIrq);*/

	/* Use the touch screen for output. */
	videoSetMode(MODE_FB0);
	vramSetBankA(VRAM_A_LCD);
	videoSetModeSub(MODE_0_2D | DISPLAY_BG0_ACTIVE);
	vramSetBankC(VRAM_C_SUB_BG);
	SUB_BG0_CR = BG_MAP_BASE(31);

	/* Set the colour of the font. */
	BG_PALETTE_SUB[255] = RGB15(25, 11, 9);

	consoleInitDefault((u16*)SCREEN_BASE_BLOCK_SUB(31), (u16*)CHAR_BASE_BLOCK_SUB(0), 16);

	test_main(argc, argv);

	/* Main loop - console style. */
	while(1) {
		swiWaitForVBlank();
	}

	return 0;
}

