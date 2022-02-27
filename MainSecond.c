#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Pokemon.h"
#include "Defs.h"
#include "BattleByCategory.h"

void free_all(Battle battle ,PokemonType* types[],int numberOfTypes ,bool kindof)
{
	if (kindof==true) //check why the program closed
	{
		printf("No memory available.\n");

	}
	  destroyBattleByCategory(battle);
	  for(int i =0; i<numberOfTypes;i++)
	          	 {
	          		 freepokemonType(types[i]);
	          	 }
	  printf("All the memory cleaned and the program is safely closed.\n");
	  exit(0);

}
bool ismeline(char* str){
	if (strstr(str, "effective-against-me:") != NULL) {
	    return true;
	}
    return false;


}
bool isotherline(char* str){
	if (strstr(str, "effective-against-other:") != NULL) {
		    return true;
		}
    return false;

}
PokemonType* gettypefromarray(PokemonType* types[],int size,char* str)
{
	for(int i=0; i<size;i++)
	{
		if(!strcmp(types[i]->TypeName,str))
		{
			return types[i];
		}
	}
	return NULL;
}
Battle Build(char *path,int numberOfTypes,int capacityInType ,	PokemonType* types[])
{
	char str[301];//the longest str
	FILE *fptr;
	fptr = fopen(path,"r");
	fscanf(fptr, "%s", str);
	fscanf(fptr, "%s", str);
	char strcopy[301];
	strcpy(strcopy,str);
	//create battle
	if (!strcmp(strcopy,"Pokemons"))
		{
		strcpy(strcopy,"");
		}
	Battle newbattle= createBattleByCategory(capacityInType, numberOfTypes, strcopy, equalpokemon, copypok, freepokemon, gettypename, attackbytype, print_Pokemon);
	char *token = strtok(str, ",");
	PokemonType* newtype;
	int i=0;
	while( NULL!= token)//create types
		   {
		newtype =initPokemonType(token);
		types[i]=newtype;
		token = strtok(NULL, ",");

		i++;
		   }
	while(strcmp(str,"Pokemons"))//add types to effective_against lists
			   {
		fscanf(fptr, "%s", str);
		if(!strcmp(str,"Pokemons"))
		{
			break;
		}
		newtype =gettypefromarray(types,numberOfTypes,str);
		fscanf(fptr, "%s", str);
		if (ismeline(str)==true)
		{
			token=strtok(str, ":");
			token=strtok(NULL, ",");
			while(NULL!=token)
			{
				add_effective_against_me(newtype, gettypefromarray(types, numberOfTypes, token));
				token=strtok(NULL, ",");

			}
		}
		if (isotherline(str)==true)
				{
					token=strtok(str, ":");
					token=strtok(NULL, ",");
					while(NULL!=token)
					{
						add_effective_against_others(newtype, gettypefromarray(types, numberOfTypes, token));
						token=strtok(NULL, ",");

					}
				}
	   }
	while (fscanf(fptr, "%s", str)!=EOF)//create pokemons and insert them to the battle
	{
		token=strtok(str, ",");
		char* PokemonName = malloc(strlen(token)*sizeof(char*)+1);
		if(NULL==PokemonName)
		{
			free_all(newbattle, types, numberOfTypes, true);
			return NULL;
		}
		strcpy(PokemonName,token);
		token=strtok(NULL, ",");
		char* species =	 malloc(strlen(token)*sizeof(char*)+1);
		if(NULL==species)
		{
			free_all(newbattle, types, numberOfTypes, true);
			return NULL;
		}
		strcpy(species,token);
		token=strtok(NULL, ",");
		float Height =atof(token);
		token=strtok(NULL, ",");
		float Weight =atof(token);
		token=strtok(NULL, ",");
		int Power =atoi(token);
		token=strtok(NULL, ",");
		char* typename =malloc(sizeof(token)+1);
		if(NULL==typename)
		{
			free_all(newbattle, types, numberOfTypes, true);
			return NULL;
		}
		strcpy(typename,token);
		insertObject(newbattle, initPokemon(PokemonName, species, gettypefromarray(types, numberOfTypes, typename), Height, Weight, Power));
		free (PokemonName);
		free(species);
		free(typename);
	}
	fclose(fptr);
return newbattle;
}
int main(int argc, char *argv[])
{

   int numberOfTypes = atoi(argv[1]);
   int capacityInType =  atoi(argv[2]);
   char *path=argv[3];
   PokemonType* types[numberOfTypes];
   Battle battle = Build(path,numberOfTypes,capacityInType,types);

 int ch = 15;
 char typename[300];
 char pokname[300];
 char pokspecies[300];
 float height;
 float weight;
 int power;

 Pokemon* pokemontoadd;
 PokemonType* insetiontype;

   while( ch != 6 ) {
	  printf("Please choose one of the following numbers:\n");
      printf("1 : Print all Pokemons by types\n");
      printf("2 : Print all Pokemons types\n");
      printf("3 : Insert Pokemon to battles training camp\n");
      printf("4 : Remove strongest Pokemon by type\n");
      printf("5 : Fight\n");
      printf("6 : Exit\n");
      scanf("%s", &ch );
      ch=ch-48;  //convert from ascii to digit


      switch( ch )
      {
          case 1:     //Print all Pokemons by types;
        	  displayObjectsByCategories(battle);
				  break;

          case 2:     //Print all Pokemons types

        	 for(int i =0; i<numberOfTypes;i++)
        	 {
        		 print_PokemonType(types[i]);
        	 }
				  break;


          case 3:     //Insert Pokemon to battles training camp
        	  printf("Please enter Pokemon type name:\n");
              scanf("%s", typename );
              insetiontype = gettypefromarray(types, numberOfTypes, typename);
              if(NULL==insetiontype)
              {
            	 printf("Type name doesn't exist.\n");
            	 break;
              }
              if(insetiontype->NuminType>=capacityInType)
				{
				  printf("Type at full capacity.\n");
				  break;
				}
        	  printf("Please enter Pokemon name:\n");
              scanf("%s", pokname );
        	  printf("Please enter Pokemon species:\n");
              scanf("%s", pokspecies );
        	  printf("Please enter Pokemon height:\n");
              scanf("%f", &height );
        	  printf("Please enter Pokemon weight:\n");
              scanf("%f", &weight );
        	  printf("Please enter Pokemon attack:\n");
              scanf("%d", &power );
              pokemontoadd= initPokemon(pokname, pokspecies, insetiontype, height, weight, power);
              if(NULL==pokemontoadd)
              {
             	 free_all(battle, types, numberOfTypes, true);
              }
              insertObject(battle, pokemontoadd);
			  printf("The Pokemon was successfully added.\n");
			  print_Pokemon(pokemontoadd);

			  break;



          case 4:    //: Remove strongest Pokemon by type

        	  printf("Please enter type name:\n");
		      scanf("%s", typename );
		      insetiontype = gettypefromarray(types, numberOfTypes, typename);
		      if(NULL==insetiontype)
		      {
		    	  printf("Type name doesn't exist.\n");
		    	  break;
		      }
		      pokemontoadd=removeMaxByCategory(battle,typename);
		      if(NULL==pokemontoadd)
		                    {
		                  	  printf("There is no Pokemon to remove.\n");
		                    }
		                    else
		                    {
		                  	 insetiontype->NuminType--;
		                  	 printf( "The strongest Pokemon was removed:\n"	);
		                  	 print_Pokemon(pokemontoadd);
		                  	 freepokemon(pokemontoadd);
		                    }
        	  	  break;


          case 5:   //fight
        	  printf("Please enter Pokemon type name:\n");
			   scanf("%s", typename );
			   insetiontype = gettypefromarray(types, numberOfTypes, typename);
			   if(NULL==insetiontype)
			   {
				 printf("Type name doesn't exist.\n");
				 break;
			   }
			  printf("Please enter Pokemon name:\n");
			   scanf("%s", pokname );
			  printf("Please enter Pokemon species:\n");
			   scanf("%s", pokspecies );
			  printf("Please enter Pokemon height:\n");
			   scanf("%f", &height );
			  printf("Please enter Pokemon weight:\n");
			   scanf("%f", &weight );
			  printf("Please enter Pokemon attack:\n");
			   scanf("%d", &power );
			   pokemontoadd =initPokemon(pokname, pokspecies, insetiontype, height, weight, power);
			   printf("You choose to fight with:\n");
			   print_Pokemon(pokemontoadd);
			   Pokemon* bfig=fight(battle, pokemontoadd);
			   if(NULL==bfig)
			   {
				   printf("There are no Pokemons to fight against you.\n");
			   }
			   else
			   {
				   if(bfig!=pokemontoadd)
				   {
				   freepokemon(bfig);
				   }
			   }
			   freepokemon(pokemontoadd);
			   insetiontype->NuminType--;
        	                break;



          case 6:    //Exit
        	 free_all(battle, types, numberOfTypes, false);
        	  exit(0);
				  break;

          default:
        	  ch=10;
        	  printf("Please choose a valid number.\n");
        	  break;


      }
   }
   return 0;
}
