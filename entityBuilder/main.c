#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*

./entityBuilder Employee int id char name[51] char lastName[51] int age int type


*/
typedef struct
{
    char type[256];
    char definition[256];
}Member;

int buildStruct(char* entityName, Member* members,int qtyMembers, char* result);
int buildConstructor(char* entityName, Member* members,int qtyMembers, char* result);
int buildConstructorPrototype(char* entityName, Member* members,int qtyMembers, char* result);
int buildSetters(char* entityName, Member* members,int qtyMembers, char* result);
int buildSettersPrototypes(char* entityName, Member* members,int qtyMembers, char* result);
int buildGetters(char* entityName, Member* members,int qtyMembers, char* result);
int buildGettersPrototypes(char* entityName, Member* members,int qtyMembers, char* result);

void strToUpper(char *str,char *strUp)
{
  while(*str != '\0')
  {
    *strUp = toupper(*str);
    str++;
    strUp++;
  }
}

int main(int argc, char **argv)
{
    char entityName[256];
    char entityNameUp[256];
    Member members[256];
    int qtyMembers;
    int i,j;
    char* result = malloc(sizeof(char)*50000);

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
    }

    strToUpper(entityName,entityNameUp);
    printf("\n\n********************* %s.h ************************\n\n",entityName);
    printf("#ifndef _%s_H\n#define _%s_H\n",entityNameUp,entityNameUp);  // _EMPLOYEE_H
    buildStruct(entityName, members, qtyMembers, result);
    printf("%s",result);
    printf("#endif// _%s_H\n\n",entityNameUp);
    buildConstructorPrototype(entityName, members, qtyMembers, result);
    printf("%s",result);
    buildSettersPrototypes(entityName, members, qtyMembers, result);
    printf("%s",result);
    buildGettersPrototypes(entityName, members, qtyMembers, result);
    printf("%s",result);
    printf("\n\n********************* %s.h ************************\n\n",entityName);

    printf("\n\n********************* %s.c ************************\n\n",entityName);
    buildConstructor(entityName, members, qtyMembers, result);
    printf("%s",result);
    buildSetters(entityName, members, qtyMembers, result);
    printf("%s",result);
    buildGetters(entityName, members, qtyMembers, result);
    printf("%s",result);

    printf("\n\n********************* %s.c ************************\n\n",entityName);


    exit(EXIT_SUCCESS);
}

int buildStruct(char* entityName, Member* members,int qtyMembers, char* result)
{
    int i;
    char auxString[1024];
    *result = '\0';
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



int isArray(char* definition,char* result)
{
    int i;
    int retorno = 0;
    *result = '\0';
    for(i=0; i < strlen(definition); i++)
    {

        if(*(definition+i)== '[')
        {
            retorno = 1;
            *(result+i) = '\0';
            break;
        }
        *(result+i) = *(definition+i);
    }
    *(result+i) = '\0';
    return retorno;
}

int buildConstructorPrototype(char* entityName, Member* members,int qtyMembers, char* result)
{
    int i;
    char auxString[1024];
    char auxDefinition[1024]="";
    *result = '\0';

    char auxPrefix[1024];

    if(strlen(entityName) > 1)
        sprintf(auxPrefix,"%c%s_",tolower(entityName[0]),entityName+1);
    else
        sprintf(auxPrefix,"%c_",tolower(entityName[0]));


    sprintf(result,"%s* %snew(",entityName,auxPrefix);

    for(i=0;i<qtyMembers;i++)
    {
        if(isArray(members[i].definition,auxDefinition) == 1)
            sprintf(auxString,"%s* %s", members[i].type,auxDefinition);
        else
            sprintf(auxString,"%s %s", members[i].type,members[i].definition);

        strcat(result,auxString);
        if((i+1)<qtyMembers) strcat(result,",");
    }
    sprintf(auxString,");\n", entityName);
    strcat(result,auxString);
    return 0;
}

int buildConstructor(char* entityName, Member* members,int qtyMembers, char* result)
{
    int i;
    char auxString[1024];
    char auxDefinition[1024];
    char auxDefinitionUp[1024];
    *result = '\0';
    char auxPrefix[1024];
    if(strlen(entityName) > 1)
        sprintf(auxPrefix,"%c%s_",tolower(entityName[0]),entityName+1);
    else
        sprintf(auxPrefix,"%c_",tolower(entityName[0]));


    sprintf(result,"%s* %snew(",entityName,auxPrefix);

    for(i=0;i<qtyMembers;i++)
    {
        if(isArray(members[i].definition,auxDefinition) == 1)
            sprintf(auxString,"%s* %s", members[i].type,auxDefinition);
        else
            sprintf(auxString,"%s %s", members[i].type,members[i].definition);

        strcat(result,auxString);
        if((i+1)<qtyMembers) strcat(result,",");
    }
    sprintf(auxString,")\n{\n", entityName);
    strcat(result,auxString);

    sprintf(auxString,"\t%s* this = malloc(sizeof(%s));\n", entityName, entityName);
    strcat(result,auxString);
    for(i=0;i<qtyMembers;i++)
    {
        isArray(members[i].definition,auxDefinition);
        if(strlen(auxDefinition) > 1)
            sprintf(auxDefinitionUp,"%c%s",toupper(auxDefinition[0]),auxDefinition+1);
        else
            sprintf(auxDefinitionUp,"%c",toupper(auxDefinition[0]));

        sprintf(auxString,"\t%sset%s(this,%s);\n", auxPrefix,auxDefinitionUp,auxDefinition);
        strcat(result,auxString);
    }

    sprintf(auxString,"\treturn this;\n}\n\n", entityName);
    strcat(result,auxString);
    return 0;
}

int buildSetters(char* entityName, Member* members,int qtyMembers, char* result)
{
    int i;
    char auxString[1024];
    char auxDefinition[1024];
    char auxDefinitionUp[1024];
    int flagArray;
    *result = '\0';
    char auxPrefix[1024];
    if(strlen(entityName) > 1)
        sprintf(auxPrefix,"%c%s_",tolower(entityName[0]),entityName+1);
    else
        sprintf(auxPrefix,"%c_",tolower(entityName[0]));

    for(i=0;i<qtyMembers;i++)
    {
        flagArray = isArray(members[i].definition,auxDefinition);
        if(strlen(auxDefinition) > 1)
            sprintf(auxDefinitionUp,"%c%s",toupper(auxDefinition[0]),auxDefinition+1);
        else
            sprintf(auxDefinitionUp,"%c",toupper(auxDefinition[0]));


        if(flagArray)
            sprintf(auxString,"int %sset%s(%s* this,%s* %s)\n{\n\tstrcpy(this->%s,%s);\n\treturn 0;\n}\n\n", auxPrefix,auxDefinitionUp,entityName,members[i].type,auxDefinition,auxDefinition,auxDefinition);
        else
            sprintf(auxString,"int %sset%s(%s* this,%s %s)\n{\n\tthis->%s = %s;\n\treturn 0;\n}\n\n", auxPrefix,auxDefinitionUp,entityName,members[i].type,auxDefinition,auxDefinition,auxDefinition);

        strcat(result,auxString);
    }


    return 0;
}
int buildSettersPrototypes(char* entityName, Member* members,int qtyMembers, char* result)
{
    int i;
    char auxString[1024];
    char auxDefinition[1024];
    char auxDefinitionUp[1024];
    int flagArray;
    *result = '\0';
    char auxPrefix[1024];
    if(strlen(entityName) > 1)
        sprintf(auxPrefix,"%c%s_",tolower(entityName[0]),entityName+1);
    else
        sprintf(auxPrefix,"%c_",tolower(entityName[0]));

    for(i=0;i<qtyMembers;i++)
    {
        flagArray = isArray(members[i].definition,auxDefinition);
        if(strlen(auxDefinition) > 1)
            sprintf(auxDefinitionUp,"%c%s",toupper(auxDefinition[0]),auxDefinition+1);
        else
            sprintf(auxDefinitionUp,"%c",toupper(auxDefinition[0]));


        if(flagArray)
            sprintf(auxString,"int %sset%s(%s* this,%s* %s);\n", auxPrefix,auxDefinitionUp,entityName,members[i].type,auxDefinition);
        else
            sprintf(auxString,"int %sset%s(%s* this,%s %s);\n", auxPrefix,auxDefinitionUp,entityName,members[i].type,auxDefinition);

        strcat(result,auxString);
    }


    return 0;
}
int buildGetters(char* entityName, Member* members,int qtyMembers, char* result)
{
    int i;
    char auxString[1024];
    char auxDefinition[1024];
    char auxDefinitionUp[1024];
    int flagArray;
    *result = '\0';
    char auxPrefix[1024];
    if(strlen(entityName) > 1)
        sprintf(auxPrefix,"%c%s_",tolower(entityName[0]),entityName+1);
    else
        sprintf(auxPrefix,"%c_",tolower(entityName[0]));

    for(i=0;i<qtyMembers;i++)
    {
        flagArray = isArray(members[i].definition,auxDefinition);
        if(strlen(auxDefinition) > 1)
            sprintf(auxDefinitionUp,"%c%s",toupper(auxDefinition[0]),auxDefinition+1);
        else
            sprintf(auxDefinitionUp,"%c",toupper(auxDefinition[0]));

        if(flagArray)
            sprintf(auxString,"%s* %sget%s(%s* this)\n{\n\treturn this->%s;\n}\n\n", members[i].type, auxPrefix,auxDefinitionUp,entityName,auxDefinition,auxDefinition);
        else
           sprintf(auxString,"%s %sget%s(%s* this)\n{\n\treturn this->%s;\n}\n\n", members[i].type, auxPrefix,auxDefinitionUp,entityName,auxDefinition,auxDefinition);


        strcat(result,auxString);
    }

    return 0;
}

int buildGettersPrototypes(char* entityName, Member* members,int qtyMembers, char* result)
{
    int i;
    char auxString[1024];
    char auxDefinition[1024];
    char auxDefinitionUp[1024];
    int flagArray;
    *result = '\0';
    char auxPrefix[1024];
    if(strlen(entityName) > 1)
        sprintf(auxPrefix,"%c%s_",tolower(entityName[0]),entityName+1);
    else
        sprintf(auxPrefix,"%c_",tolower(entityName[0]));

    for(i=0;i<qtyMembers;i++)
    {
        flagArray = isArray(members[i].definition,auxDefinition);
        if(strlen(auxDefinition) > 1)
            sprintf(auxDefinitionUp,"%c%s",toupper(auxDefinition[0]),auxDefinition+1);
        else
            sprintf(auxDefinitionUp,"%c",toupper(auxDefinition[0]));

        if(flagArray)
            sprintf(auxString,"%s* %sget%s(%s* this);\n", members[i].type, auxPrefix,auxDefinitionUp,entityName,auxDefinition);
        else
           sprintf(auxString,"%s %sget%s(%s* this);\n", members[i].type, auxPrefix,auxDefinitionUp,entityName,auxDefinition);


        strcat(result,auxString);
    }

    return 0;
}
