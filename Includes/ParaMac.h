/* Header files needed for the Mac build, plus Mac specific #defines */


#include	<Types.h>
#include <stdio.h>
#include <CType.h>
#include <IOCtl.h>
#include <StdLib.h>
#include <String.h>
#include <memory.h>
#include <Time.h>
#include	<CursorCtl.h>
#include	<Errors.h>
#include <quickdraw.h>
#include <fonts.h>
#include <dialogs.h>
#include <windows.h>
#include <menus.h>
#include <events.h>
#include <OSEvents.h>
#include <Desk.h>
#include <diskinit.h>
#include <OSUtils.h>
#include <Printing.h>
#include <resources.h>
#include <sound.h>
#include <toolutils.h>
#include <SegLoad.h>
#include <Packages.h>
#include <values.h>
#include <traps.h>



/
#include "global.h"
extern void _DataInit();


#ifndef __MAIN__
#define __MAIN__
/* All the function prototypes for the program have really got to go in
your header files.   Since the MPW IIGS compiler is not ANSI compatable
(yet) the prototypes would confuse that compiler */
void DoDiskEvents(long message);


#endif
#ifndef __MYMENUS__
#define __MYMENUS__
extern Handle MyMenuHandle;
extern Boolean ReturnID(long fred);
#endif
extern void AboutPara();

/* All the Mac specific defines */
#define applemenu 128
#define filemenu 129
#define editmenu 130

extern short FixEvent(EventRecord *x);