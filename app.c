
#include "app.h"



#define appStart main
void appStart(void) {

	ST_cardData_t carddata ;
	ST_terminalData_t termdata ;
	ST_transaction_t TD;

	/////////////////// Card Data ///////////////////
	getCardHolderName(&carddata);
	getCardPAN(&carddata);
	getCardExpiryDate(&carddata);

	///////////////// Terminal Data /////////////////
	getTransactionDate(&termdata);
	if(isCardExpired(&carddata, &termdata)== RIGHT)
	{

		getTransactionAmount(&termdata);
		if(isBelowMaxAmount(&termdata)== RIGHT)      // predefined Max Amount ->  10000
		{
			if(isValidAccount(&carddata)== SERVER_OK)
			{
				if (isAmountAvailable(&termdata)== SERVER_OK)
				{
					UpdateBalance(&termdata);

					saveTransaction(&TD);

				}
				else
				{
					printf("---------------------------------------\n");
					printf("Declined Insufficient Fund\n");
					printf("---------------------------------------\n");

				}

			}
			else
			{
				printf("---------------------------------------\n");
				printf("Declined Invalid Account\n");
				printf("---------------------------------------\n");


			}

		}
		else
		{
			printf("---------------------------------------\n");
			printf("%s\n", "Declined Amount Exceeding Limit\n ");
			printf("---------------------------------------\n");

		}


	}
	else
	{
		printf("---------------------------------------\n");
		printf("%s\n", "Declined Expired Card");
		printf("---------------------------------------\n");


	}


	printf("Every Story Comes To An END ----THANK U\n---------------------------------------");




}

