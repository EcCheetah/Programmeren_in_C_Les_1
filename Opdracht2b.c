#include <stdio.h>
#include <string.h>

int main(int argc, char **argv) {
	char firstName[30] = "Nora";
	char lastName[30] = "van het Spil";
  	int bsn = 23456789;
  	char birthDate[30] = "28-11-2000";
	char landOfBirth[30] = "netherlands";
	int passportId = 62;

  	printf("First name : %s\n", firstName);
  	printf("Last name : %s\n", lastName);
  	printf("BSN : %d\n", bsn);
  	printf("Birthdate : %s\n", birthDate);
  	printf("Land of birth : %s\n", landOfBirth);
  	printf("Passport ID : %d\n", passportId);

  	return 0;
}
