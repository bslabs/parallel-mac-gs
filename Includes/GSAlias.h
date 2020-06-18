/* Redefining a GS call to act like it's Mac equiv. */
#include <control.h>
HiliteControl(controlhand,yyhilite)
CtlRecHndl controlhand;
int yyhilite;
{
myHiliteControl(yyhilite,controlhand);


}

/* To use this you MUST change your Control.h file.  Change the line */
/* extern pascal void HiliteControl() inline(0x1110,dispatcher); */
/* to read ...*/
/* extern pascal void myHiliteControl() inline(0x1110,dispatcher); */