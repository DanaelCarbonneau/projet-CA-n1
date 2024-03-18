#ifndef _DOMAIN_STATE_H
#define _DOMAIN_STATE_H

#include "mlvalues.h"


typedef struct _caml_domain_state {
  /* Stack */
  mlvalue* stack;
  mlvalue* heap;
  size_t end_heap;
  size_t stack_pointer;
  mlvalue accu;
  mlvalue* env;
} caml_domain_state;

/* The global state */
extern caml_domain_state* Caml_state;

/* Initialisation function for |Caml_state| */
void caml_init_domain();
void caml_free_domain(); //Ajout pour libérer correctement la mémoire du tas et de la pile
#endif
