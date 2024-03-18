#include <stdlib.h>

#include "alloc.h"
#include "config.h"
#include "mlvalues.h"
#include "domain_state.h"

typedef struct liste_block
{
  mlvalue *content;
  struct liste_block *next;
} liste_block_t;

int size_l(liste_block_t *l)
{
  int i = 0;
  liste_block_t *cur = l;
  while (cur)
  {
    i++;
    cur = cur->next;
  }
  return i;
}
// faite avec François Malenfer
void set_color(mlvalue *hd, color_t color)
{
  *hd &= 0xFFFFFFFFFFFFFCFF;
  *hd |= (color << 8);
}

mlvalue *caml_alloc(size_t size)
{
  printf("\n====\nappel à alloc\n");
  mlvalue *block = &Caml_state->heap[Caml_state->end_heap];

  Caml_state->end_heap += size;

  // if( Caml_state->end_heap*sizeof(mlvalue) > Heap_size){
  printf("On a marqué %d blocs\n", mark()); // Bizarre, ne devrait péter le tas qu'une fois
  //}
  return block;
}

liste_block_t *avoir_les_racines()
{
  liste_block_t *l = NULL;
  for (int i = 0; i < Caml_state->stack_pointer; i++)
  {
    if (Is_block(Caml_state->stack[i]))
    {
      liste_block_t *new_cell = (liste_block_t *)malloc(sizeof(liste_block_t));
      new_cell->content = Ptr_val(Caml_state->stack[i]);
      set_color(new_cell->content - 1, GRAY); //-1 car on veut le header
      new_cell->next = l;
      l = new_cell;
    }
  }
  if(Is_block(Caml_state->accu)){
      liste_block_t *new_cell = (liste_block_t *)malloc(sizeof(liste_block_t));
      new_cell->content = Ptr_val(Caml_state->accu);
      set_color(new_cell->content - 1, GRAY); //-1 car on veut le header
      new_cell->next = l;
      l = new_cell;
  }
  if(Is_block((mlvalue)(Caml_state->env))){
    liste_block_t *new_cell = (liste_block_t *)malloc(sizeof(liste_block_t));
      new_cell->content = Caml_state->env;
      set_color(new_cell->content - 1, GRAY); //-1 car on veut le header
      new_cell->next = l;
      l = new_cell;
  }
  return l;
}

/*Fonction faisant le marquage et retournant le nombre de blocs*/
int mark()
{

  liste_block_t *todo = avoir_les_racines();
  printf("taille de todo après avoir récup les racines %d", size_l(todo));
  liste_block_t *to_free;
  liste_block_t *new_cell;
  size_t size_block;
  mlvalue *cur_ptr;
  int cpt_elem;

  while (todo != NULL)
  {
    // printf("Tour de boucle, taille de toto%d %d\n",size_l(todo), todo);
    //  pour chaque tête de la liste, on la pop, on passe la couleur à noir
    cur_ptr = todo->content;
    to_free = todo;
    todo = todo->next;
    free(to_free);

    size_block = Size(cur_ptr);
    printf("\ndébut du tas %p, fin du tas %p\n", Caml_state->heap, Caml_state->heap+Caml_state->end_heap);
    printf("taille de ce qu'on parcourt %d\n",size_block);
    for (int i = 0; i < size_block; i++)
    {
      if (Is_block(cur_ptr[i]) && Color(cur_ptr[i]) == WHITE)
      {
        printf("entête avant marquage à gris\n",Color(cur_ptr[i]));
        set_color(Ptr_val(cur_ptr[i]) - 1, GRAY); // Pré marquage pour éviter les problèmes de cycles
        new_cell = (liste_block_t *)malloc(sizeof(liste_block_t *));
        new_cell->content = cur_ptr[i];
        new_cell->next = todo;
        todo = new_cell;
      }
    }
    printf("pointeur : %p\n", Ptr_val(cur_ptr));
    //  On a fini de traiter tous les descendants de ce nœud, on peut le sortir, on passe son marquage à noir
    set_color(cur_ptr - 1, BLACK);

    cpt_elem++; // On a un élément de plus
  }
  printf("Fin de parcours\n");

  return cpt_elem;
}

void calcul_adresse(mlvalue ***tab_assoc_addr, size_t cpt_objet)
{
#if 0
  mlvalue* top_apres_slide = Caml_state->heap;
  /**
   * parcourt tout le tas
   * quand on trouve un block noir, on associe son adresse avant à son adresse après compaction
   * et on met à jour l'adresse du parcourt (+ size+1), et de l'adresse du top si il était noir (size +1)
   * 
   */
  mlvalue * heap = Caml_state->heap;
  mlvalue cur;
  size_t future_top_of_heap = 0;
  size_t tete_lecture_heap = 0;
  while(tete_lecture_heap < Caml_state->end_heap ){
    cur = heap[tete_lecture_heap];
    if( color(cur)==BLACK){   //On ne peut pas savoir si c'est un header... Mais normalement on est sur un header
      
    }

  }
#endif
}