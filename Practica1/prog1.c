#include <stdlib.h>
#include <stdio.h>
#include <math.h>

int main(int argc, char * argv[]){
  double num, result;
  printf("%s\n",argv[0] );
  printf("Escribe un numero positivo para calcular su raiz cuadrada: \n");
  scanf("%lf",&num);
  if(num < 0 ){
    fprintf(stderr, "Negative number\n" );
    exit(-1);
  }else{
    result = sqrt(num);
    printf("La raiz cuadrada de %.2lf es %.2lf\n",num,result );
    return 0;
  }

}
