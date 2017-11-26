#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    char type[256];
    char definition[256];
}Member;

int builStruct(char* entityName, Member* members,int qtyMembers, char* result);

int main(int argc, char **argv)
{
    char entityName[256];
    Member members[256];
    int qtyMembers;
    int i,j;
    char result[4096];

    if((argc >= 4) && (argc%2 != 1))
    {

        qtyMembers = (argc - 2) / 2;
        printf("ENTIDAD %s - CANTIDAD MIEMBROS: %d\n", *(argv+1),qtyMembers);
        strcpy(entityName,*(argv+1));
        j=0;
        for(i=2;i<argc;i=i+2)
        {
            printf("TIPO %s - NOMBRE %s\n", *(argv+i),*(argv+i+1));
            strcpy(members[j].type,*(argv+i));
            strcpy(members[j].definition,*(argv+i+1));
            j++;
        }
    }


    printf("ENTIDAD %s - CANTIDAD MIEMBROS: %d\n", entityName, qtyMembers);
    for(i=0;i<qtyMembers;i++)
        printf("TIPO %s - NOMBRE %s\n", members[i].type,members[i].definition);

    builStruct(entityName, members, qtyMembers, result);
    printf("%s",result);

    exit(EXIT_SUCCESS);
}

int builStruct(char* entityName, Member* members,int qtyMembers, char* result)
{
    int i;
    char auxString[1024];

    sprintf(result,"typedef struct\n{\n");
    for(i=0;i<qtyMembers;i++)
    {
        sprintf(auxString,"\t%s %s;\n", members[i].type,members[i].definition);
        strcat(result,auxString);
    }
    sprintf(auxString,"}%s;\n", entityName);
    strcat(result,auxString);
    return 0;
}





