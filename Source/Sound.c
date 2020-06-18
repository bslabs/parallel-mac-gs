#ifdef GS
#include "parags.h"
#include <notesyn.h>

/* a very simple instrument */
Instrument myinst = {
	0x7f,    
	0x7f00,     
	0,   
	0x80,    
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0, 
	1,    
	0x32,    
	0,  
	0x0,     
	0x0,  
	0x0,     
	1,     
	1,  /* bWaveCount;  Instrument -   */
	{0x7f, 0xf0,1,0,0},  /*   Waveform aWaveList[aWCount]; */
	{0x7f, 0xf0,1,0,0}
};
















/* Inputs : note value */
/* Ouputs : none */
note(noteis)
int noteis;
{
int gentouse;
long startticks;
long nowticks;
startticks=TickCount();
AllNotesOff();  /* so they don't step on each other */
gentouse=AllocGen(0x80);  /* a high priority please */
NoteOn(gentouse,noteis,0x7f,&myinst);

/* wait a few ticks */
nowticks=TickCount();
while((nowticks-startticks)<15){
nowticks=TickCount();}
}


/* Inputs : none */
/* Ouputs : none */
/* create a wave and stuff it into DOC RAM */
InitBell()
{Ptr mywave;
Handle temphandle;
int qq;
char val;
Boolean goingup;
goingup=true;
val=0x20;

/* if your always going to use pointers, C's malloc works fine */
/*  as in mywave=malloc(0x100); */
/*  But we'll use NewHandle here to emphasis the differences in the two machines */
/* 	that you need to keep aware of */
temphandle=NewHandle(0x100L,_ownerid,0x8010,0L);
/*  one locked, non-bank crossing handle $100 bytes long */

/* on the Mac, the same thing would be done by...
	temphandle=NewHandle(0x100);
	HLock(temphandle);
	or by using the pointer routine...
	mywave=NewPtr(0x100);
*/
mywave=*temphandle;

for(qq=0;qq<0x0100;qq++){	/* making a little triangle wave */
*(mywave+qq)=val;
if(goingup){val++;
if(val==0x7f)goingup=false;}
else{ val--;
if(val==0x20)goingup=true;}

}
/* move the thing */
WriteRamBlock(mywave,0xf000,0x100);
/* If we were using malloc... */
/*   free(fred);  */

/* unuse the space */
DisposeHandle(temphandle);
/* on the Mac, freeing the space would take place with either
	DisposHandle(temphandle);
	or
	DisposPtr(mywave);
	In either case, GS programmers should note that it's spelled
	DisposHandle, _not_ DisposeHandle
	*/
}

#endif

#ifdef MAC
#pragma load "paraheaders"

Wave BellWave;


long Scale[4]={

0x26370,
0x44176,
0x55ca2,
0x808a1
};




FTSoundRec myTrec = {
   0, /* short duration;  */ 
   2, /* Fixed sound1Rate; */ 
   0, /* long sound1Phase;*/ 
   0, /* Fixed sound2Rate; */ 
   0, /* long sound2Phase; */ 
   0, /* Fixed sound3Rate; */
   0, /* long sound3Phase; */
   0, /* Fixed sound4Rate; */
   0, /* long sound4Phase; */
   &BellWave, /* WavePtr sound1Wave; */
   &BellWave, /* WavePtr sound2Wave; */ 
   &BellWave, /* WavePtr sound3Wave; */
   &BellWave, /* WavePtr sound4Wave; */
};

FTSynthRec mytones = {
ftMode,
&myTrec};

/* Inputs : note index */
/* Ouputs : none */
void note(mynote)
int mynote;
{
long nowticks;
long startticks;

startticks=TickCount();
myTrec.duration=2*5;   

myTrec.sound1Rate=(Fixed)mynote;	
myTrec.sound2Rate= (Fixed)mynote; 
myTrec.sound3Rate=(Fixed)mynote;
myTrec.sound4Rate=(Fixed)mynote; 

StartSound((Ptr)&mytones,255,(SndCompletionProcPtr)-1);
while(!SoundDone())/* do nothing */;

/* wait a bit.  Or a byte */
nowticks=TickCount();
while((nowticks-startticks)<15){
nowticks=TickCount();}



StopSound();


}





/* Inputs : none */
/* Ouputs : none */
InitBell()
{ register qq;
unsigned char tom=0x80;
Boolean switg=true;
for(qq=0;qq<256;qq++){
BellWave[qq]=tom;
if(switg!=true){tom=tom+2;if(tom>0xf0)switg=true;}
if(switg){tom=tom-2;if(tom<10)switg=false;}
}}

#endif