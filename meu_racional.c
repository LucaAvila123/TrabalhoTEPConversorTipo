/**********************************************************************
* Baseado no código disponibilizado em
*  Application Note: "Object-Oriented Programming in C"
* https://www.state-machine.com/doc/AN_OOP_in_C.pdf
*
* Aqui se implementa o número do tipo "double"
*
* numero.h definiu a interface do "número_t virtual"
* que é usada aqui
* ********************************************************************/
#include <float.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <math.h>
#include "meu_racional.h"

/*------------------------------------------------------------------*
 *  IMPLEMENTACAO DAS FUNCOES VIRTUAIS DE "DOUBLE"                  *
 * Uma função virtual é uma função que é declarada (mas não         *
 * implementada em uma classe base (NO CASO, NUMERO) e redefinida   *
 * pela classe derivada (NO CASO, DOUBLE).                          *
 * Para declarar uma função como sendo virtual, é preciso associá-la*
 * com uma entrada da tabela vtbl da classe base.                   *
 * A redefinição da função na classe derivada sobrepõe a definição  *
 * da função na classe base.                                        *
 *                                                                  *
 * No fundo, a declaração da função virtual na classe base age      *
 * como uma espécie de indicador que especifica uma linha geral de  *
 * ação e estabelece uma interface de acesso.                       *
 *                                                                  *
 * A redefinição da função virtual pela classe derivada especifica  *
 * verdadeiramente IMPLEMENTA as operações realmente executadas     *
 * por cada método da tabela.                                       *
 *                                                                  *
 * Quando acessadas normalmente, funções virtuais se comportam como *
 * qualquer outro tipo de função membro da classe. Entretanto, o que*
 * torna funções virtuais importantes e capazes de suportar         *
 * polimorfismo em tempode execução é o seu modo de comportamento   *
 * quando acessado através de um apontador.                         *
 *                                                                  *
 * Lembre-se que um apontador para a classe base pode ser usado     *
 * para apontar para qualquer classe derivada daquela classe base,  *
 * desde que corretamente convertido ("cast").                      *
 *                                                                  *
 * Quando um apontador base aponta para um objeto derivado que      *
 * contém uma função virtual, o programa irá determina qual versão  *
 * daquela função chamar baseada no tipo do objeto apontado pelo    *
 * apontador.                                                       *
 *                                                                  *
 * Assim, quando objetos diferentes são apontados, versões          *
 * diferentes da função virtual são executadas.                     *
 * -----------------------------------------------------------------*/

/*------------------------------------------------------------------*
 * PROTOTIPOS DA IMPLEMENTACAO DAS FUNCOES VIRTUAIS                 *
 * note o "_" (underline) no final dos nomes das funções            *
 * Trata-se de uma convenção que usamos para nos lembrar que estas  *
 * funções são "static". Isto é: são declaradas e definidas pelo    *
 * compilador de tal forma que são reconhecidas apenas aqui dentro  *
 * deste arquivo  ____.c --> _______.o                              *
 * Estas funções não podem ser chamadas PELO NOME para serem        *
 * executadas por outros trechos de código em outros arquivos .c    *
 * Todavia, podem ser chamadas para serem executadas através de seus*
 * ENDEREÇOS. E são os endereços destas funções que são atribuídos  *
 * às respectivas posições da tabela vtbl que é apontada pelo campo *
 * . O campo super a que se refere aqui é o PRIMEIRO campo da  *
 *                                                                  *
 * -----------------------------------------------------------------*/
static  Numero_pt Rac_copia_ (Numero_t const * const  me);

static  Numero_pt Rac_atribui_ (Numero_t const * const  me,
							     Numero_t       * const  outro) ;

static  Numero_pt Rac_soma_  (Numero_t const * const  me,
							   Numero_t const * const  outro,
							   Numero_t       * const  res);

static  Numero_pt Rac_subt_  (Numero_t const * const  me,
							   Numero_t const * const  outro,
							   Numero_t       * const  res);

static  Numero_pt Rac_mult_  ( Numero_t const * const  me,
								Numero_t const * const  outro,
								Numero_t       * const  res);

static  Numero_pt Rac_divd_  ( Numero_t const * const  me,
								Numero_t const * const  outro,
								Numero_t       * const  res);

static  Numero_pt Rac_ac_soma_ (Numero_t       * const  me,
								 Numero_t const * const  outro);

static  Numero_pt Rac_ac_subt_ (Numero_t       * const  me,
								 Numero_t const * const  outro);

static  Numero_pt Rac_ac_mult_ (Numero_t       * const  me,
								 Numero_t const * const  outro);

static  Numero_pt Rac_ac_divd_ (Numero_t       * const  me,
								 Numero_t const * const  outro);

static  int	Rac_compara_ 	(Numero_t const * const  me,
							 Numero_t const * const  outro);

static  char * Rac_imprime_  (Numero_t const * const  me);

static  void Rac_destroi_ (Numero_t   *   me);

static Numero_pt Rac_reduz_ (Numero_t const * const  me);


/*---------------------------------------------------------------------*
 * IMPLEMENTAÇÃO DA INTERFACE PÚBLICA das funções virtuais de MeuRacional*
 * -------------------------------------------------------------------*/
static  MeuRacional_pt Copia_ (MeuRacional_t const * const  me);

static  MeuRacional_pt Atribui_ (MeuRacional_t const * const  me,
							     MeuRacional_t       * const  outro) ;

static  MeuRacional_pt Soma_  (MeuRacional_t const * const  me,
							   MeuRacional_t const * const  outro,
							   MeuRacional_t       * const  res);

static  MeuRacional_pt Subt_  (MeuRacional_t const * const  me,
							   MeuRacional_t const * const  outro,
							   MeuRacional_t       * const  res);

static  MeuRacional_pt Mult_  ( MeuRacional_t const * const  me,
								MeuRacional_t const * const  outro,
								MeuRacional_t       * const  res);

static  MeuRacional_pt Divd_  ( MeuRacional_t const * const  me,
								MeuRacional_t const * const  outro,
								MeuRacional_t       * const  res);

static  MeuRacional_pt Ac_Soma_ (MeuRacional_t       * const  me,
								 MeuRacional_t const * const  outro);

static  MeuRacional_pt Ac_Subt_ (MeuRacional_t       * const  me,
								 MeuRacional_t const * const  outro);

static  MeuRacional_pt Ac_Mult_ (MeuRacional_t       * const  me,
								 MeuRacional_t const * const  outro);

static  MeuRacional_pt Ac_Divd_ (MeuRacional_t       * const  me,
								 MeuRacional_t const * const  outro);

static  int	Compara_ 	(MeuRacional_t const * const  me,
							 MeuRacional_t const * const  outro);

static  char *      Imprime_  (MeuRacional_t const * const  me);

static  void        Destroi_ (MeuRacional_t  *   me);

static MeuRacional_pt Reduz_ (MeuRacional_t const* const me);

/* protótipos das funçoes get e set */
static 	long int GetNumerador_ (MeuRacional_t  const * const me);
static 	long int GetDenominador_ (MeuRacional_t  const * const me);
static 	void   Set_ (MeuRacional_t   * const me, long int numerador, long int denominador);


 /*---------------------------------------------*
 * implementação do construtor                  *
 * ---------------------------------------------*/
MeuRacional_pt Rac_constroi (MeuRacional_pt  me, long int numerador, long int denominador)
{
	/* tabela de funções virtuais da classe Numero_t *
	 * Esta tabela estática será compartilhada por todos os números *
	 * da classe MeuRacional_t                                        */

    static struct NumeroVtbl const vtbl = {
        &Rac_copia_,
        &Rac_atribui_,
        &Rac_soma_,
        &Rac_subt_,
        &Rac_mult_,
        &Rac_divd_,
        &Rac_ac_soma_,
        &Rac_ac_subt_,
        &Rac_ac_mult_,
        &Rac_ac_divd_,
        &Rac_compara_,
        &Rac_imprime_,
		&Rac_reduz_,
        &Rac_destroi_
		
     };
     
         me = (MeuRacional_pt) Num_constroi ((Numero_pt) me);
                        /*constroi o Numero_t  */
                        /* no início de MeuRacional_t  */
						 
         me->super.metodo = &vtbl;
            /* metodo aponta para vtbl de MeuRacional_t */
            /* as operações do "numero", a partir de agora,     */
            /* são as operações sobre double                    */

     /* Agora, mais uma tabela estática a ser compartilhada pelos     *
      * "MeuRacional_t": a tabela de interface                          *
      * note que a estrutura Interface incorpora os métodos Get e Set */
     static struct MeuRacional_Interface_st const interface = {
        &Copia_,
        &Atribui_,
        &Soma_,
        &Subt_,
        &Mult_,
        &Divd_,
        &Ac_Soma_,
        &Ac_Subt_,
        &Ac_Mult_,
        &Ac_Divd_,
        &Compara_,
        &Imprime_,
        &Destroi_,
        &GetNumerador_,
        &GetDenominador_,
        &Set_,
		&Reduz_
     };

     me->Metodo = &interface;
            /* metodo aponta para vtbl de MeuRacional_t */
            /* as operações do "numero", a partir de agora,     */
            /* são as operações sobre double                    */

    /* aloca dinamicamente uma area de memoria para um double  */
    /* e atribui o endereço de memória alocada para o ponteiro */
    /* valor que está dentro da estrutura MeuRacional_st         */
	me->valor = (long int *) malloc (sizeof(long int));
	if (me->valor == NULL)
	{	/*erro!!! não conseguiu alocar */
	    printf ("Erro na alocação de memória em Num_Constroi");
	    printf ("Nao alocou o valor long int");
	    exit (1);
	}

	/* copia os valores passado como parâmetro */
    /* no endereco de memoria recém alocado  */
     me->valor[0] = numerador;
     me->valor[1] = denominador;

     return (me);

	/* ------------------------------------------------------------
	 * quando implementarmos o "meu_float", valor apontará para float
     * quando implementarmos o racional,   valor apontará para
     * um vetor com dois "long int"
     * quando implementarmos o complexo,   valor apontará para
     * um vetor com dois "double"
     * quando implementarmos o quaternion, valor apontará para
     * um vetor com quatro "double"
     * Por isso, cada tipo específico de número terminará de implementar
     * o seu construtor....
     *---------------------------------------------------------------*/
}


 /*---------------------------------------------*
 * implementação do set e get                   *
 * ---------------------------------------------*/
 static inline
long int GetNumerador_ (MeuRacional_t const * const  me)
{
	return ((me->valor[0]));
}
 static inline
long int GetDenominador_ (MeuRacional_t const * const  me)
{
	return ((me->valor[1]));
}

static inline
void Set_ (MeuRacional_t  * const  me,
           long int numerador, long int denominador)
{
	me->valor[0] = numerador;
    me->valor[1] = denominador;
}



/*------------------------------------------------------*
 * IMPLEMENTAÇÃO DAS FUNÇÕES VIRTUAIS           *
 * -----------------------------------------------------*/
static inline
MeuRacional_pt Copia_ (MeuRacional_t const * const  me)
{
	return ( (MeuRacional_pt)
	          Rac_copia_ ((Numero_pt) me));
}

 static
 Numero_pt Rac_copia_ (Numero_t const * const  me)
{
	assert (me != NULL);
	Numero_pt outro = NULL;
	outro = (Numero_pt) Rac_constroi
							((MeuRacional_pt) outro,
							  GetNumerador_((MeuRacional_pt) me),
                              GetDenominador_((MeuRacional_pt) me));
	return outro;
}

/*-----------------------------------------------------------------*/
static inline
MeuRacional_pt Atribui_(MeuRacional_t const * const me,
					  MeuRacional_t       * const  outro )
{
	return ( (MeuRacional_pt)
	          Rac_atribui_ ((Numero_pt) me,
										 (Numero_pt) outro));
}

static
 Numero_pt Rac_atribui_ (Numero_t const * const  me,
						  Numero_t       * const  outro)
 {
	 Set_( (MeuRacional_pt) outro,	GetNumerador_((MeuRacional_pt) me),
                                    GetDenominador_((MeuRacional_pt) me) );
	 return (Numero_pt) outro;
 }
/*-----------------------------------------------------------------*/
static inline
MeuRacional_pt Soma_  ( MeuRacional_t const * const  me,
						   MeuRacional_t const * const  outro,
						   MeuRacional_t       * const  res)
{
	return ( (MeuRacional_pt)
	          Rac_soma_ ((Numero_pt) me,
									  (Numero_pt) outro,
									  (Numero_pt) res));
}

static  Numero_pt Rac_soma_  ( Numero_t const * const  me,
								Numero_t const * const  outro,
								Numero_t       * const  res)
{
	Set_((MeuRacional_pt) res,
				GetNumerador_((MeuRacional_pt) me) *
                GetDenominador_((MeuRacional_pt) outro) +
                GetNumerador_((MeuRacional_pt) outro) *
                GetDenominador_((MeuRacional_pt) me),
				GetDenominador_((MeuRacional_pt) me) *
                GetDenominador_((MeuRacional_pt) outro) );

	return (Numero_pt) res;
}


/*-----------------------------------------------------------------*/
static inline
MeuRacional_pt Subt_  (      MeuRacional_t const * const  me,
						   MeuRacional_t const * const  outro,
						   MeuRacional_t       * const  res)
{
	return ( (MeuRacional_pt)
	          Rac_subt_ ((Numero_pt) me,
									  (Numero_pt) outro,
									  (Numero_pt) res));
}
static  Numero_pt Rac_subt_  (	Numero_t const * const  me,
								Numero_t const * const  outro,
								Numero_t       * const  res)
{
		Set_((MeuRacional_pt) res,
				GetNumerador_((MeuRacional_pt) me) *
                GetDenominador_((MeuRacional_pt) outro) -
                GetNumerador_((MeuRacional_pt) outro) *
                GetDenominador_((MeuRacional_pt) me),
				GetDenominador_((MeuRacional_pt) me) *
                GetDenominador_((MeuRacional_pt) outro) );
		return (Numero_pt) res;
}

/*-----------------------------------------------------------------*/
static inline
MeuRacional_pt Mult_  ( MeuRacional_t const * const  me,
						   MeuRacional_t const * const  outro,
						   MeuRacional_t       * const  res)
{
	return ( (MeuRacional_pt)
	          Rac_mult_ ((Numero_pt) me,
									  (Numero_pt) outro,
									  (Numero_pt) res));
}

static  Numero_pt Rac_mult_  ( Numero_t const * const  me,
								Numero_t const * const  outro,
								Numero_t       * const  res)
{
	Set_((MeuRacional_pt) res,
				GetNumerador_((MeuRacional_pt) me) *
				GetNumerador_((MeuRacional_pt) outro),
                GetDenominador_((MeuRacional_pt) me) *
                GetDenominador_((MeuRacional_pt) outro) );
	return (Numero_pt) res;
}

/*-----------------------------------------------------------------*/
static inline
MeuRacional_pt Divd_  ( MeuRacional_t const * const  me,
						   MeuRacional_t const * const  outro,
						   MeuRacional_t       * const  res)
{
	return ( (MeuRacional_pt)
	          Rac_divd_ ((Numero_pt) me,
									  (Numero_pt) outro,
									  (Numero_pt) res));
}

static  Numero_pt Rac_divd_  (	Numero_t const * const  me,
								Numero_t const * const  outro,
								Numero_t       * const  res)
{
	Set_((MeuRacional_pt) res,
				GetNumerador_((MeuRacional_pt) me) *
                GetDenominador_((MeuRacional_pt) outro),
				GetDenominador_((MeuRacional_pt) me) *
                GetNumerador_((MeuRacional_pt) outro) );
		return (Numero_pt) res;
}

/*-----------------------------------------------------------------*/
static inline
MeuRacional_pt Ac_Soma_  ( MeuRacional_t  * const  me,
						 MeuRacional_t const * const  outro)
{
	return ( (MeuRacional_pt)
	          Rac_ac_soma_ ((Numero_pt) me,
									     (Numero_pt) outro));
}

static  Numero_pt Rac_ac_soma_  (Numero_t       * const  me,
								  Numero_t const * const  outro)
{
	Set_((MeuRacional_pt) me,
				GetNumerador_((MeuRacional_pt) me) *
                GetDenominador_((MeuRacional_pt) outro) +
                GetNumerador_((MeuRacional_pt) outro) *
                GetDenominador_((MeuRacional_pt) me),
				GetDenominador_((MeuRacional_pt) me) *
                GetDenominador_((MeuRacional_pt) outro) );
	return (Numero_pt) me;
}

/*-----------------------------------------------------------------*/
static inline
MeuRacional_pt Ac_Subt_  ( MeuRacional_t  * const  me,
						 MeuRacional_t const * const  outro)
{
	return ( (MeuRacional_pt)
	          Rac_ac_subt_ ((Numero_pt) me,
									     (Numero_pt) outro));
}


static  Numero_pt Rac_ac_subt_  (Numero_t       * const  me,
								  Numero_t const * const  outro)
{
	Set_((MeuRacional_pt) me,
				GetNumerador_((MeuRacional_pt) me) *
                GetDenominador_((MeuRacional_pt) outro) -
                GetNumerador_((MeuRacional_pt) outro) *
                GetDenominador_((MeuRacional_pt) me),
				GetDenominador_((MeuRacional_pt) me) *
                GetDenominador_((MeuRacional_pt) outro) ); 
	return (Numero_pt) me;
}

/*-----------------------------------------------------------------*/
static inline
MeuRacional_pt Ac_Mult_  ( MeuRacional_t  * const  me,
						 MeuRacional_t const * const  outro)
{
	return ( (MeuRacional_pt)
	          Rac_ac_mult_ ((Numero_pt) me,
									     (Numero_pt) outro));
}


static  Numero_pt Rac_ac_mult_  (Numero_t       * const  me,
								 Numero_t const * const  outro)
{
	Set_((MeuRacional_pt) me,
				GetNumerador_((MeuRacional_pt) me) *
				GetNumerador_((MeuRacional_pt) outro),
                GetDenominador_((MeuRacional_pt) me) *
                GetDenominador_((MeuRacional_pt) outro) );
	return (Numero_pt) me;
}

/*-----------------------------------------------------------------*/
static inline
MeuRacional_pt Ac_Divd_  ( MeuRacional_t  * const  me,
						 MeuRacional_t const * const  outro)
{
	return ( (MeuRacional_pt)
	          Rac_ac_divd_ ((Numero_pt) me,
									     (Numero_pt) outro));
}


static  Numero_pt Rac_ac_divd_  (Numero_t       * const  me,
								  Numero_t const * const  outro)
{
	Set_((MeuRacional_pt) me,
				GetNumerador_((MeuRacional_pt) me) *
                GetDenominador_((MeuRacional_pt) outro),
				GetDenominador_((MeuRacional_pt) me) *
                GetNumerador_((MeuRacional_pt) outro) );
	return (Numero_pt) me;
}

/*-----------------------------------------------------------------*/
static inline
int Compara_  ( MeuRacional_t const * const  me,
				MeuRacional_t const * const  outro)
{
	return ( Rac_compara_ ((Numero_pt) me,
									     (Numero_pt) outro));
}

static  int	Rac_compara_ 	(Numero_t const * const  me,
						     Numero_t const * const  outro)
{
	
	double diff = 	GetNumerador_((MeuRacional_pt) me) / 
					GetDenominador_((MeuRacional_pt) me) -
					GetNumerador_((MeuRacional_pt) outro) /
					GetDenominador_((MeuRacional_pt) outro);
					
	if (fabs(diff) <  (DBL_MIN * 256.0) )
	{	return (0);	}
	else if (diff > 0)
	{    return (1); }
	else
	{ return (-1);   }
}

/*-----------------------------------------------------------------*/
static inline
char * Imprime_  ( MeuRacional_t const * const  me)
{
	return ( Rac_imprime_ ((Numero_pt) me));
}
static  char * Rac_imprime_  (Numero_t const * const  me)
{
    static char buffer[50];
	sprintf(buffer, "%ld / %ld",GetNumerador_((MeuRacional_pt) me), GetDenominador_((MeuRacional_pt) me));
	return buffer;
}


 /*---------------------------------------------*
 * implementação do destrutor                   *
 * ---------------------------------------------*/
 /*-----------------------------------------------------------------*/
static inline
void Destroi_  ( MeuRacional_t  *   me)
{
	  Rac_destroi_ ((Numero_t *)  me);
}
static void Rac_destroi_ (Numero_t *  me)
{
	/* primeiro destroi o valor double */
	free (((MeuRacional_pt) me)->valor);
	/*... e só agora destroi-se o número virtual da classe base */
	free ((Numero_t *) me);
}

static inline
MeuRacional_pt Reduz_(MeuRacional_t const * const me)
{
	return ( (MeuRacional_pt) Rac_reduz_ ((Numero_pt) me));
}

static
 Numero_pt Rac_reduz_ (Numero_t const * const  me)
 {
	long int numerador = GetNumerador_((MeuRacional_pt) me);
	long int denominador = GetDenominador_((MeuRacional_pt) me);
	if(numerador <= denominador){
        for(int i=numerador; i>0; i--){
            if(numerador % i == 0 && denominador % i == 0){
                numerador   /= i;
                denominador /= i;
            }
        }
    }
    else{
        for(int i=denominador; i>0; i--){
            if(numerador % i == 0 && denominador % i == 0){
                numerador   /= i;
                denominador /= i;
            }
        }
    }
	 Set_( (MeuRacional_pt) me,	numerador, denominador );
	 return (Numero_pt) me;
 }
