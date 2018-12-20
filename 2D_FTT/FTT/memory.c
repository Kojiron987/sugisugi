/* ----------------------------------------------------------------------
   memory.c

   malloc_2D
   malloc_3D
   free_2D
   free_3D

   May/09/'03 A.Sugimura
   Jan./10/'04 A.Sugimura
   ---------------------------------------------------------------------- */
#include <stdio.h>
#include <stdlib.h>

#define NR_END 1
#define FREE_ARG char*

void   nrerror(char error_text[]);
char   **malloc_2D( int x_size, int y_size, int size );
char   ***malloc_3D( int x_size, int y_size, int t_size, int size);
int    free_2D( int y_size, char **p);
int    free_3D( int y_size, int t_size, char ***p );
double **dmatrix(long nrl, long nrh, long ncl, long nch);
void   free_dmatrix(double **m, long nrl, long nrh, long ncl, long nch);

/* ------------------------------------------------------------ */
void nrerror(char error_text[])
{
  fprintf(stderr,"Numerical Recipes run-time error...\n");
  fprintf(stderr,"%s\n", error_text);
  fprintf(stderr,"..now exiting to system...\n");
  exit(1);
}

/* ------------------------------------------------------------ */
int free_2D( int y_size, char **p)
{
  while( --y_size >= 0 )
    free( p[y_size] );
  free( p );
  return 0;
}

/* ------------------------------------------------------------ */
int free_3D( int y_size, int t_size, char ***p )
{
  while( --t_size >= 0 )
    free_2D( y_size, p[t_size] );
  free( p );
  return 0;
}

/* ------------------------------------------------------------ */
char **malloc_2D( int x_size, int y_size, int size )
{
  char **p;

  p = (char **)malloc( sizeof *p * y_size);
  if( p == (char **) NULL )
    return (char **)NULL;
  else{

    int  y;

    for( y=0 ; y < y_size ; ++y )
      if( (p[y]=(char *)malloc(sizeof **p * x_size * size))
          == (char *)NULL ){
        while ( y > 0 )
          free( p[--y] );
        free( p );
        return (char **)NULL;
      }
    return (char **)p;
  }  
}

/* ------------------------------------------------------------ */
char ***malloc_3D( int x_size, int y_size, int t_size, int size)
{
  char ***p = (char ***)malloc( sizeof *p * t_size);

  if( p == (char ***)NULL )
    return (char ***)NULL;
  else{

    int  t;

    for( t=0 ; t < t_size ; ++t )
      if( ( p[t]=(char **)malloc_2D(x_size, y_size, size) )
           == (char **)NULL ){
        while( t > 0 )
          free_2D( y_size, p[--t] );
        free( p );
        return (char ***)NULL;
      }
    return (char ***)p;
  }
}

/* ---------------------------------------------------------------------- */
double **dmatrix(long nrl, long nrh, long ncl, long nch)
{
  long   i, nrow=nrh-nrl+1, ncol=nch-ncl+1;
  double **m;

  m=(double **)malloc((size_t)((nrow + NR_END)*sizeof(double*)));
  if (!m) nrerror("allocation failure 1 in matrix()");
  m += NR_END;
  m -= nrl;

  m[nrl]=(double *)malloc((size_t)((nrow*ncol+NR_END)*sizeof(double)));
  if (!m[nrl]) nrerror("allocation failure 2 in matrix()");
  m[nrl] += NR_END;
  m[nrl] -= ncl;

  for(i=nrl+1; i<=nrh; i++) m[i]=m[i-1]+ncol;

  return m;

}

/* ---------------------------------------------------------------------- */
void free_dmatrix(double **m, long nrl, long nrh, long ncl, long nch)
{
  free((FREE_ARG) (m[nrl]+ncl-NR_END));
  free((FREE_ARG) (m+nrl-NR_END));
}

/* ---------------------------------------------------------------------- */

