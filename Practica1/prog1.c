#include <stdlib.h>
#include <stdio.h>
#include <math.h>

int main(int argc, char * argv[]){
  double num, result;

  do
  {
    printf("\nEscribe un numero positivo para calcular su raiz cuadrada: \n");
    scanf("%lf", &num);
    if(num < 0)
    {
      printf("Error: Negative number\n");
    }

  }while(num < 0);

  result = sqrt(num);
  printf("La raiz cuadrada de %.2lf es %.2lf\n", num, result);

  return 0;

}
