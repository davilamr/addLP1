#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "entityBuilder.h"
/*

typedef struct
{
    int id;
    char nombre[51];
    char apellido[51];
    char dni[51];
    int estado;
}Socio;

./entityBuilder Socio int id char nombre[51] char apellido[51] char dni[51] int estado


*/



int main(int argc, char **argv)
{
    char entityName[256];
    char entityNameUp[256];
    Member members[256];
    int qtyMembers;
    int i,j;
    char* result = malloc(sizeof(char)*50000);
 printf("%d",argc);
    if((argc >= 4) && (argc%2 != 1))
    {

        qtyMembers = (argc - 2) / 2;
        //printf("ENTIDAD %s - CANTIDAD MIEMBROS: %d\n", *(argv+1),qtyMembers);
        strcpy(entityName,*(argv+1));
        j=0;
        for(i=2;i<argc;i=i+2)
        {
            //printf("TIPO %s - NOMBRE %s\n", *(argv+i),*(argv+i+1));
            strcpy(members[j].type,*(argv+i));
            strcpy(members[j].definition,*(argv+i+1));
            j++;
        }


    strToUpper(entityName,entityNameUp);
    printf("\n\n********************* %s.h ************************\n\n",entityName);
    printf("#include \"ArrayList.h\"\n\n#ifndef _%s_H\n#define _%s_H\n",entityNameUp,entityNameUp);  // _EMPLOYEE_H
    entity_buildStruct(entityName, members, qtyMembers, result);
    printf("%s",result);
    printf("#endif// _%s_H\n\n",entityNameUp);
    entity_buildConstructorPrototype(entityName, members, qtyMembers, result);
    printf("%s",result);
    entity_buildDestructorPrototype(entityName,result);
    printf("%s",result);
    entity_buildSettersPrototypes(entityName, members, qtyMembers, result);
    printf("%s",result);
    entity_buildGettersPrototypes(entityName, members, qtyMembers, result);
    printf("%s",result);
    entity_buildFindersPrototypes(entityName, members, qtyMembers, result);
    printf("%s",result);
    entity_buildComparativeFunctionsPrototypes(entityName, members, qtyMembers, result);
    printf("%s",result);
    printf("\n\n********************* %s.h ************************\n\n",entityName);

    printf("\n\n********************* %s.c ************************\n\n",entityName);
    printf("#include <stdio.h>\n#include <stdlib.h>\n#include <string.h>\n#include \"ArrayList.h\"\n#include \"%s.h\"\n\n",entityName);  // _EMPLOYEE_H
    entity_buildConstructor(entityName, members, qtyMembers, result);
    printf("%s",result);
    entity_buildDestructor(entityName,result);
    printf("%s",result);
    entity_buildSetters(entityName, members, qtyMembers, result);
    printf("%s",result);
    entity_buildGetters(entityName, members, qtyMembers, result);
    printf("%s",result);
    entity_buildFinders(entityName, members, qtyMembers, result);
    printf("%s",result);
    entity_buildComparativeFunctions(entityName, members, qtyMembers, result);
    printf("%s",result);
    printf("\n\n********************* %s.c ************************\n\n",entityName);

    }
    else
    {
        printf("\n\nERROR DE FORMATO\n\n\n./entityBuilder Employee int id char name[51] char lastName[51] int age int type\n\n");
    }

    exit(EXIT_SUCCESS);

}

