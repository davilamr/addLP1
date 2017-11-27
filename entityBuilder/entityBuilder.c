#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "entityBuilder.h"

static int isArray(char* definition,char* result);


int entity_buildStruct(char* entityName, Member* members,int qtyMembers, char* result)
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



int entity_buildConstructorPrototype(char* entityName, Member* members,int qtyMembers, char* result)
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
    sprintf(auxString,");\n");
    strcat(result,auxString);
    return 0;
}

int entity_buildConstructor(char* entityName, Member* members,int qtyMembers, char* result)
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
    sprintf(auxString,")\n{\n");
    strcat(result,auxString);

    sprintf(auxString,"\t%s* this = malloc(sizeof(%s));\n", entityName, entityName);
    strcat(result,auxString);


    sprintf(auxString,"\n\tif(this != NULL)\n\t{\n\n");
    strcat(result,auxString);
    for(i=0;i<qtyMembers;i++)
    {
        isArray(members[i].definition,auxDefinition);
        if(strlen(auxDefinition) > 1)
            sprintf(auxDefinitionUp,"%c%s",toupper(auxDefinition[0]),auxDefinition+1);
        else
            sprintf(auxDefinitionUp,"%c",toupper(auxDefinition[0]));

        sprintf(auxString,"\t\t%sset%s(this,%s);\n", auxPrefix,auxDefinitionUp,auxDefinition);
        strcat(result,auxString);
    }

    sprintf(auxString,"\t}\n\treturn this;\n}\n\n");
    strcat(result,auxString);
    return 0;
}

int entity_buildDestructor(char* entityName,char* result)
{
    char auxPrefix[1024];
    *result = '\0';

    if(strlen(entityName) > 1)
        sprintf(auxPrefix,"%c%s_",tolower(entityName[0]),entityName+1);
    else
        sprintf(auxPrefix,"%c_",tolower(entityName[0]));

    sprintf(result,"void %sdelete(%s* this)\n{\n\tfree(this);\n}\n\n",auxPrefix,entityName);

    return 0;
}

int entity_buildDestructorPrototype(char* entityName,char* result)
{
    char auxPrefix[1024];
    *result = '\0';

    if(strlen(entityName) > 1)
        sprintf(auxPrefix,"%c%s_",tolower(entityName[0]),entityName+1);
    else
        sprintf(auxPrefix,"%c_",tolower(entityName[0]));

    sprintf(result,"void %sdelete(%s* this);\n",auxPrefix,entityName);

    return 0;
}

int entity_buildSetters(char* entityName, Member* members,int qtyMembers, char* result)
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
int entity_buildSettersPrototypes(char* entityName, Member* members,int qtyMembers, char* result)
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
int entity_buildGetters(char* entityName, Member* members,int qtyMembers, char* result)
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
            sprintf(auxString,"%s* %sget%s(%s* this)\n{\n\treturn this->%s;\n}\n\n", members[i].type, auxPrefix,auxDefinitionUp,entityName,auxDefinition);
        else
           sprintf(auxString,"%s %sget%s(%s* this)\n{\n\treturn this->%s;\n}\n\n", members[i].type, auxPrefix,auxDefinitionUp,entityName,auxDefinition);


        strcat(result,auxString);
    }

    return 0;
}

int entity_buildGettersPrototypes(char* entityName, Member* members,int qtyMembers, char* result)
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
            sprintf(auxString,"%s* %sget%s(%s* this);\n", members[i].type, auxPrefix,auxDefinitionUp,entityName);
        else
           sprintf(auxString,"%s %sget%s(%s* this);\n", members[i].type, auxPrefix,auxDefinitionUp,entityName);


        strcat(result,auxString);
    }

    return 0;
}

static int isArray(char* definition,char* result)
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


void strToUpper(char *str,char *strUp)
{
  while(*str != '\0')
  {
    *strUp = toupper(*str);
    str++;
    strUp++;
  }
}
