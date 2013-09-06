#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <time.h>

#ifdef __ATARI__
#include <peekpoke.h>
#endif

/* rollDice prototype for rolling the dice */
char rollDice (struct characterStats *, char);

/*build Character */
void buildCharacter (struct characterStats * );

/* file operations prototype */
char fileOps(char);

/*Standard character stats 
* proto code to build as a linked list and only store 10 sets of stats */
typedef struct characterStats{
	int wisdom;
	int intelligence;
	int dexterity;
	int strength;
	int charisma;
	int floor;
	int max;
	// struct characterStats *next;
}CHARACTER;

/* proto code to initalize the head of the linked list of characterStats */
// struct characterStatus *head = NULL;

/* Standard class modifiers */
enum charClass_t { 
	wizard_int,
	fighter_str,
	seductress_cha,
	cleric_wis
};

/* Standard race modifiers */
char elf[7] = {2,1,2,0,2,5,14};
char dwarf[7] = {1,-1,1,2,2,6,14};
char human[7] = {0,0,0,0,0,6,14};
char planes[7] = {2,2,0,-2,-2,3,14};

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

void addRaceModifiers (unsigned char *, struct characterStats *);

char main (void) {

	unsigned char c;
	
	char accept[2] = "0";
		
	unsigned char race;
	unsigned char total;

	CHARACTER *thisCharacter;

	// proto code for characterStats linked list 
	 struct characterStats *tempCharStats;
	 tempCharStats = (struct characterStats *)calloc(8, sizeof(struct characterStats));



	// zero fill the memory space for thisCharacter 
	thisCharacter = (CHARACTER *) calloc(7, sizeof(CHARACTER));

	// Seed the randomizer 
	randomizer();

	printf("Generating random stats.\n");
	printf("Choose a race ( [1] elf, [2] human, [3] dwarf, [4] planes ) : ");
	scanf("%1i", &race);

	while(1) {
		
		addRaceModifiers(&race, thisCharacter);
		buildCharacter(thisCharacter);
	
		printf("SizeOf struct thisCharacter = %d\n", sizeof(thisCharacter));
		printf("SizeOf int race = %d\n", sizeof(race));
		printf("SizeOf char c = %d\n", sizeof(c));

		total = thisCharacter->wisdom + thisCharacter->intelligence + thisCharacter->dexterity + thisCharacter->strength + thisCharacter->charisma;
	
		if (total >= 65) {
			// printf("Total %i\n", total);
			printf("Wis : %d\n", thisCharacter->wisdom);
			printf("Int : %d\n", thisCharacter->intelligence);
			printf("Dex : %d\n", thisCharacter->dexterity);
			printf("Str : %d\n", thisCharacter->strength);
			printf("Cha : %d\n", thisCharacter->charisma);

			printf("Do you accept, reroll or previous? [1] Accept, [2] Reroll, [3] Previous");
			scanf("%s", accept);

			/*
			* switch (choice) {
			* case 1:
				break;
			* case 2:
				;
			* case 3:
				printf("Wis : %d\n", thisCharacter->wisdom);
				printf("Int : %d\n", thisCharacter->intelligence);
				printf("Dex : %d\n", thisCharacter->dexterity);
				printf("Str : %d\n", thisCharacter->strength);
				printf("Cha : %d\n", thisCharacter->charisma);
				break;
			*/
			if (strcmp(accept, "Y") == 0) {
				printf("Accept == %s \n", accept);
				break;
			}
		// printf("Reroll : %i\n", total);

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


void addRaceModifiers (unsigned char *race, struct characterStats *thisCharacter) {
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
		srand(time(NULL)); 
	#endif

	return;
	
}

char rollDice (struct characterStats *thisCharacter, char numOfRolls) {
	unsigned char x = numOfRolls;
	unsigned char i, final = 0;
	unsigned char roll;
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

