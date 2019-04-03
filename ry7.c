#include <stdio.h>

int main(int argc, char *arvg[])
{
	int distance = 100;

	// float rounds final of 6 places
	float power = 2.34567850f;

	// Seems to only allow 5 digits  of prevision. Jeez.
	double super_power = 56789.4532123456789;
	char initial = 'A';
   	char first_name[] = "Zed";
   	char last_name[] = "Shaw";

	//first_name[2] <<= "P";

   	printf("You are %d miles away.\n", distance);
   	printf("You have %f levels of power.\n", power);
   	printf("You have %f awesome super powers.\n", super_power);
   	printf("I have an initial %c. \n", initial);
   	printf("I have a first name %s.\n", first_name);
   	printf("I have a last name %s.\n", last_name);
   	printf("My whole name is %s %c %s.\n",
		first_name, initial, last_name);

   	int bugs = 100;
   	double bug_rate = 1.2;

   	printf("You have %d bugs at the imaginary rate of %f.\n",
	  	bugs, bug_rate);

   	long universe_of_defects = 1L * 1024L * 1024L * 1024L * 124L;
	printf("The entre universe has %ld bugs.\n", universe_of_defects);

	double expected_bugs = bugs * bug_rate;
	printf("You are expected to have %f bugs.\n", expected_bugs);

	double part_of_universe = expected_bugs / universe_of_defects;
	printf("That is only a %e portion of the universe.\n",
		part_of_universe);

  // this makes no sense, just a demo of something weird
  char nul_byte = '\0';
  int care_percentage = bugs * nul_byte;
  printf("Which means you should care %d%%.\n", care_percentage);

  return 0;
}
