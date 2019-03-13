#include <stdio.h>
#include <string.h>

#define NPROC 5

typedef struct params
{
    char nombre[10];
    int t_ejec;  // Se introducen
    int t_lleg;
    int t_com;   // Se calculan
    int t_fin;
    int t_ret;
    int t_esp;

} parametros;

void main(){

    int i,j;

    int quantum = 3;
    int contador = 1;
    int comienzo;

    // Inicialización de los datos de procesos
    parametros procesos[NPROC];
    parametros aux;
    strcpy(procesos[0].nombre, "A");
    procesos[0].t_ejec = 8;
    procesos[0].t_lleg = 0;
    procesos[0].t_com = 0;
    procesos[0].t_fin = procesos[0].t_ejec;
    procesos[0].t_ret = procesos[0].t_fin;
    procesos[0].t_esp = 0;

    strcpy(procesos[1].nombre, "B");
    procesos[1].t_ejec = 4;
    procesos[1].t_lleg = 4;

    strcpy(procesos[2].nombre, "C");
    procesos[2].t_ejec = 9;
    procesos[2].t_lleg = 2;

    strcpy(procesos[3].nombre, "D");
    procesos[3].t_ejec = 5;
    procesos[3].t_lleg = 1;

    strcpy(procesos[4].nombre, "E");
    procesos[4].t_ejec = 2;
    procesos[4].t_lleg = 3;


      // Ordenamos los procesos en funcion del tiempo de llegada
      for(i = 0; i<NPROC;i++){
        for(j = i+1; j<NPROC; j++){
          if(procesos[i].t_lleg>procesos[j].t_lleg){
            aux = procesos[i];
            procesos[i] = procesos[j];
            procesos[j] = aux;
          }
        }
      }

      comienzo = procesos[0].t_lleg;

// En el momento que contador llegue al numero de procesos totales, significa que el tiempo de ejecucion de todos los procesos ha llegado a cero
while(contador!=NPROC){

// Recorremos proceso a proceso
  for(i=0; i<NPROC;i++){


    if(procesos[i].t_ejec != 0){
      printf("\nProceso | t_comienzo | t_final | t_retorno | t_espera | t_ejec\n");
      printf("----------------------------------------------------------------\n");

        procesos[i].t_com = comienzo;

        if((procesos[i].t_ejec - quantum) >=0){
        procesos[i].t_fin = procesos[i].t_com + quantum;
        procesos[i].t_ejec = procesos[i].t_ejec - quantum;

        procesos[i].t_ret = procesos[i].t_fin - procesos[i].t_lleg;
        procesos[i].t_esp = procesos[i].t_com - procesos[i].t_lleg;

        comienzo = procesos[i].t_fin;
      }
      else{
        procesos[i].t_fin = procesos[i].t_com + procesos[i].t_ejec;
        procesos[i].t_ejec = 0;
        contador++;

        procesos[i].t_ret = procesos[i].t_fin - procesos[i].t_lleg;
        procesos[i].t_esp = procesos[i].t_com - procesos[i].t_lleg;

        comienzo = procesos[i].t_fin;
      }
      printf("   %s \t    %d \t\t %d \t   %d \t      %d\t      %d\n", procesos[i].nombre,procesos[i].t_com, procesos[i].t_fin, procesos[i].t_ret, procesos[i].t_esp, procesos[i].t_ejec);
    }

  }
}

}
