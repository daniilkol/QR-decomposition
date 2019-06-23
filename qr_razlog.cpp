#include "qr_razlog.h"
void transponirovanie(double* a,int n)
{    int i,j;
    double p;
    for (i=0;i<n;i++)
    {
      for(j=i;j<n;j++)
      {
          p=a[i*n+j];
          a[i*n+j]=a[j*n+i];
          a[j*n+i]=p;
      }
    }
}
void func1_stroka (double* a,int n,int i,int j,double b)
{
    int k;
    double* p=a+j*n;
    double* t=a+i*n,h;
    for (k=0;k<n;k++)
    {
       h=t[k];
       p[k]=b*h+p[k];
    }
}
#define MAX_N 8
void print_qr (double* a,double* x,int n)
{
    int i,j,p;
    int n_max=(n>MAX_N?MAX_N:n);
    transponirovanie(x,n);
    for(i=0;i<n_max;i++)
    {
        p=i*n;
        printf("|");
        for(j=0;j<n_max;j++)
            printf("  %.2f",x[p+j]);
        printf("|");
        printf("         ");
        printf("|");
        for(j=0;j<n_max;j++)
            printf("  %.2f",a[p+j]);
        printf("|");
        printf("\n");
    }
    transponirovanie(x,n);
}
/*void func2_stroka (double* a,int n,int i,int j)
{
    int k;
    double p;
    double* t=a+i*n;
    double* h=a+j*n;
    for (k=0;k<n;k++)
    {
      p=t[k];
      t[k]=h[k];
      h[k]=p;
    }
}*/
void func3_stroka (double* a,int n,int i,double b)
{
    int k;
    double* t=a+i*n;
    for (k=0;k<n;k++)
    {
      t[k]=b*t[k];
    }
}
int obratnii_xod (double* a,double* x,int n)
{
    int i,j;
    double tmp;
    for(i=n-1;i>=0;i--)
    {
        tmp=a[i*n+i];
        if(fabs(tmp)<1e-16)
        {
            //printf("Matrica virozgdena\n");?
            return 1;
        }
        func3_stroka(a,n,i,1/tmp);
        func3_stroka(x,n,i,1/tmp);
        for(j=0;j<i;j++)
        {
            func1_stroka(x,n,i,j,-a[j*n+i]);
            a[j*n+i]=0;

        }
    }
    return 0;
}
void stroim_q (double* x,int n,int i,int j,double c,double s)
{
    int k,p=i*n,t=j*n;
    double tmp;
    for (k=0;k<n;k++)
    {
       tmp=x[p+k];
       x[p+k]=c*x[p+k]+s*x[t+k];
       x[t+k]=-s*tmp+c*x[t+k];
    }
}
void change_a (double* a,int n,int i,int j,double c,double s)
{
    int k,p=i*n,t=j*n;
    double tmp;
    for(k=i;k<n;k++)
    {
        tmp=a[p+k];
        a[p+k]=c*a[p+k]+s*a[t+k];
        a[t+k]=-s*tmp+c*a[t+k];
    }
}
int qr_razlog (double* a,double* x,int n)
{
    int i,j,key;
    double cosij,sinij,p,t,kor;
    for(i=0;i<n;i++)
    {
       for(j=i+1;j<n;j++)
        {
            t=a[j*n+i];
            p=a[i*n+i];
            if(fabs(p)<1e-16&&fabs(t)<1e-16)
            {
                sinij=0;
                cosij=1;

            }else
            {
                kor=sqrt(p*p+t*t);
                cosij=p/kor;
                sinij=t/kor;
            }
            change_a(a,n,i,j,cosij,sinij);
            stroim_q(x,n,i,j,cosij,sinij);
        }
    }
    printf("Would you like to print QR decomposition of matrix A? Yes-1,No-0\n");
    scanf("%d",&key);
    if(key)
      print_qr(a,x,n);
    if(obratnii_xod(a,x,n))
        return 1;
    return 0;
}






