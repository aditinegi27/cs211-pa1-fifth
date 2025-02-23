#include <stdio.h>
#include <stdlib.h>

long **createMatrix(int d){  //parameter d for dxd matrix
   long **matrix = malloc(d*sizeof(long *));
   for(int i = 0; i < d; i++){
      matrix[i] = malloc(d*sizeof(long));
   }
   return matrix;
}

void freeMatrix(long **matrix, int r){
   for(int i = 0; i < r; i++){
      free(matrix[i]);  //free each row
   }
   free(matrix);  //free row pointers
}

long **createMinor(long **matrix, long **minor, int row, int col, int n){
   int i = 0, j = 0;
   for(int r = 0; r < n; r++){
      j=0;
      for(int c = 0; c < n; c++){
         if(r != row && c != col){
            minor[i][j] = matrix[r][c];
            j++;
            
         }
         if (j == n - 1) {  // Move to the next row in the minor matrix
            j = 0;
            i++;
         }
      }
      //if(r != row)
      //j++;
   }
   return minor;
}

long determinant(long **matrix, int n){
   long det = 0;
   if(n == 1){  //1x1 matrix
      det = matrix[0][0];
      return det;
   }
   if(n == 2){  //2x2 matrix
      det = (matrix[0][0]*matrix[1][1]) - (matrix[0][1]*matrix[1][0]);
      return det;
   }
   //int **minor = createMatrix(n-1);
   int sign = 1;
   for(int c = 0; c < n; c++){
   long **minor = createMatrix(n-1);
      minor = createMinor(matrix, minor, 0, c, n);
      det += (sign * matrix[0][c] * determinant(minor, n-1));
      sign *= -1;  //alternating signs
      freeMatrix(minor, n-1);
   }
   
   //det += (sign * matrix[0][c] * determinant(minor, n-1));
   //sign *= -1;  //alternating signs
   
   //freeMatrix(minor, n);
   
   return det;
}

int main(int argc, char** argv){
   if(argc < 2) { //checks if there are 2 arguments!
      fprintf(stderr,"./first {text file}"); //prints messages to stderr. Primarily for error messages
      exit(1); //exits the program with a return code 1.
   }
   
   FILE *file = fopen(argv[1], "r"); //opening file
   if(file == NULL){ //if fopen fails to open the file, it returns NULL
      fprintf(stderr,"%s failed to open\n",argv[1]);
      exit(1); //exits your program
   }
   
   int n;
   int f1 = fscanf(file, "%d", &n);
   if(f1 != 1) return 0;
   long **matrix = createMatrix(n); //n from file!
   
   for(int i = 0; i < n; i++){
      for(int j = 0; j < n; j++){
         int f2 = fscanf(file, "%ld", &matrix[i][j]);
         if(f2 != 1) return 0;
         //matrix[i][j] = fscanf(file, "%d"); // Assign values
      }
   }
   fclose(file);
   
   long det = determinant(matrix, n);
   printf("%ld\n", det);
   
   
   freeMatrix(matrix, n);
}
