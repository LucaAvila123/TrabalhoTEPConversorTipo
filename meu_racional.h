/**********************************************************************
* Baseado no código disponibilizado em
*  Application Note: "Object-Oriented Programming in C"
* https://www.state-machine.com/doc/AN_OOP_in_C.pdf
* 
* Aqui se apresenta a interface do número do tipo "double"
* 
* numero.h definiu a interface do "número_t virtual"
* ********************************************************************/

#ifndef MEURACIONAL_H
#define MEURACIONAL_H

#include "numero.h" /*a interface da classe básica */

struct MeuRacional_Interface_st;
/*-------------------------------------------------------------*
 *  definição da estrutura MeuRacional_st                        *
 * * trouxe a definição da estrutura para o "___.h" porque vou * 
 * fazer a herança da estrutura de um "____.h" pai para        *
 * um "_____.h" filho                                          *
 * Aqui, iremos agregar duas "features" importantes:           *
 *                                                             *
 * a) uma tabela de interfaces que irá permitir acessar de     *
 *    forma mais legível os métodos de Numero_t. O ponteiro    *
 *    MeuRacional_t é convertido para Numero_t antes de ser      *
 *    passado como argumento para as funções da classe base.   *
 *    E o resultado retornado da classe base é convertido "de  *
 *    volta" para "MeuRacional_t". 
 *                                                             *
 * b) os atributos (valores) numéricos do MeuRacional_t          *
 *     (FINALMENTE  !!!!   :)                                  *
 * ------------------------------------------------------------*/
 struct MeuRacional_st {
    struct Numero_st super; 
                     /* <== herda a "super-classe Numeros", 
                      * isto é, a classe superior a MeuRacional na 
                      * hierarquia dos números 
                      * Com isso, herda as operações da            
                      * tabela de métodos comuns a todos os Numeros 
                      * assim como os atributos desta classe base,  
                      * (caso houvessem)       */
    
    struct MeuRacional_Interface_st const *  Metodo; 
                      /* o ponteiro para a tabela de 
                       * ponteiros para funções 
                       * que são apenas as chamadas para os métodos
                       * da super-classe, porém fazendo as 
                       * devidas conversões na "entrada" e na
                       * saída               */
                     
    /* o atributo  desta classe é o ponteiro para um double  */
    long int * valor;
}  ;
/* ----------------------------------------------------------*
 * declaro o ponteiro para o número do tipo MeuRacional_t      *
 * que não estão "dentro" da tabela de funções virtuais      *
 * ----------------------------------------------------------*/
typedef struct MeuRacional_st *MeuRacional_pt;
typedef struct MeuRacional_st  MeuRacional_t;



struct MeuRacional_Interface_st {
	MeuRacional_pt (*copia)	(MeuRacional_t const * const me);
	
    MeuRacional_pt (*atribui)(MeuRacional_t const * const  me, 
							 MeuRacional_t       * const  outro);
							 
    MeuRacional_pt (*soma)	(MeuRacional_t const * const  me, 
							 MeuRacional_t const * const  outro, 
							 MeuRacional_t       * const res);
							 
    MeuRacional_pt (*subt)	(MeuRacional_t const * const  me, 
							 MeuRacional_t const * const  outro, 
							 MeuRacional_t       * const res);
							 
    MeuRacional_pt (*mult)	(MeuRacional_t const * const  me, 
							 MeuRacional_t const * const  outro, 
							MeuRacional_t        * const res);
							
    MeuRacional_pt (*divd)	(MeuRacional_t const * const  me, 
							 MeuRacional_t const * const  outro, 
							 MeuRacional_t       * const res);
							 
    MeuRacional_pt (*ac_soma)	(MeuRacional_t       * const  me, 
							 MeuRacional_t const * const  outro);
							 
    MeuRacional_pt (*ac_subt)	(MeuRacional_t       * const  me, 
							 MeuRacional_t const * const outro);
							 
    MeuRacional_pt (*ac_mult)	(MeuRacional_t       * const  me, 
							 MeuRacional_t const * const outro);
							 
    MeuRacional_pt (*ac_divd)	(MeuRacional_t        * const  me, 
							 MeuRacional_t const * const outro);
							 
    int			   (*compara)	(MeuRacional_t const * const  me, 
							 MeuRacional_t const * const  outro);
							 
    char *         (*imprime)  (MeuRacional_t const * const  me);
    
    void           (*destroi)  (MeuRacional_t       *        me);
    /*------------------------------------------------------*/
    long int       (*getNumerador) (MeuRacional_t  const * const me);
	long int       (*getDenominador)(MeuRacional_t const * const me);
    void   		   (*set     ) (MeuRacional_t        * const me, 
	                          long int numerador, long int denominador);
    /*------------------------------------------------------*/
    MeuRacional_pt (*reduz) (MeuRacional_t   const * const me); 
};

typedef struct MeuRacional_Interface_st *MeuRacional_Interface_pt;


/* protótipo do construtor   */
MeuRacional_pt Rac_constroi (MeuRacional_pt  me, long int numerador, long int denominador);



#endif /* MeuRacional_H */
