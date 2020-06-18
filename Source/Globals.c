/* Various global variables used here and there */
#ifdef MAC
#include "paramac.h" 
#endif
#ifdef GS
#include "parags.h"
#endif
#include "defines.h"
int itemID;
int menuID;		/* global for HiliteMenu() use */
WindowPtr activewindow;  /* our window */

#ifdef GS

EventRecord ERecord={
0,
0L,
0L,
0L,
0L,
0x1f5fffL,
0L,
0,
0L,
0L
};
PatternPtr Pats[5]; /* color patterns and pointers */
Pattern mypatterns[5];




#endif

#ifdef MAC


ControlHandle myctlhandle; 
Boolean gHasWaitNextEvent;

EventRecord ERecord;

MenuHandle applemenuhandle,filemenuhandle,editmenuhandle;

ControlHandle TheControlID;

SysEnvRec myConfig;
Boolean YeahColor;

Handle MyMenuHandle;
long Notes[4]={
0x3025d,	/* middle C */
0x360b5,	/* D */
0x3ca99,	/* E */
0x40450		/* F */
};
#endif

#ifdef GS

MenuBarRecHndl MyMenuHandle;
Boolean editSet;

Ref mystartstopreccord;
CtlRecHndl myctlhandle;
short Notes[4]={
0x50, 	/* middle C */
0x52, 	/* D */
0x54,	/* E */
0x55	/* F */
};
#endif

Rect RA[6];	/* array of rects */
Point WordPoint;
/* game variables */
Boolean Playing;
Boolean PlayedOnce;
unsigned char Sequence[500];
int SeqPos;
int CurrentLength;
Boolean tryagain;
int CurrentScore;
