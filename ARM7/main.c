#include <stdio.h>
#include <stdlib.h>
 unsigned char check_Register(char BX[],int start_index);
unsigned char BX_ins[4]={0xE1,0x2f,0xff,0x10};
char BX[10]="BXR";
int main()
{
    char ch[10]={0};
    char flag=0,rn=0;;
    FILE*fread;
    FILE*fwrite;

    fread=fopen("ASMFILE.txt","r");
    fwrite=fopen("MACHINEFILE.txt","w");
    if (fread == NULL || fwrite == NULL)
    {
        printf("Error! Could not open file\n");
        exit(-1); // must include stdlib.h
    }

        fscanf(fread,"%[^\n]%s",ch);
            removeSpaces(ch);
            printf("%s",ch);

           for(int i=0;i<3;i++)
           {
               if(ch[i]==BX[i])
               {
                flag++;

               }
           }

           if(flag==3)
           {
               rn=check_Register(ch,3);
               BX_ins[3]|=rn;
               for(int i=0;i<4;i++)
               {
                   fprintf(fwrite,"%x",BX_ins[i]);
               }
          }
          else
          {
              fprintf(fwrite,"#### invalid operation");
          }

    fclose(fread);
    fclose(fwrite);

    return 0;
}

void removeSpaces(char *str)
{
    // To keep track of non-space character count
    int count = 0;

    // Traverse the given string. If current character
    // is not space, then place it at index 'count++'
    for (int i = 0; str[i]; i++)
        if (str[i] != ' ')
            str[count++] = str[i]; // here count is
                                   // incremented
    str[count] = '\0';
}
 unsigned char check_Register(char BX[],int start_index)
 {
     unsigned char reg_val=0;
    for(int i=start_index;BX[i]!=0;i++)
     {

         reg_val=(BX[i]-48)+reg_val*10;

     }

     return reg_val;
 }
// test for files not existing.

// write to file vs write to screen

// read from file/keyboard. remember the ampersands!

