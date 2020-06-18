#ifdef MAC 
#include "paramac.h"
#endif
#ifdef GS
#include "parags.h"
#endif
/* Dialog event handling is very similar on both machines.  However, one */
/*	 of the major differences is in the use of Dialog resources.  The gs */
/*	 does not have any dialog resource types defined, and there are      */
/*	 no mechanisms in the gs Dialog Manager to support resources.        */
/*	 So you have two choices;											 */ 
/*	 1) Use the Dialog Manager and just create your structures in memory */
/*	 2) Use an alert window and modify your event loop                   */
/*	 For the purposes of this program, I'll take the first path.         */

/* Here's all the gs dialog templates we'll be using */
#ifdef GS
char item01pointertrya[] = "\p\
OK";
char item00pointertrya[] = "\p\
Ooops, first mistake!\r\
You have one more chance";



ItemTemplate 
item00trya  = {              /* Name as needed */            
	      0x0064,       /* Item ID number */             
		  002,18,30,210,  /* Bounding rectangle */       
		  0x800F,         /* item type */          
		  item00pointertrya, /* Item descriptor */      
		  00,             /* Item value */       
		  0x0000,            /* Item bit flag */       
		  NULL,               };  /* Item color table */  


ItemTemplate 
item01trya  = {              /* Name as needed */            
      0x0001,       /* Item ID number */             
	  32,074,0,0,  /* Bounding rectangle */       
      0x000A,         /* item type */          
      item01pointertrya, /* Item descriptor */      
	  0000,             /* Item value */       
      0x0000,            /* Item bit flag */       
      NULL,               };  /* Item color table */  






AlertTemplate TryBox = {                            
         32,  20,  90, 266, /* rectangle */           
		 0x02,             /* alert id */               
		 0x80,           /* stage byte */             
		 0x80,           /* stage byte */             
		 0x80,           /* stage byte */             
		 0x80,           /* stage byte */                
		 &item00trya,             /* item pointer */   
		 &item01trya,             /* item pointer */   
         NULL    };          /* Null terminator */  



char item02pointerfail[] = "\p\
Print my score";
char item01pointerfail[] = "\p\
OK";
char item00pointerfail[] = "\p\
                     Too many misses!\r\
You completed a ^0 step long sequence.\r\
See if you can do better next time!";

ItemTemplate 
item00fail  = {              /* Name as needed */            
      0x0064,       /* Item ID number */             
	  001,005,40,286,  /* Bounding rectangle */       
      0x800F,         /* item type */          
      item00pointerfail, /* Item descriptor */      
	  0112,             /* Item value */       
      0x0000,            /* Item bit flag */       
      NULL,               };  /* Item color table */  


ItemTemplate 
item01fail  = {              /* Name as needed */            
      0x0001,       /* Item ID number */             
	  42,13,0,0,  /* Bounding rectangle */       
      0x000A,         /* item type */          
      item01pointerfail, /* Item descriptor */      
	  0000,             /* Item value */       
      0x0000,            /* Item bit flag */       
      NULL,               };  /* Item color table */  
ItemTemplate
item02fail  = {              /* Name as needed */            
      0x0003,       /* Item ID number */             
	  42,160,0,0,  /* Bounding rectangle */       
      0x000A,         /* item type */          
      item02pointerfail, /* Item descriptor */      
	  0000,             /* Item value */       
      0x0000,            /* Item bit flag */       
      NULL,               };  /* Item color table */  





AlertTemplate ScoreBox = {                            
         31,  92,  100, 400, /* rectangle */           
		 0x03,             /* alert id */               
		 0x80,           /* stage byte */             
		 0x80,           /* stage byte */             
		 0x80,           /* stage byte */             
		 0x80,           /* stage byte */                
		 &item00fail,             /* item pointer */   
		 &item01fail,             /* item pointer */ 
		 &item02fail,
         NULL    };          /* Null terminator */  








char item02pointerabou[] = "\p\
Written in MPW CIIGS and MPW C\r\
by\r\
C.K. Haun <TR>\r\
Copyright 1990, Apple Computer, Inc.";


char item03pointerabou[] = "\p\
Thanx";
char item00pointerabou[] = "\p\
Paralell";
char item01pointerabou[] = "\p\
A demonstration of Mac <=> GS\r\
paralell development.";


ItemTemplate 
item00abou  = {              /* Name as needed */            
      0x0064,       /* Item ID number */             
	  6,112,16,175,  /* Bounding rectangle */       
      0x800F,         /* item type */          
      item00pointerabou, /* Item descriptor */      
	  0008,             /* Item value */       
      0x0000,            /* Item bit flag */       
      NULL,               };  /* Item color table */  


ItemTemplate 
item01abou  = {              /* Name as needed */            
      0x0064,       /* Item ID number */             
	  25,57,45,269,  /* Bounding rectangle */       
      0x800F,         /* item type */          
      item01pointerabou, /* Item descriptor */      
	  0051,             /* Item value */       
      0x0000,            /* Item bit flag */       
      NULL,               };  /* Item color table */  


ItemTemplate 
item02abou  = {              /* Name as needed */            
      0x0064,       /* Item ID number */             
	  48,11,92,292,  /* Bounding rectangle */       
      0x800F,         /* item type */          
      item02pointerabou, /* Item descriptor */      
	  79,             /* Item value */       
      0x0000,            /* Item bit flag */       
      NULL,               };  /* Item color table */  


ItemTemplate 
item03abou  = {              /* Name as needed */            
      0x0001,       /* Item ID number */             
	  96,111,109,189,  /* Bounding rectangle */       
      0x000A,         /* item type */          
      item03pointerabou, /* Item descriptor */      
	  0000,             /* Item value */       
      0x0000,            /* Item bit flag */       
      NULL,               };  /* Item color table */  


AlertTemplate AboutBox = {                            
         30,  20, 150, 363, /* rectangle */           
		 15999,             /* alert id */               
		 0x80,           /* stage byte */             
		 0x80,           /* stage byte */             
		 0x80,           /* stage byte */             
		 0x80,           /* stage byte */                
		 &item00abou,             /* item pointer */   
		 &item01abou,             /* item pointer */   
		 &item02abou,             /* item pointer */   
		 &item03abou,             /* item pointer */   
         NULL    };          /* Null terminator */  



#endif








/* Input : none */
/* Ouput : none */
void AboutPara()
{

#ifdef MAC
Alert(15999,0);   /* resource */
#endif
#ifdef GS
Alert((Ptr)&AboutBox,0L);  /* template */
InvalRect(&activewindow->portRect);
#endif
}

/* Input : score */
/* Ouput : none */
int DisplayScore(thescore)
int thescore;
{
char thetextscore[4];
/* GS number conversion routine recommends that the text buffer you're filling */
/* should be initialized with spaces, so we may as well do it with both. */
strcpy(thetextscore,"    ");



#ifdef GS
Int2Dec(thescore,thetextscore+1,3,0);
thetextscore[0]=3;
#endif
#ifdef MAC
NumToString((long)thescore,&thetextscore);
#endif
ParamText(thetextscore,"","","");
#ifdef GS
return(Alert((Ptr)&ScoreBox,0L));  /* template */
#endif
#ifdef MAC
return(Alert(15997,0)); 					/* resource */
#endif

}

/* Input : none */
/* Ouput : none */
SayTryAgain()
{
#ifdef MAC
Alert(15998,0);   /* resource */
#endif
#ifdef GS
Alert((Ptr)&TryBox,0L);  /* template */
#endif

}
