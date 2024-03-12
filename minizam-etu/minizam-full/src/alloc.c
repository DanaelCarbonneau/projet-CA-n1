#include <stdlib.h>

#include "alloc.h"
#include "config.h"
#include "mlvalues.h"
#include "domain_state.h"

typedef struct liste_block{
  mlvalue* content;
  struct liste_block * next;
}liste_block_t;


// faite avec François Malenfer
void set_color(mlvalue*hd,color_t color){
  *hd &= 0xFFFFFFFFFFFFFCFF;
  *hd |= (color << 8);
}

mlvalue* caml_alloc(size_t size) {
  mlvalue * block = Caml_state->heap + Caml_state->end_heap;  //Arithmétique des pointeurs
  Caml_state->end_heap+=size;    //taille 0 + 1 pour le header

  return block;
}

liste_block_t * get_racines(){
  liste_block_t * l = NULL;
  for (int i = 0 ; i < Caml_state->stack_pointer ; i++){
    if (isBlock(Caml_state->stack[i])){
      liste_block_t * new_cell = (liste_block_t*) malloc (sizeof(liste_block_t));
      new_cell->content = Caml_state->stack[i];
      set_color(new_cell->content-1,GRAY);    //-1 car on veut le header
      new_cell->content;
      new_cell->next = l;
      l = new_cell;
    }
  }
  return l;
}

/*Fonction faisant le marquage et retournant le nombre de blocs*/
size_t mark(){
  
  liste_block_t *todo = get_racines();
  size_t cpt_elem;
  while(todo != NULL){
    //pour chaque tête de la liste, on la pop, on passe la couleur à noir

    /*
     *  On parcourt toutes ses cases pour regarder si c'est des ptr, si leur couleur est blanche,
     * auquel cas ajout en tête et on les passe en gris 
     */
     

    cpt_elem++;   //On a un élément de plus
  } 

  return cpt_elem;
}

void calcul_adresse(mlvalue*** tab_assoc_addr, size_t cpt_objet){
  mlvalue* top_apres_slide = Caml_state->heap;
  /**
   * parcourt tout le tas
   * quand on trouve un block noir, on associe son adresse avant à son adresse après compaction
   * et on met à jour l'adresse du parcourt (+ size+1), et de l'adresse du top si il était noir (size +1)
   * 
   */
}