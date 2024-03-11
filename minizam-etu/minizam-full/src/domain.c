#include <stdlib.h>

#include "domain_state.h"
#include "config.h"
#include "mlvalues.h"


caml_domain_state* Caml_state;

void caml_init_domain() {

  Caml_state = malloc(sizeof(caml_domain_state));
  Caml_state->end_heap = 0;

  Caml_state->stack = malloc(Stack_size);
  Caml_state->heap = malloc(Heap_size); //Ajout 1 : allouer le tas !
}


void camml_free_domain(){
  free(Caml_state->stack);
  free(Caml_state->heap);
  free(Caml_state);
}