
#include <stdio.h>
#include <string.h>
#include "card.h"


EN_cardError_t getCardHolderName(ST_cardData_t* cardData) {
	
	char name[50];
	printf("Please Enter CardHolderName: ");
	gets(name);
	for (int i = 0; i < strlen(name); i++)         //Copy the name 
		cardData->cardHolderName[i] = name[i];
	//printf("%s\n", &cardData->cardHolderName);

	if (strlen(name) > 24 || strlen(name) < 20 || name == NULL) {
	//	printf("%s\n", "WRONG_NAME");

		return WRONG_NAME;
	}
	printf("................................\n");

	//printf("%s\n", "VALID NAME");
	printf("................................\n");

	return OK;

}
EN_cardError_t getCardExpiryDate(ST_cardData_t* cardData) {
	//Card expiry date is 5 characters string in the format "MM/YY"dcsdccvvvsfv
	char date[10];
	printf("%s", "Enter Expiry Date in the format MM / YY :  ");
	//ask for the card expiry date
	gets(date);
	//store it in card data.
	for (int i = 0; i < strlen(date); i++)
		cardData->cardExpirationDate[i] = date[i];

	//check
	if (strlen(date) != 5 || date == NULL || date[2] != '/') {
		//printf("%s\n", "WRONG_EXP_DATE");
		return WRONG_EXP_DATE;
	}
	printf("................................\n");

	//printf("%s\n", "VALID EXP Date");
	printf("................................\n");


	return OK;
}


EN_cardError_t getCardPAN(ST_cardData_t* cardData) {

	char PAN[30];

	//ask for the card's Primary Account Number
	printf("%s", "Enter PAN : ");
	
	gets(PAN);
	for (int i = 0; i < 20; i++) {
		cardData->primaryAccountNumber[i] = '\0';
	}
	//store it in card data.
	for (int i = 0; i < 20; i++)
		cardData->primaryAccountNumber[i] = PAN[i];
	cardData->primaryAccountNumber[19] ='\0';
	//printf("%s\n", cardData->primaryAccountNumber);
	if (PAN == NULL || strlen(PAN) > 19 || strlen(PAN) < 16) {
		return WRONG_PAN;

		//printf("%s\n", "WRONG PAN ");

}


	//printf("..................................\n%s", "VALID PAN \n");
	return OK;

}