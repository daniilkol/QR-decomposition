#include "proverka.cpp"
#include "qr_razlog.cpp"
void delnewline(char* buf)
{
    int i;
    for(i=0;buf[i];i++)
        if (buf[i]=='\n')
        {
            buf[i]=0;
            break;
        }
}
//TEST DR
/*
double f(int i,int j,int n)
{

    if(i<n/2&&j<n/2)
    {
        if(j-i==1)
            return 2;
        if(i==j)
            return 1;
    }
    if(i+j==(3*n)/2-1)
      return 1;
    return 0;
}
*/
double f(int i,int j,int n)
{
    (void)n;
    return fabs(i-j);
}
void init_matrix (double* a,int n)
{
    int i,j,p;
    for(i=0;i<n;i++)
    {
       p=i*n;
       for(j=0;j<n;j++)
          a[p+j]=f(i,j,n);
    }

}
#define MAX_N 8
void print_matrix(double* a,int n)
{
    int i,j,p;
    int n_max=(n>MAX_N?MAX_N:n);
    for(i=0;i<n_max;i++)
    {
        p=i*n;
        for(j=0;j<n_max;j++)
            printf("  %.2f",a[p+j]);
        if(n_max==MAX_N)
            printf("... %.2f",a[p+n-1]);
        printf("\n");
    }
}
int main()
{
    int key,n;
    double* a,*copy_of_a;
    double time;
    printf("Input the way of filling the matrix\n");
    printf("Please, write 0 for filling by formula or 1 for filling from the file\n");
    if(scanf("%d",&key)!=1)
    {
        printf("Cannot read your key,sorry\n");
        return 1;
    }
    if (key==1)
       {
          //const char* name="a.txt";
          char name[1024];
          printf("Input the name of file:\n");
          scanf("%s",name);
          delnewline(name);
          FILE*fp;
          if(!(fp=fopen(name,"r")))
          {
              printf("Check your filename,please\n");
              return -1;
          }
          int i,j;
          if(fscanf(fp,"%d",&n)!=1)
          {
              printf("Cannot read your n,sorry\n");
              return -2;
          }
          //printf("%d\n",n);
          if(n<0)
          {
              printf("Your n is negative, sorry\n");
              return -3;
          }
          a=new double[n*n];
          for(i=0;i<n;i++)
              for(j=0;j<n;j++)
              {
                  if(fscanf(fp,"%lf",a+i*n+j)!=1)
                  {
                      printf("Cannot read %s\n",name);
                      fclose(fp);
                      delete [] a;
                      return -2;
                  }
              }
          fclose(fp);
          }
          else
          {
              printf("Input the n for matrix:\n");
              if(scanf("%d",&n)!=1)
              {
              printf("Cannot read your n,sorry\n");
              return -2;
              }
              if(n<0)
              {
                  printf("Your n is negative, sorry\n");
                  return -3;
              }
              a=new double[n*n];
              init_matrix(a,n);
          }
    printf("MATRIX A BEFORE:\n");
    print_matrix(a,n);
    copy_of_a=new double[n*n];
    int k,l;
    for(k=0;k<n;k++)
        for(l=0;l<n;l++)
        copy_of_a[k*n+l]=a[k*n+l];
    double* x;
    x=new double[n*n];
    int i,j,p;
    for(i=0;i<n;i++)
    {
        p=i*n;
        for(j=0;j<n;j++)
        {
            if(i==j)
                x[p+j]=1;
            else x[p+j]=0;
        }
    }
    //printf("MATRIX X BEFORE:\n");
    //print_matrix(x,n);
    time=clock();
    if(qr_razlog(a,x,n))
    {
        printf("Sorry,matrix is degenerative, so there is no reverse matrix\n");
        delete[] x;
        delete [] a;
        delete [] copy_of_a;
        return -4;
    }
    time=(clock()-time)/CLOCKS_PER_SEC;
    printf("Elapsed time for algorithm=%.6f\n",time);
    printf("MATRIX A AFTER:\n");
    print_matrix(a,n);
    printf("REVERSE MATRIX:\n");
    print_matrix(x,n);
    time=clock();
    printf("NEVYAZKA=%e\n",nevyazka(copy_of_a,x,a,n));
    time=(clock()-time)/CLOCKS_PER_SEC;
    printf("Elapsed time for counting discrepancy=%.6f\n",time);
    delete[] x;
    delete [] a;
    delete [] copy_of_a;
    return 0;
}
