/* main.c */
/* teste do tipo de dados meuRac */
#include <stdio.h>
#include "meu_complexo.h"
#include "meu_racional.h"

MeuRacional_pt ConverteNumero (MeuComplexo_pt complexo, MeuRacional_pt racional);
int main ()
{
	MeuComplexo_pt oi=NULL;
   MeuRacional_pt top=NULL;

   oi = Comp_constroi(oi, 10.0, -10.0);
   printf("%s\n", oi->Metodo->imprime(oi));

   top = ConverteNumero(oi, top);
   top->Metodo->reduz (top);
   printf("%s\n", top->Metodo->imprime(top));
   
   oi->Metodo->destroi (oi);
   top->Metodo->destroi(top);
   return 0;
}
MeuRacional_pt ConverteNumero (MeuComplexo_pt complexo, MeuRacional_pt racional){
   //o numero complexo para converter vai usar a seguinte lógica:
   //o numerador vai ser o módulo multiplicado e o denominador fixo em 1000
   //o sinal vai ser determinado pelo quadrante do número complexo
   double numeroConversivel = complexo->Metodo->getModulo(complexo);
   numeroConversivel *= 1000;
   long int numerador = (long int) numeroConversivel;
   long int denominador = 1000;
   short int sinal = 1;
   double parteReal = complexo->Metodo->getReal(complexo);
   double parteImaginaria = complexo->Metodo->getImaginario(complexo);
   if((parteReal > 0 && 
      parteImaginaria < 0)||
      (parteReal < 0 &&
      parteImaginaria > 0))
         sinal = -1;
   numerador *= sinal;
   racional = Rac_constroi(racional, numerador, denominador);
   return(racional);
}