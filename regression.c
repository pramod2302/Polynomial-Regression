#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <string.h>


int main(int argc, char **argv) {

  double *x, *y;
  int i,n,xx;
  FILE *infile;
  char filename[255];

  strcpy(filename,argv[1]);
  
  
  infile = fopen(filename, "r");
  if (infile == NULL) printf("error opening file\n");    
  fscanf (infile, "%d", &n);
  x = (double *) malloc (n*sizeof(double));
  y = (double *) malloc (n*sizeof(double));
  

  
  
  for (i=0; i<n; i++) {
    fscanf (infile, "%lf %lf", &x[i], &y[i]);
	}

  int exp,j;
  printf("enter the order of the equation\n");
  scanf("%d",&exp);

  double powers[exp*2+1][n];
  for (i=0;i<exp*2+1;i++)
  	for (j=0;j<n;j++)
  	{
  		powers[i][j]=pow(x[j],i+1);
  	}

  	for (i=0;i<exp*2+1;i++)
  	{
  		printf("\n");
  		for (j=0;j<n;j++)
  		{
  			printf("%lf		",powers[i][j]);
  		}  	
  	}
  printf("\n");
  printf("\n");

  double sumx[exp*2+1],count=0;
 
  j=0;
  for (i=0;i<exp*2+1;i++)
  {
  		sumx[i]=0;
  	for (j=0;j<n;j++)
  	{
  		sumx[i]=sumx[i]+powers[i][j];
  		
  	}
  	printf("Summation t^ %d = %lf	\n",i,sumx[i]);
  } 


  //for (i=0;i<exp*2+1;i++)
  	//printf ("Summation x^%d = %lf	\n",i,sumx[i]);
  		  printf("\n");
  printf("\n");
  
  double sumxt[exp+1];
  sumxt[0]=0.0;
  for (i=0;i<n;i++)
  	sumxt[0]=sumxt[0]+y[i];
  for (i=0;i<exp;i++)
  {
  		sumxt[i+1]=0;
  	for (j=0;j<n;j++)
  	{
  		sumxt[i+1]=sumxt[i+1]+powers[i][j]*y[j];
  	}
  	printf ("Summation y * x^%d = %4lf	\n",i,sumxt[i]);
  }


 printf("\n");
  printf("\n");
 //for (i=0;i<exp+1;i++)
  //	printf ("Summation y * x^%d = %4lf	\n",i,sumxt[i]);



double mat[exp+1][exp+1];
for (i=0;i<exp+1;i++)
{
	for (j=0;j<exp+1;j++)
	{
		if (i==0 && j==0)
			mat[i][j]=n;
		else
			mat[i][j]=sumx[i+j-1];
	}
}

printf("\n");
  printf("\n");
FILE *fd = fopen("intermediate.txt","w");
fprintf(fd," %d\n",(exp+1));
for (i=0;i<exp+1;i++)
  	{
  		printf("\n");
  		for (j=0;j<exp+1;j++)
  		{
  			printf("%4lf		",mat[i][j]);
  			fprintf(fd," %lf",mat[i][j]);
  		}  	
  		fprintf(fd," %lf\n",sumxt[i]);
  	}
  	pclose(fd);




  	int k=0;
  	i=0;
    FILE *fp;
    
    fp = fopen("intermediate.txt","r");

    fscanf(fp,"%d",&n);

    float A[n+1][n+1],c,x1[n+1],sum=0.0;

    for(i=1; i<=n; i++)
    {
        for(j=1; j<=(n+1); j++)
        {
            fscanf(fp, "%f",&A[i][j]);
        }
    }
fclose(fp);



    for(j=1; j<=n; j++) /* loop for the generation of upper triangular matrix*/
    {
        for(i=1; i<=n; i++)
        {
            if(i>j)
            {
		//Step 1:
                c=A[i][j]/A[j][j];

		//Step 2:
                for(k=1; k<=n+1; k++)
                {
                    A[i][k]=A[i][k]-c*A[j][k];
                }
            }
        }
    }
    x1[n]=A[n][n+1]/A[n][n];
    /* this loop is for backward substitution*/
    for(i=n-1; i>=1; i--)
    {
        sum=0;
        for(j=i+1; j<=n; j++)
        {
            sum=sum+A[i][j]*x1[j];
        }
        x1[i]=(A[i][n+1]-sum)/A[i][i];
    }
    printf("\nThe solution is: \n");
    for(i=1; i<=n; i++)
    {
        printf("\nx%d=%f\t",i,x1[i]); /* x1, x2, x3 are the solutions*/
    }
    
    double value[20];
    for (j=0;j<20;j++)
    {	value[j]=0.0;
    for (i=0;i<exp+1;i++)
    {
    	value[j]=value[j]+x1[i]*pow(x[j],(exp-i));
    }
}



    printf ("\nvalues are\n");
    printf("\n x \t\t y \t\t value of y from regression \t\t abs error \t sum of squares error");
    for (i=0;i<20;i++)
    {
    	double error = abs(y[i]-value[i]);
    	double sqerror = abs (y[i]*y[i] + value[i]*value[i]);
    	printf("\n%lf\t %lf\t \t\t%lf \t \t%lf \t\t %lf",x[i],y[i],value[i], error, sqerror);
    }



   
    return(0);


















  	
  	

}
