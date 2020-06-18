/* Printing routines */
/* Printing is printing, the two machine managers are basically the same in function.  */
/* BUT, the call parameters and structures are different enough to give you fits, so be careful */
#ifdef MAC
#include "paramac.h"
#endif
#ifdef GS
#include "parags.h"
#endif

char playername[19];

/* Inputs : none */
/* Ouputs : none */
PrintScore()
{

int perr;
int papercenter;
Rect mypaperrect;
static char line1[]="\pHas completed";
static char line2[]="\p Steps in Simple Simon.";
#ifdef MAC
GrafPtr oldport;
THPrint myrec;
TPrStatus mystats;
TPPrPort printport;
long fred;
GetPort(&oldport);
MaxMem(&fred);
PrOpen();



myrec=(THPrint)NewHandle(sizeof(TPrint));
PrintDefault(myrec);

#endif

#ifdef GS
int temp;
PrRecHndl myrec;
Handle temphandle;
GrafPortPtr printport;
PrStatusRec mystats;
WindowPtr oldport;
long tlong;
oldport=GetPort();

LoadOneTool(0x13,0x0100);   /* we only load and start the PM when we have to */
/* I'm getting direct page space here using an auxillary ID number.  That way I don't */
/* have to keep track of the handles I allocate in this routine, I can just do a */
/* DisposeAll on the AuxID when I leave the printing job. */
temphandle=NewHandle(0x200L,(_ownerid|0x300),0xC015,0L);

temp = LoWord(*temphandle);
PMStartUp(_ownerid,temp);

tlong=sizeof(PrRec);
myrec=(PrRecHndl)NewHandle(tlong,(_ownerid|0x300),0x0,0L);
PrDefault(myrec);
#endif

NameEntry();  /* get a name to print */

if(PrJobDialog(myrec)){   /* if they said OK */
	PrValidate(myrec);
	mypaperrect=(*(myrec))->prInfo.rPage;
	/* I'm going to take the top 1/3 of this page, box it, and put up the score */
	#ifdef MAC
	mypaperrect.bottom=(mypaperrect.bottom-mypaperrect.top)/3;
	papercenter=(mypaperrect.right-mypaperrect.left)/2;
	#endif
	
	#ifdef GS
	mypaperrect.v2=(mypaperrect.v2-mypaperrect.v1)/3;
	papercenter=(mypaperrect.h2-mypaperrect.h1)/2;
	#endif
	
	/* then come in 2 from the sides... */
	InsetRect(&mypaperrect,2,0);
	#ifdef MAC
	printport=PrOpenDoc(myrec,nil,nil);
	#endif
	
	#ifdef GS
	printport=PrOpenDoc(myrec,nil);
	#endif
	
	perr=PrError();
	
	if(!perr)PrOpenPage(printport,nil);

	FrameRect(&mypaperrect); 
	/* Now print the player's name */
	/* centered horizontally, please */
	MoveTo((papercenter-(StringWidth(playername)/2)),30);
	DrawString(playername);
	MoveTo((papercenter-(StringWidth(line1)/2)),44);
	DrawString(line1);
	MoveTo(papercenter,58);
	WriteNum(CurrentScore);
	MoveTo((papercenter-(StringWidth(line2)/2)),72);
	DrawString(line2);
	
	
	if(!perr)PrClosePage(printport);
	
	
	PrCloseDoc(printport);
	perr=PrError();
	#ifdef MAC
	if(!perr)PrPicFile(myrec,nil,nil,nil,&mystats);
	#endif
	#ifdef GS
	if(!perr)PrPicFile(myrec,nil,&mystats);
	#endif
	
	
	
	
}




#ifdef MAC
PrClose();
DisposHandle((Handle)myrec);
MaxMem(&fred);  /* crunch everything again */
#endif
#ifdef GS

PMShutDown();
UnloadOneTool(0x13);  /* and get rid of the memory it used */
DisposeAll(_ownerid|0x300);
CompactMem();	/* compact anything that got moved during printing */
#endif
SetPort(oldport);




}



#ifdef GS
/* The name-getting dialog box structure for the GS */


char item00pointername[] = "\p\
Fred";

ItemTemplate 
item00name  = {              /* Name as needed */            
      0x0003,       /* Item ID number */             
	  021,080,034,363,  /* Bounding rectangle */       
      0x0011,         /* item type */          
      item00pointername, /* Item descriptor */      
	  18,             /* Item value */       
      0x0000,            /* Item bit flag */       
      NULL,               };  /* Item color table */  



char item01pointername[] = "\p\
Please enter your name;";
ItemTemplate 
item01name  = {              /* Name as needed */            
      0x0064,       /* Item ID number */             
	  3,129,13,297,  /* Bounding rectangle */       
      0x000F,         /* item type */          
      item01pointername, /* Item descriptor */      
	  0,             /* Item value */       
      0x0000,            /* Item bit flag */       
      NULL,               };  /* Item color table */  


char item02pointername[] = "\p\
Done";

ItemTemplate 
item02name  = {              /* Name as needed */            
      0x0001,       /* Item ID number */             
	  37,184,50,254,  /* Bounding rectangle */       
      0x000A,         /* item type */          
      item02pointername, /* Item descriptor */      
	  0000,             /* Item value */       
      0x0000,            /* Item bit flag */       
      NULL,               };  /* Item color table */  







DialogTemplate nameDialogBox ={                              
         32, 108,  87, 565, /* bounding rectangle */       
		 -1,              /* Visibility Flag */     
		 NULL,             /* RefCon */                    
		 &item00name,             /* item pointer */   
		 &item01name,             /* item pointer */   
		 &item02name,             /* item pointer */   
         NULL    };          /* Null terminator */  



#endif





/* Inputs : none */
/* Ouputs : none */
/* Ask for a name and saves it in playername[] */
 NameEntry()
	{ short hititem;
	DialogPtr namepointer;
	short itemtype;
	Rect itemrect;
	Handle itemhandle;
	
	Boolean flg;
	hititem=0;
	flg=true;
	#ifdef MAC
	namepointer=GetNewDialog(9876,nil,(WindowPtr)-1);
	GetDItem(namepointer,3,&itemtype,&itemhandle,&itemrect);
	#endif
	#ifdef GS
	namepointer=GetNewModalDialog(&nameDialogBox);
	#endif
	
	while(flg){
		while(hititem!=1){
			#ifdef MAC
			ModalDialog((ModalFilterProcPtr)nil,&hititem);
			#endif
			#ifdef GS
			hititem=ModalDialog(0L);
			#endif
			/* restrict name to 18 characters, just because. The GS edit line item does it
			     automatically, you have to check on every edit line hit for the Mac .*/
			#ifdef MAC
			if(hititem==3){
				GetIText(itemhandle,&playername);				
				if(playername[0]>18){
					ErrorSound(0L);playername[0]=18;
					SetIText(itemhandle,&playername);
					}
				}
			#endif			
			}
		#ifdef MAC
		GetIText(itemhandle,&playername);
		#endif
		#ifdef GS
		GetIText(namepointer,3,playername);
		#endif
		
		if(playername[0])flg=false;
		hititem=99;
		}
	#ifdef MAC
	DisposDialog(namepointer);
	#endif
	#ifdef GS
	CloseDialog(namepointer);
	#endif
	
}   
