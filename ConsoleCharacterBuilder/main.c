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
typedef struct characterStats{
	int wisdom;
	int intelligence;
	int dexterity;
	int strength;
	int charisma;
	int floor;
	int max;
}CHARACTER;

/* Standard class modifiers */
enum charClass { 
	wizard,
	fighter,
	seductress,
	cleric
};

/* Standard race modifiers */
int elf[7] = {2,1,2,0,2,5,14};
int dwarf[7] = {1,-1,1,2,2,6,14};
int human[7] = {0,0,0,0,0,6,14};
int planes[7] = {2,2,0,-2,-2,3,14};

/* Seed the randomizer prototype */
void randomizer (void);

/* Character tweak modifiers */
struct characterSpecials { 
	int gender;
	int eyecolor;
	int height;
};

void drawStats (struct characterStats *);

/* Function addRaceModifiers add the standard race modifiers to the character stats as part of the build character process. 
*  The function takes two parameters.  A pointer to the int race (declared in main) and pointer to the structure characterStats.
*  The purpose of the function was to ensure that the characterStats were reset with each die roll and the modifiers readded. 
*  The pointers serve as a means of optimization for the limited 8-bit machines 
*/
void addRaceModifiers (int *, struct characterStats *);

int main (void) {

	char c;
	char accept[2];
	int race;
	CHARACTER *thisCharacter;
	/* zero fill the memory space for thisCharacter */
	thisCharacter = (CHARACTER *) calloc(7, sizeof(CHARACTER));

	/* Seed the randomizer */
	randomizer();

	printf("Generating random stats.\n");
	printf("Choose a race ( [1] elf, [2] human, [3] dwarf, [4] planes ) : ");
	scanf("%1i", &race);

	while(1) {
		
		addRaceModifiers(&race, thisCharacter);
		buildCharacter(thisCharacter);

		printf("Wis : %d\n", thisCharacter->wisdom);
		printf("Int : %d\n", thisCharacter->intelligence);
		printf("Dex : %d\n", thisCharacter->dexterity);
		printf("Str : %d\n", thisCharacter->strength);
		printf("Cha : %d\n", thisCharacter->charisma);

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

void addRaceModifiers (int *race, struct characterStats *thisCharacter) {
	switch (*race) {
		
		case 1:
			thisCharacter->wisdom = elf[0];
			thisCharacter->floor = elf[5];
			thisCharacter->max = elf[6];
			break;
		case 2:
			thisCharacter->wisdom = dwarf[0];
			thisCharacter->floor = dwarf[5];
			thisCharacter->max = dwarf[6];
			break;
		case 3:
			thisCharacter->wisdom = human[0];
			thisCharacter->floor = human[5];
			thisCharacter->max = human[6];
			break;
		case 4:
			thisCharacter->wisdom = planes[0];
			thisCharacter->floor = planes[5];
			thisCharacter->max = planes[6];
			break;
		default:
			printf("No choice made; assigning human\n");
			break;
	}
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

	thisCharacter->wisdom = rollDice(thisCharacter, 1) + thisCharacter->wisdom;
	thisCharacter->intelligence = rollDice(thisCharacter, 1);
	thisCharacter->dexterity = rollDice(thisCharacter, 1);
	thisCharacter->strength = rollDice(thisCharacter, 1);
	thisCharacter->charisma = rollDice(thisCharacter, 1);
}

void drawStats (struct characterStats *thisCharacter) {
	// clrscr();
	// bgcolor("black");
}


	






