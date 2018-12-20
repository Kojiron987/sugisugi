/* ----------------------------------------------------------------------
   memory.h

   malloc_2D
   malloc_3D
   free_2D
   free_3D

   May/09/'03 A.Sugimura
   ---------------------------------------------------------------------- */

char **malloc_2D( int x_size, int y_size, int size );
char ***malloc_3D( int x_size, int y_size, int t_size, int size);
int free_2D( int y_size, char **p);
int free_3D( int y_size, int t_size, char ***p );
double **dmatrix(long nrl, long nrh, long ncl, long nch);
void free_dmatrix(double **m, long nrl, long nrh, long ncl, long nch);

/* ---------------------------------------------------------------------- */
