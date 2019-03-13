#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <sys/types.h>
#include <pwd.h>
#include <grp.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>

int main(int argc, char **argv) {

  int c;
  char *lgn;
  struct passwd *pw;
  struct group *gr;
  int uid;
  char user[10] = "USER";

  int uflag = 0;
  int iflag = 0;
  int gflag = 0;
  int dflag = 0;
  int sflag = 0;
  int hflag = 0;
  int aflag = 0;
  int bflag = 0;

  char *uvalue;
  char *ivalue;
  char *gvalue;
  char *dvalue;
  char *avalue;

  static struct option long_options[] =
  {
    /* Opciones que no van a actuar sobre un flag */
    /* "opcion", recibe o no un argumento, 0,
    identificador de la opción */
    {"username",	 required_argument,	   0, 'u'},
    {"useruid",  required_argument,	   0, 'i'},
    {"groupname",  required_argument, 0, 'g'},
    {"groupuid",  required_argument, 0, 'd'},
    {"allgroups",	no_argument, 0, 's'},
    {"allinfo",	required_argument, 0, 'a'},
    {"bactive",	no_argument, 0, 'b'},
    {"help",	no_argument, 0, 'h'},
    /* Necesario para indicar el final de las opciones */
    {0, 0, 0, 0}
  };

  int option_index = 0;

  while ((c = getopt_long (argc, argv, "u:i:g:d:sa:bh", long_options, &option_index))!=-1)
  {
    /* El usuario ha terminado de introducir opciones */
    if (c == -1)
    break;
    switch (c)
    {
      case 'u':
      uflag = 1;
      uvalue = optarg;
      break;

      case 'i':
      iflag = 1;
      ivalue = optarg;
      break;

      case 'g':
      gflag = 1;
      gvalue = optarg;
      break;

      case 'd':
      dflag = 1;
      dvalue = optarg;
      break;

      case 's':
      sflag = 1;
      break;

      case 'a':
      aflag = 1;
      avalue = optarg;
      break;

      case 'b':
      bflag = 1;
      break;

      case 'h':
      hflag = 1;
      break;

      case '?':


      default:
      abort ();
    }
  }


  if(uflag == 1){
    if(iflag == 1){

      printf("No se pueden activar las opciones -i (useruid) -u (username) a la vez.\n");
      exit(1);

    }else if(aflag == 1){

      printf("No se pueden activar las opciones -a (allinfo) -u (username) a la vez.\n");
      exit(1);

    } else{

      lgn = uvalue;

      if ((pw = getpwnam(lgn)) == NULL){

        fprintf(stderr, "Get of user information failed.\n");
        exit(1);
      }
      else{

        printf("Nombre: %s\n", pw->pw_gecos);
        printf("Login: %s\n", pw->pw_name);
        printf("Password: %s\n", pw->pw_passwd);
        printf("UID: %d\n", pw->pw_uid);
        printf("Home: %s\n", pw->pw_dir);
        printf("Número de grupo principal: %d\n", pw->pw_gid);
      }
    }

  }

  if(iflag == 1){
    uid = atoi(ivalue);

    if ((pw = getpwuid(uid)) == NULL){
      fprintf(stderr, "Get of user information failed.\n");
      exit(1);
    }
    else {
      printf("Nombre: %s\n", pw->pw_gecos);
      printf("Login: %s\n", pw->pw_name);
      printf("Password: %s\n", pw->pw_passwd);
      printf("UID: %d\n", pw->pw_uid);
      printf("Home: %s\n", pw->pw_dir);
      printf("Número de grupo principal: %d\n", pw->pw_gid);
    }
  }

  if(gflag == 1){
    if(dflag == 1){
      printf("No se pueden activar las opciones -g (groupname) -d (groupuid) a la vez.\n");
      exit(1);
    }
    lgn = gvalue;

    if ((gr = getgrnam(lgn)) == NULL)
    {
      fprintf(stderr, "Get of group information failed.\n");
      exit(1);
    }

    {
      printf("Main Group Name: %s\n", gr->gr_name);
      printf("Main Group Number: %d\n", gr->gr_gid);
      printf("Main Group Password: %s\n", gr->gr_passwd);
    }
  }

  if(dflag == 1){
    lgn = dvalue;

    if ((gr = getgrnam(lgn)) == NULL)
    {
      fprintf(stderr, "Get of group information failed.\n");
      exit(1);
    }

    {
      printf("Nombre del grupo principal: %s\n", gr->gr_name);
      printf("GID: %d\n", gr->gr_gid);
      printf("Password: %s\n", gr->gr_passwd);
    }
  }

  if(sflag == 1){
    FILE *file;

    if((file = fopen("/etc/group", "r")) == NULL){
      fprintf(stderr, "Error : Failed to open output_file\n");

      return 1;
    }
    else{

      char *nombregrupo;
      nombregrupo=(char *)calloc(50, sizeof(char));

      while(fscanf(file, "%s", nombregrupo) != EOF){

        nombregrupo = strtok(nombregrupo, ":");

        gr = getgrnam(nombregrupo);

        printf("Nombre del grupo principal: %s\n", gr->gr_name);
        printf("GID: %d\n", gr->gr_gid);
        printf("Password: %s\n", gr->gr_passwd);
      }
    }
  }

  if(aflag == 1){
    //printf("Opción -f con valor '%s'\n", optarg);
    lgn = avalue;

    if ((pw = getpwnam(lgn)) == NULL)
    {
      fprintf(stderr, "Get of user information failed.\n");
      exit(1);
    }

    {
      printf("Nombre: %s\n", pw->pw_gecos);
      printf("Login: %s\n", pw->pw_name);
      printf("Password: %s\n", pw->pw_passwd);
      printf("UID: %d\n", pw->pw_uid);
      printf("Home: %s\n", pw->pw_dir);
      printf("Número de grupo principal: %d\n", pw->pw_gid);

      gr = getgrgid(pw->pw_gid);

      printf("Nombre del grupo principal: %s\n", gr->gr_name);
      printf("GID: %d\n", gr->gr_gid);
      printf("Password: %s\n", gr->gr_passwd);
    }
  }

  if(bflag == 1){
    lgn = getenv(user);
    if ((gr = getgrnam(lgn)) == NULL)
    {
      fprintf(stderr, "Get of group information failed.\n");
      exit(1);
    }

    {
      printf("Main Group Number: %d\n", gr->gr_gid);
      printf("Main Group Name: %s\n", gr->gr_name);
    }
  }

  if(hflag == 1){
    printf("Opciones:\n");
    printf("-h, --help    Imprimir esta ayuda\n");
    printf("-u, --username    Nombre de Usuario\n");
    printf("-i, --useruid   Identificador de Usuario\n");
    printf("-g, --groupname   Nombre de Grupo\n");
    printf("-d, --groupuid    Identificador de Grupo\n");
    printf("-s, --allgroups   Muestra info de todos los grupos del sistema\n");
    printf("-a, --allinfo   Nombre de Usuario\n");
    printf("-b, --bactive   Muestra info grupo usuario Actual\n");
  }

  if(hflag == 0 && uflag == 0 && iflag == 0 && gflag == 0 && dflag == 0 && sflag == 0 && aflag == 0 && bflag == 0){
    lgn = getenv(user);
    if ((pw = getpwnam(lgn)) == NULL)
    {
      fprintf(stderr, "Get of group information failed.\n");
      exit(1);
    }
    {
      if(getenv("LANG") == "ES"){
        printf("Nombre de usuario: %s\n", pw->pw_gecos);
        printf("Identificador de usuario: %d\n", pw->pw_uid);
        printf("Contraseña: %s\n", pw->pw_passwd);
        printf("Carpeta inicio: %s\n", pw->pw_dir);
        printf("Login de usuario: %s\n", pw->pw_name);
        printf("Número de grupo: %d\n", pw->pw_gid);

        gr = getgrgid(pw->pw_gid);

        printf("Nombre de grupo: %s\n", gr->gr_name);
      }
      else{
        printf("Username: %s\n", pw->pw_gecos);
        printf("User ID: %d\n", pw->pw_uid);
        printf("Password: %s\n", pw->pw_passwd);
        printf("Home: %s\n", pw->pw_dir);
        printf("User login: %s\n", pw->pw_name);
        printf("Group number: %d\n", pw->pw_gid);

        gr = getgrgid(pw->pw_gid);

        printf("Group name: %s\n", gr->gr_name);
      }
    }
  }
  return 0;
}
