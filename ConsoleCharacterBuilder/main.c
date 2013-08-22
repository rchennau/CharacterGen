#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

#ifdef __ATARI__
#include <peekpoke.h>
#endif

/* rollDice prototype for rolling the dice */
int rollDice (struct characterStats *, int);

/*build Character */
void buildCharacter (struct characterStats * );

/* file operations prototype */
int fileOps(char);

/* Standard character stats */
struct characterStats{
	int wisdom;
	int intelligence;
	int dexterity;
	int strength;
	int charisma;
	int floor;
	int max;
} thisCharacter;

/* Standard class modifiers */
enum class { 
	wizard,
	fighter,
	seductress,
	cleric
};

/* Standard race modifiers */
enum race { 
	elf,
	human,
	dwarf,
	planes
};

/* Seed the randomizer prototype */
void randomizer (void);

/* Character tweak modifiers */
struct characterSpecials { 
	int gender;
	int eyecolor;
	int height;
};

int main (void) {

	char c;
	char accept[2];
	
	thisCharacter.floor = 4;
	thisCharacter.max = 14;

	printf("Generating random stats.\n");
	randomizer();
	while(1) {
		buildCharacter(&thisCharacter);

		printf("Wis : %d\n", thisCharacter.wisdom);
		printf("Int : %d\n", thisCharacter.intelligence);
		printf("Dex : %d\n", thisCharacter.dexterity);
		printf("Str : %d\n", thisCharacter.strength);
		printf("Cha : %d\n", thisCharacter.charisma);

		printf("Do you accept? [Y/N] ");
		
		scanf("%s", accept);
		if (strcmp(accept, "Y") == 0) {
			printf("Accept == %s \n", accept);
			break;
		}
	}
	
	printf("Press any character to exit\n");

	while (1) {
		#ifdef __ATARI__
			c=cgetc();
		#else
			c=getc(stdin);
		#endif
		if (c=='\n' || c==EOF) {
			break;
		}
	}

	return 0;
}

/* In order to pass by reference a structure to a function you must define the type 'struct' with its tag (or name) and 
*  then finally the pointer to the instance of the structure you have initialized in main */
void randomizer (void) {
	
	#ifdef __ATARI__
		srand(PEEK(53770));
	#else
		srand(time(0));  
	#endif

	return;
	
}

int rollDice (struct characterStats *thisCharacter, int numOfRolls) {
	int x = numOfRolls;
	int i, final = 0;
	int roll;
	for (i = 0; i < x; i++) {
		roll = rand()%thisCharacter->max + thisCharacter->floor;
				
		if (roll > final) {
			final = roll;
		}
	}
	return final;
}

void buildCharacter (struct characterStats *thisCharacter) {

	thisCharacter->wisdom = rollDice(thisCharacter, 1);
	thisCharacter->intelligence = rollDice(thisCharacter, 1);
	thisCharacter->dexterity = rollDice(thisCharacter, 1);
	thisCharacter->strength = rollDice(thisCharacter, 1);
	thisCharacter->charisma = rollDice(thisCharacter, 1);

}


	






