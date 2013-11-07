#include "header_file.c"

int main()
{
    int selection=0;
    int conti=0; //continue?
    
    do
    {
        printf("============\n"
               "1) BTC\n"
               "2) psnr\n"
               "============\n");
        scanf("%d",&selection);
        
        switch(selection)
        {
              case 1:
                     set();
                     break;
              case 2:
                     psnr();
                     break;
              default:
                      printf("ERROR!\n");
        }
        
        printf("continue:\n"
               "1.YES 2.NO\n");
        scanf("%d",&selection);
        if(selection==1)
        conti=1;
        else
        conti=0;
    }while(conti==1);
    
    return 0;
}
