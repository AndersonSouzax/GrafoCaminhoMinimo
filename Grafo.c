#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "Grafo.h"

typedef struct user User;

struct user{
  char nome[15];
  int priority;
  int usado;
  int quantAmg;
  User * amigo;
  User * prox;
  User * ant;
};

struct lista{
 User * ini, * fim;
 int tam;
};

Lista * criar(){
  Lista * l = (Lista*)malloc(sizeof(Lista));
  l->ini = NULL;
  l->fim = NULL;
  l->tam = 0;
  return l;
}


int User_nulo(User * a){
   return a == NULL;
} 

void imprimirMenorCaminho(User * a){
   User * aux;
   aux = a;
   printf("Em sentido contrario de amizades\n");
   while(aux!=NULL){
     printf("%s<-",aux->nome);
     aux = aux->ant;
   }
}

User * buscar(Lista * l,char * nome){
   User * aux;
   aux = l->ini;

  while(aux != NULL){
    if(strcmp(aux->nome,nome) == 0){
       return aux;
     }
     aux = aux->prox;
   }
    return aux;
}

void imprimirDados(char * nome,Lista * l){
   User * aux; 
   aux = l->ini;

   while(aux != NULL){
    if(strcmp(nome,aux->nome) == 0){
      printf("[%s",aux->nome);
      aux = aux->amigo;
      while(aux != NULL){
      printf("-%s",aux->nome);
      aux = aux->prox;
      }
      printf("]\n");
      return;
    } 
    aux = aux->prox;
  }
    if(aux == NULL){
		printf("%s Nao Encontrado",nome);
     return;
   } 
}

//Proximo da lista de prioridade//
User * proximo(Lista * l){
	User * aux, * aux2;
   if(l->ini == NULL){
     printf("Vazio\n >< ");
     return NULL;
   }
   
   aux = l->ini;
   if(aux->priority == 0 && aux->usado == 1){
	   aux = aux->prox;
   }
      
   aux2 = aux->prox;
   
   while(aux2 != NULL){
	 if(aux->usado == 1){
        aux = aux2;
     }
	 if(aux2->priority < aux->priority){
		 if(aux2->usado == 0){
			 aux = aux2;
		 }
	 }
      aux2 = aux2->prox;
   } 
     if(aux == NULL){
     printf("Todos os usuarios ja foram testados ><\n");
     return NULL;
     }

     return aux;
}


void relaxar(User * u,User * v,int peso){
  if(peso + 1 < v->priority){
     v->priority = peso + 1; 
     v->ant = u;   
   }      
}

void cadastrar_user(char * nome,Lista * l){
 int i;
 User * aux = l->ini;
 User * aux2;
 User * u;
 while(aux != NULL){
    if(strcmp(nome,aux->nome)==0){
      printf("Ja existe Outro usuario com esse nome\n");
      return;
     }
    aux2 = aux;
    aux = aux->prox;
 }
  u = (User*)malloc(sizeof(User));
  for(i=0;nome[i]!='\0';i++){
    u->nome[i] = nome[i];
  }
    u->nome[i] = '\0';
    u->amigo=NULL;
    u->quantAmg = 0;
    u->prox = NULL;
	u->priority = 5000;
    u->usado = 0; //nao usado//
    u->ant = NULL;

    if(l->tam == 0){
    l->ini = u;
    l->fim = u;
    l->tam++;
    }else{
     
    aux2->prox = u;
    l->fim = u;
    l->tam++; 
  }      
}

void imprimir(Lista * l){
 User * aux, * aux2;
 if(l->ini == NULL){
    printf("Sem usuarios para mostrar\n");
    return;
  }  
  aux = l->ini;

  while(aux!=NULL){
    printf("[%s",aux->nome);
    if(aux->amigo != NULL){
       aux2 = aux->amigo;
       while(aux2 != NULL){
       printf("-%s",aux2->nome);
       aux2 = aux2->prox;
       }
     } 
	printf("]\n");
    aux = aux->prox;  
  }
}

void juntarAmigos(User * a,char * nome){
     User * aux, * aux2;
	 int i;
     User * u = (User*)malloc(sizeof(User));
      for(i=0;nome[i]!='\0';i++){
           u->nome[i] = nome[i];
       }
       u->nome[i] = '\0';
	   u->quantAmg = 0;
       u->amigo = NULL;
       u->prox = NULL;
	   u->priority = 5000;
       u->usado = 0; //nao usado//
       u->ant = NULL;
     if(a->amigo == NULL){
        a->amigo = u;
        a->quantAmg++;  
     }else{
      aux = a->amigo;
      while(aux != NULL){
      aux2 = aux;
      aux = aux->prox;
     }
      aux2->prox = u;
      a->quantAmg++;
   }
}
void Amizade(char * nome1,char * nome2,Lista * l){
   User * aux, * aux2;
  if(l->ini == NULL){
     printf("Sem usuarios Cadastrados\n");
     return;
   }
  
   aux = l->ini;
   while(aux!= NULL){
    if(strcmp(nome1,aux->nome) == 0){
        aux2 = l->ini;
        while(aux2 != NULL){
        if(strcmp(nome2,aux2->nome) == 0){
           juntarAmigos(aux2,nome1);
           juntarAmigos(aux,nome2);
           printf("Amizade feita >< \n");
           return;           
         } 
           aux2 = aux2->prox;  
        }
          if(aux2 == NULL){
			  printf("Usuario %s nao cadastrado>< \n",nome2);
           return;
         }
     }
    aux = aux->prox;
  }
   if(aux == NULL){
	   printf("Usuario %s nao cadastrado >< \n",nome1);
     return;
   }       
}

void separarAmigo(User * a,char * nome){
      User * aux, * aux2;
	  aux = a->amigo;
      aux2 = aux;
      while(aux != NULL){
      if(strcmp(aux->nome,nome) == 0){
       if(aux == a->amigo){
         a->amigo = aux->prox;
       }else{
       aux2->prox = aux->prox;
       }
       free(aux);   
       a->quantAmg--;
       return;
      }
      aux2 = aux; 
      aux = aux->prox;
     }
     
 }

void intriga(char *nome1, char *nome2, Lista *l) {
   User * aux, * aux2;
   if(l->ini == NULL){
    printf("Sem usuarios cadastrados ><\n");
    return;
   }
   aux = l->ini;
  while(aux!=NULL){
    if(strcmp(aux->nome,nome1) == 0){
      aux2 = l->ini;

      while(aux2!= NULL){
       if(strcmp(aux2->nome,nome2) == 0){
         separarAmigo(aux,nome2);
         separarAmigo(aux2,nome1);
         printf("Amizade desfeita ><\n");
         return;
        }
       aux2 = aux2->prox;
      }
      if(aux2 == NULL){
		  printf("usuario %s nao cadastrado >< \n",nome2);
      }
    }
    aux = aux->prox;
  }
    if(aux == NULL){
		printf("Usuario %s nao cadastrado >< \n",nome1);
     return; 
    }  
}

void remover(char * nome,Lista * l){
 User * aux, * aux2,* aux3, * aux4;
    if(l->ini == NULL){
     printf("Sem usuários cadastrados ><\n"); 
     return;
    }
 aux = l->ini;
 aux2 = aux;
 aux4 = aux;
 while(aux!=NULL){
  if(strcmp(nome,aux->nome) == 0){
     if(aux->amigo == NULL){
		 if(aux == l->ini){
			 l->ini = aux->prox;
		 }else{
        aux2->prox = aux->prox;
		 }
        free(aux);
        l->tam--;
        return;
     }
    
     aux2 = aux->amigo;
     while(aux2 != NULL){
       aux3 = l->ini;
       while(aux3!= NULL){
       if(strcmp(aux2->nome,aux3->nome) == 0){
          separarAmigo(aux3,aux->nome);
        } 
	    aux3 = aux3->prox;
       }
       aux2 = aux2->prox;
     }
     aux2 = aux->amigo;
     while(aux2 != NULL){
       aux3 = aux2;
       aux2 = aux2->prox;
       free(aux3);
     }
     if(aux == l->ini){
       l->ini = aux->prox;
     }
     if(aux == l->fim){
       l->fim = aux4;  
     }else{
       aux4->prox = aux->prox;
     }
     l->tam--;
     free(aux);
     return;
   }
  aux4 = aux;
  aux = aux->prox;
 }
  if(aux == NULL){
	  printf("Usuario %s nao cadastrado ><\n",nome);
  }
}


void caminhoMinimo(Lista * l,char * nome1,char * nome2){
 User * aux, * aux2, * aux3, * aux4 = NULL;
 if(l->ini == NULL) {
     printf("Sem usuarios cadastrados");
     return;
  }
  
  aux = buscar(l,nome1);
  if(aux == NULL) {
     printf("Usuario %s nao encontrado\n",nome1);
     return;
  }
  aux2 = buscar(l,nome2);
  if(aux2 == NULL){
    printf("Usuario %s nao encontrado ><\n",nome2);
    return;
  } 
  aux->priority = 0;
 
  if(aux->amigo == NULL){
    printf("O usuario %s nao possui amigos\n",aux->amigo);
    return;
  }

  while(User_nulo(aux4)){
      aux3 = aux->amigo;
	  if(aux3 != NULL){
		  if(aux3->usado == 1){
			  aux3 = aux3->prox;
		  }
	  }
      while(aux3 != NULL){
       if(aux3->prox == NULL && strcmp(aux3->nome,nome2)!=0){
          aux3->usado = 1;
       }
       aux2 = buscar(l,aux3->nome);
       relaxar(aux,aux2,aux->priority);
       aux3 = aux3->prox;
      }
      aux->usado = 1;
      aux = proximo(l);
      if(strcmp(aux->nome,nome2) == 0){
         aux4 = aux;
      }
 }      
     imprimirMenorCaminho(aux);   
    
}