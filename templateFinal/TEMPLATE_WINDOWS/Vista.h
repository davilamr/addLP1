#ifndef VISTA_H_INCLUDED
#define VISTA_H_INCLUDED

#endif // VISTA_H_INCLUDED

#define VISTA_IDIOMA_ES 0
#define VISTA_IDIOMA_EN 1

#define MENU_PPAL_ES "\n1. Listar X\n2. Alta X\n3.Baja X\n4. Modifica X\n4. Ordena X\n6. Salir\n"
#define MENU_PPAL_ERROR_ES "\nOPCION INVALIDA\n"




int vista_init (int idioma);
int vista_mostrarMenu();
void mostrarError(char * mensaje);



