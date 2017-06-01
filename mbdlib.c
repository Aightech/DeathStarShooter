
#include <stdio.h>
#include "mbdlib.h"
#include "struct.h"
#include "unistd.h"
#include <iostream>

//#include <unistd.h>



void initPantilt(Pantilt *pnt)
{
       pnt->archPro=open("/dev/ttyACM0", O_RDWR | O_NOCTTY);
       pnt->str[4]=',';
       pnt->str[8]='\0';
       if(pnt->archPro!=0)  // check if we succeeded
              //return -1;
       printf("Communication started\n");
}


int movePantilt(Pantilt *pnt)
{
       int fact=100;
       for(int i=0;i<3;i++)
       {
              pnt->str[i]='0'+((int)pnt->posM1/fact)%10;
              pnt->str[i+4]='0'+((int)pnt->posM2/fact)%10;
              fact=fact/10;
       }
       write(pnt->archPro,pnt->str,8);
}
