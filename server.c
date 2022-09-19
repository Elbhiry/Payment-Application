#include <stdio.h>
#include <string.h>
#include "terminal.h"
#include "card.h"
#include "server.h"


static ST_accountsDB_t  DB[255] =
{ {7000, RUNNING, "1234567887654321"},
    {1525, RUNNING, "1239123412341734"},
    {18885, BLOCKED, "9874123412341734"},
    {8965, RUNNING, "1234567887654321"},
    {1854, RUNNING, "1777767887654321"},
    {778452, RUNNING, "1234512547654321"},
    {4886, RUNNING, "8974568923459874"},
    {7846, RUNNING, "1274444423459874"},
    {456, RUNNING, "5694568923451234"},
    {1000.0, BLOCKED, "5807007076043875"},
    {2000.0, RUNNING, "8989374615436851"}

};


static ST_transaction_t transation[255];

static int TSN=0;
static int  stopAt= 0;
static float currBalance = 0;
static int Stat;
static float curTrans = 0;



static EN_transState_t recieveTransactionData(ST_transaction_t* transData, ST_terminalData_t* termData, ST_cardData_t* cardData) {



    if (isValidAccount(&cardData) != SERVER_OK) {
        transData->transState = FRAUD_CARD;   
        printf("the account does not exist\n");
        return FRAUD_CARD;
    }

    if (isAmountAvailable(&termData) != SERVER_OK) {
        transData->transState = DECLINED_INSUFFECIENT_FUND;
        printf("DECLINED_INSUFFECIENT_FUND\n");

        return DECLINED_INSUFFECIENT_FUND;
    }

     if (isBlockedAccount(&DB[stopAt]) == BLOCKED)
     {
         transData->transState = DECLINED_STOLEN_CARD;
         printf("................................\n");
         printf("STOELEN CARD transaction made by this card is declined.");
         printf("................................\n");

         return  DECLINED_STOLEN_CARD;

     }


    if (saveTransaction(transData) != SERVER_OK) {
        return INTERNAL_SERVER_ERROR;
    }

    transData->transState = APPROVED;

    printf("Approved\n");
    //update data base with new balance
    DB[stopAt].balance -= termData->transAmount;

    printf("---------------------------------------\n");
    printf("New Balance is : %f\n", DB[stopAt].balance);
    printf("---------------------------------------\n");
  

    return APPROVED;
   
}

static EN_serverError_t  isValidAccount(ST_cardData_t* cardData) {

    for (int i = 0; i < 255; i++) {

        if (strcmp(DB[i].primaryAccountNumber, cardData->primaryAccountNumber) == 0) {
            currBalance = DB[i].balance;
            printf("................................\n");
            printf("Valid Account.......Proceed \n");
            printf("................................\n");
            printf("Current Account Balance is : % f\n", currBalance);
            printf("................................\n");

            stopAt = i;
            return SERVER_OK;
        }
    }
    return ACCOUNT_NOT_FOUND;

}


static void BlockThisAccount(ST_accountsDB_t* accountRefrence)
{
    //SET 
    DB[stopAt].state = BLOCKED;



}

static EN_serverError_t isAmountAvailable(ST_terminalData_t* termData) {
    if (currBalance >= termData->transAmount && currBalance > 0) {
        printf("---------------------------------------\n");

        printf("Required Amount is Available .....Proceed\n");
        printf("---------------------------------------\n");

        return SERVER_OK;
        }
    
    
    printf("---------------------------------------\n");
     // printf("Not Available Amount\nDeclined Insufficient Fund\n");
        printf("---------------------------------------\n");

        return LOW_BALANCE;
}

static EN_serverError_t isBlockedAccount(ST_accountsDB_t* accountRefrence)
{
    if(accountRefrence->state==BLOCKED){
        printf("---------------------------------------\n");

        printf("STOELEN CARD transaction made by this card is declined.\n");
        printf("---------------------------------------\n");

        return  BLOCKED_ACCOUNT;
    }
    printf("---------------------------------------\n");

  //  printf("Not Blocked yet action needed \n");
    printf("---------------------------------------\n");


   // printf("State : RUNNING \n");
    return SERVER_OK;
}


static EN_serverError_t UpdateBalance( ST_terminalData_t* termData) {


   // printf("Balance Before updating is : %f \n", DB[stopAt].balance);
    printf("---------------------------------------\n");
    if (DB[stopAt].balance >= termData->transAmount)
    {
        DB[stopAt].balance -= termData->transAmount;

        printf("New Balance is : %f\n", DB[stopAt].balance);
        printf("---------------------------------------\n");
    }
    else {
        printf("---------------------------------------\n");
        printf("Same Balance  : %f \n", DB[stopAt].balance);
        printf("---------------------------------------\n");

    }
}









static EN_serverError_t saveTransaction(ST_transaction_t* transData) {
   
 
    TSN = stopAt;
    //CHECK
    if (TSN > 255) {      /////    ||dropped connection////
        printf("SAVING_FAILED\n");
        return SAVING_FAILED;
    }       
    
    // SAVE

    ////////     CARD DATA   ////////
    transation[stopAt].transactionSequenceNumber = TSN;
   // _mbscpy_s(transation[stopAt].cardHolderData.cardHolderName, transData->cardHolderData.cardHolderName);   
   // _mbscpy_s(transation[stopAt].cardHolderData.primaryAccountNumber, transData->cardHolderData.primaryAccountNumber); 
  //  _mbscpy_s(transation[stopAt].cardHolderData.cardExpirationDate, transData->cardHolderData.cardExpirationDate);  
    ////   TERMINAL DATA  ///   /////
     transation[stopAt].terminalData.transAmount = transData->terminalData.transAmount;              
     transation[stopAt].terminalData.maxTransAmount = transData->terminalData.maxTransAmount;              
   //  _mbscpy_s(transation[stopAt].terminalData.transactionDate, transData->terminalData.transactionDate);   

       transation[stopAt].transactionSequenceNumber = transData->transactionSequenceNumber;


       transation[stopAt].transState = transData->transState;

       TSN++;

       transation[stopAt].transactionSequenceNumber = TSN;
       printf("---------------------------------------\n");

       printf("Done Saving\n");
       printf("---------------------------------------\n");

       
       return SERVER_OK;

}



static EN_serverError_t getTransaction(uint32_t transactionSequenceNumber, ST_transaction_t* transData) {
    for (int i = 0; i < 255; i++) {
        if (transactionSequenceNumber != transData->transactionSequenceNumber) {
            printf("TRANSACTION_NOT_FOUND\n");
            return TRANSACTION_NOT_FOUND;
        }
    }
    transData->transactionSequenceNumber = transactionSequenceNumber;

    printf("Valid TRANACTION\n");
    return SERVER_OK;
}



