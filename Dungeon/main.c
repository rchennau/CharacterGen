#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <time.h>

// Characeter defines 
// #define CHARACTER_STAT_MAX		// maximum value for a stat. 
// #define CHARACTER_STAT_FLOOR	// minimum value for of a stat
// #define CHARACTER_STAT_WIS		// define to hold the wisdom stat for selected character
// #define CHARACTER_STAT_INT
// #define CHARACTER_STAT_DEX
// #define CHARACTER_STAT_STR
// #define CHARACTER_STAT_CHA
#define CHARACTER_STAT_ARR 7	// Size of Stat array
#define CHARACTER_STAT_NUM 5	// number of character stats (good for iterating over each stat)

#define RACES_INDEX 4			// size of array for all races [0...n]

#ifdef __ATARI__
#include <peekpoke.h>
#endif

/* On the Atari platform an int = 2 byte's while a char occupies a single byte.  
** Furthermore t
*/
typedef unsigned char byte;

char rollDice (char* array,byte);

/* file operations prototype */
// char fileOps(char);

/* Standard class modifiers */
union MyClassModifiers
{
	char wizard[7];
	char figher[7];
	char seducer[7];
	char cleric[7];
};

/* Build a 2D array to hold default race stats.  
** Standard race modifier array for character stat
** [0] = Wisdom
** [1] = Intelligence
** [2] = Dexterity
** [3] = Strength
** [4] = Charisma
** [5] = Floor
** [6] = Max
*/
char race_modifiers[RACES_INDEX][CHARACTER_STAT_ARR] = { 
	{2,1,2,0,2,5,14}, // elf
	{1,-1,1,2,2,6,14}, // dwarf
	{0,0,0,0,0,6,14}, // human
	{2,2,0,-2,-2,3,14} // planes
};

/* Seed the randomizer prototype */
void randomizer (void);

/* Character tweak modifiers */
struct characterSpecials { 
	int gender;
	int eyecolor;
	int height;
};

void drawStats (struct characterStats *);

char main (void) {

	byte c;		// used to capture input from the user
	
	char accept[2] = "0";
		
	unsigned char total;

	char myCharacter[7];

	printf("Choose a race ([0] elf, [1] dwarf, [2] human, [3] planes) : ");

	scanf("%1i", &c);
			
	while(1) {
		byte i;
		byte rolls = 1;
		byte temp = 0;
		byte total = 0;


		// Set the race modifiers based on race selection
		for (i = 0; i < CHARACTER_STAT_ARR; i++) {
			myCharacter[i] = race_modifiers[c][i];
		}

		for (i = 0; i < CHARACTER_STAT_NUM; i++) {
			
			// temp = rand()%myCharacter[6] + myCharacter[5];
			myCharacter[i] = rollDice(myCharacter, rolls);
			// myCharacter[i] = temp;
		}
		
		for (i = 0; i < CHARACTER_STAT_NUM; i++) {
			total = total + myCharacter[i];
		}
		
		if(total >= 65) {
			printf("Wis: %d ", myCharacter[0]);
			printf("Int: %d ", myCharacter[1]);
			printf("Dex: %d ", myCharacter[2]);
			printf("Str: %d ", myCharacter[3]);
			printf("Cha: %d\n\n", myCharacter[4]);
			printf("Do you accept, reroll or previous? [0] Accept, [1] Reroll, [2] Previous");
			scanf("%s", accept);
			if (strcmp(accept, "0") == 0) {
				printf("Accept == %s \n", accept);
				break;
			}
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
		srand(time(NULL)); 
	#endif

	return;
	
}

char rollDice (char* localCharacter, byte numOfRolls) {
	byte localNumOfRolls = numOfRolls;
	
	byte i, final = 0, roll;
	
	
	for (i = 0; i < localNumOfRolls; i++) {
		// Seed the randomizer with each roll ensures that numbers are random per roll and per start of the program.
		randomizer();
		roll = rand()%localCharacter[6] + localCharacter[5];
		printf("roll:%d\n", roll);
		if (roll >= final) {
			printf("FR = %i\n", roll);
			final = roll;
		}
	}
	return final;
}

void drawStats (struct characterStats *thisCharacter) {
	// clrscr();
	// bgcolor("black");
}

