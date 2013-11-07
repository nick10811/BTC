#include "header_file.c"

int psnr()
{
    int i=0; //number of loop 
    double sum=0; //sum of squared differences 
    double mse=0;
    double psnr=0;
    
    unsigned char path[2][100];

    struct stat f_stat[2];
    
    FILE *fp_1, *fp_2;
    
    printf("Input file 1 path:");
    scanf("%s",path[0]);
    printf("Input file 2 path:");
    scanf("%s",path[1]);
    
    fp_1=fopen(path[0],"rb");
    fp_2=fopen(path[1],"rb");
    
    stat(path[0],&f_stat[0]);
    stat(path[1],&f_stat[1]);
    
    unsigned char file_read[2][f_stat[0].st_size];
    
    fread(file_read[0],sizeof(char),f_stat[0].st_size,fp_1);
    fread(file_read[1],sizeof(char),f_stat[1].st_size,fp_2);
    
    for(i=0;i<f_stat[0].st_size;i++)
       sum+=pow((file_read[0][i]-file_read[1][i]),2);
    mse=sum/f_stat[0].st_size;
    psnr=10*log10((pow(255,2)/mse));
    
    printf("PSNR:%f\n",psnr);
	
    fclose(fp_1);
	fclose(fp_2);
	
    return 0;
}
