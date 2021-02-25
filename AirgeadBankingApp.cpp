/*
 * AirgeadBankingApp.cpp
 *
 *  Date: 02/06/2021
 *  Author: Andrew Alves
 */

#include "AirgeadBankingClass.h"

int main(){

    //create the class instance normally:
    AirgeadBankingApp bankingApp;

    //create the class from the Standards document:
    //    auto bankingClass = std::make_shared<AirgeadBankingApp>();

    while(1){
        bankingApp.inputMainMenu();
        bankingApp.printYearEndBalanceReports();
    }
    
    return 0;
}