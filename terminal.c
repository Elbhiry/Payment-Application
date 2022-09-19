#include  <stdio.h>
#include <string.h>
#include "terminal.h"
#include "card.h"
#include <time.h>

#define mxAmount  10000

//float maxAmount = 0;
static 	float transAm = 0;

static 	float maxAmount = 0;

EN_terminalError_t getTransactionDate(ST_terminalData_t* termData) {
	//10 characters string in the format DD/MM/YYYY
	char date[11];	
	
	//ask for the transaction date

	printf("%s","Enter TransactionDate in Format DD/MM/YYYY  :");
	gets(date);
		//store it in terminal data.
	for (int i = 0; i < 11; i++)
		termData->transactionDate[i] = date[i];
	//for (int i = 0; i < 11; ++i) {printf("%c\n", date[i]);} 
	//("%d\n", strlen(date));

	if (date == NULL || strlen(date) < 10 || date[2] != '/' || date[5] != '/') {
		//printf("%s", "WRONGFORMAT\n");
		return WRONG_DATE;
	}
	printf("................................\n");

	//printf("%s", "VALID TransactionDate\n");
	printf("................................\n");

	return RIGHT;
}


EN_terminalError_t isCardExpired(ST_cardData_t cardData, ST_terminalData_t termData) {
	//Validity Check
	/*if (!(getCardExpiryDate(&cardData) == 0)) { printf("%s", "WRONGFORMAT\n");  return 100; }
	if (!(getTransactionDate(&termData) == 0)) {
		    printf("%s", "WRONGFORMAT\n");
		 	printf("Can't proceed with wrong data\n");
			return 100;
		}
	*/

	char trans[5] = { termData.transactionDate[8],termData.transactionDate[9],termData.transactionDate[3],termData.transactionDate[4],'\0' };
	char exp[5] = { cardData.cardExpirationDate[3], cardData.cardExpirationDate[4] , cardData.cardExpirationDate[0] , cardData.cardExpirationDate[1] ,'\0' };
	
	
	int tr =   atoi(trans);  //convert string to int
	int expi = atoi(exp);
	

	if (expi >= tr) {
		printf("---------------------------------------\n");
		printf("%s\n", "Active Card(NOT EXPIRED)\n");
		printf("---------------------------------------\n");

		return RIGHT;
	}
	//printf("%s\n", "Expired Card");
	return EXPIRED_CARD;


}


EN_terminalError_t getTransactionAmount(ST_terminalData_t* termData) {
	printf("Enter Tranaction Amount : ");
	scanf_s("%f", &transAm);

	//save
	termData->transAmount = transAm;
	if (transAm <= 0) {
		printf("%s\n", "NOT VALID");
		return  INVALID_AMOUNT;
	}
	//printf("%s\n", ".....................");

	return RIGHT;
}


EN_terminalError_t isBelowMaxAmount(ST_terminalData_t* termData) {

	if (mxAmount < transAm) {
       
		return EXCEED_MAX_AMOUNT;
     }
	
		
		printf("---------------------------------------\n");

	    printf("%s\n", "Below Max Amount\n ");
		printf("---------------------------------------\n");

		return RIGHT;
     }






EN_terminalError_t setMaxAmount(ST_terminalData_t* termData) {

	printf("Enter Max Amount : ");
	scanf_s("%f", &maxAmount);
	
	//SET   ................................................
	termData->maxTransAmount = maxAmount;
	//printf("maxAmount is:%f\n", termData->maxTransAmount);
	
	
	if (termData->maxTransAmount <= 0) {
	printf("INVALID  _  MAX  _  AMOUNT\n");
	return INVALID_MAX_AMOUNT;

    }

	//printf("...................\nmaxAmount is:%f\nproceed\n", termData->maxTransAmount);
	return RIGHT;
}







 




