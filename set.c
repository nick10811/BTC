#include "header_file.c"
void bit_map();

const block_array[2]={2,4};

unsigned char h_path[100];
unsigned char d_path[100]; //file path of destination

struct stat f_stat;

int h_size; //host size
int b_size; //block size

int set()
{
    int selection=0;
    
    printf("============\n"
           "block size:\n"
           "1) 2\n"
           "2) 4\n"
           "============\n");
    scanf("%d",&selection);
    b_size=block_array[selection-1];
    
    printf("Input file path of host:");
    scanf("%s",h_path);
    
    stat(h_path,&f_stat);
    h_size=sqrt(f_stat.st_size);
    
    printf("Input file path of destination:");
    scanf("%s",d_path);
    
    bit_map();
    
    return 0;   
}

void bit_map()
{
     int b_num=0; 
     int hb_num=h_size/b_size;
    
     unsigned char *h_array; //host array
     unsigned char *bm_array; //bit map array
    
     struct set_pixel
     {
            int count_0;
            int count_1;
            int avg_0;
            int avg_1;
     }bitmap_stat[hb_num*hb_num];
    
     FILE *h_fp, *d_fp;
    
     h_fp=fopen(h_path,"rb");
     h_array=(char *)calloc(h_size*h_size,sizeof(char));
     fread(h_array,sizeof(char),h_size*h_size,h_fp);
     fclose(h_fp);
     
     d_fp=fopen(d_path,"wb");
     bm_array=(char *)calloc(h_size*h_size,sizeof(char));
    
     int row,column;
     int row_max,column_max;
    
     for(b_num=0;b_num<(hb_num*hb_num);b_num++)
     {
        int sum=0;
        int avg=0; //average
        row_max = (b_num/hb_num+1)*b_size;
        column_max = (b_num%hb_num+1)*b_size;
        
        bitmap_stat[b_num].count_0=0;
        bitmap_stat[b_num].count_1=0;
        bitmap_stat[b_num].avg_0=0;
        bitmap_stat[b_num].avg_1=0;
        
        for(row=(b_num/hb_num)*b_size;row<row_max;row++)
           for(column=(b_num%hb_num)*b_size;column<column_max;column++)
              sum+=*(h_array+row*h_size+column);
        avg=sum/(b_size*b_size);
        
        /*bit map*/
        for(row=(b_num/hb_num)*b_size;row<row_max;row++)
           for(column=(b_num%hb_num)*b_size;column<column_max;column++)
           {
              if(*(h_array+row*h_size+column)>=avg)
              {
                 *(bm_array+row*h_size+column)=1;
                 bitmap_stat[b_num].count_1++;
                 bitmap_stat[b_num].avg_1+=*(h_array+row*h_size+column);
              }
              else
              {
                  *(bm_array+row*h_size+column)=0;
                  bitmap_stat[b_num].count_0++;
                  bitmap_stat[b_num].avg_0+=*(h_array+row*h_size+column);
              }
           }
        bitmap_stat[b_num].avg_1/=bitmap_stat[b_num].count_1;
        if(bitmap_stat[b_num].count_0) //avoid a situation of pixels in block are same 
           bitmap_stat[b_num].avg_0/=bitmap_stat[b_num].count_0;
     }
    
     /*Re-build Image*/
     for(b_num=0;b_num<(hb_num*hb_num);b_num++)
     {
         row_max = (b_num/hb_num+1)*b_size;
         column_max = (b_num%hb_num+1)*b_size;
        
        for(row=(b_num/hb_num)*b_size;row<row_max;row++)
            for(column=(b_num%hb_num)*b_size;column<column_max;column++)
            {
                 if(*(bm_array+row*h_size+column)==1)
                    *(bm_array+row*h_size+column)=bitmap_stat[b_num].avg_1;
                 else
                     *(bm_array+row*h_size+column)=bitmap_stat[b_num].avg_0;
            }
     }
    
    fwrite(bm_array,sizeof(char),h_size*h_size,d_fp);
    fclose(d_fp);
    free(h_array);
    free(bm_array);
}
