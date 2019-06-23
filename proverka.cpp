#include "proverka.h"
void matrix_x_matrix (double* a,double* b,double* c,int n)
{
    int i,j,t,p;
    double sum=0;
    for (i=0;i<n;i++)
    {
       p=i*n;
       for(j=0;j<n;j++)
          {
              for(t=0;t<n;t++)
                sum+=a[p+t]*b[t*n+j];
              c[p+j]=sum;
              sum=0;
          }
    }
}
double norma (double* a,int n)
{
    int i,j;
    double p,max=0;
    for (i=0;i<n;i++)
    {
        p=0;
        for(j=0;j<n;j++)
            p+=fabs(a[i*n+j]);
        if (p>max)
            max=p;
    }
    return max;
}
double nevyazka (double* a,double* x,double* c,int n)
{
    int i;
    double p;
    matrix_x_matrix(a,x,c,n);
    for(i=0;i<n;i++)
        c[i*n+i]=c[i*n+i]-1;
    p=norma(c,n);
    return p;

}
