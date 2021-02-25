/*
 * AirgeadBankingAllInOne.cpp
 *
 *  Date: 02/06/2021
 *  Author: Andrew Alves
 */


#include <iostream> 
using namespace std;
#include <string>
#include <sstream>
#include <iostream>
#include <vector>
#include <conio.h>

class AirgeadBankingApp{

    private:
        double m_initialInvestment = 0.00;
        double m_monthlyDeposit    = 0.00;
        double m_annualInterest    = 0.00;
        int    m_numYears          = 1;

        vector<int>    m_year;
        vector<double> m_yearEndBalance;
        vector<double> m_yearEndEarnedInterest; 
        vector<string> reportRows;

    public: 
        AirgeadBankingApp(void){           //constructor function for the AirgeadBankingApp
                // Here we will declare class variables to store calculations and user input
                // Decided to make it private because I would only like my class to be able to modify these values                      

                m_year.resize(m_numYears);
                m_yearEndBalance.resize(m_numYears);
                m_yearEndEarnedInterest.resize(m_numYears);
                reportRows.resize(m_numYears);

                for(int i = 0; i < m_numYears; i++){
                    m_year[i] = i+1;
                    m_yearEndBalance[i] = 0.00;
                    m_yearEndEarnedInterest[i] = 0.00;
                }    
        }  

        void inputMainMenu(){
            //Here we will print the main menu which will be formatted as such:
            /*
            **********************************
            *********** Data Input ***********
            Inital Investment Amount : $
                    Monthly Deposit  : $
                    Annual Interest  : %
                    Number of Years  :  
            
            Press any key to coninue...

            */

            cout << endl; 
            cout << "**********************************" << endl;
            cout << "*********** Data Input ***********" << endl;
            
            cout << "Inital Investment Amount : $";
            cin >> m_initialInvestment;
            cin.ignore(); 

            cout <<"        Monthly Deposit  : $";
            cin >> m_monthlyDeposit;
            cin.ignore(); 
 
            cout << "        Annual Interest  : %";
            cin >> m_annualInterest;
            cin.ignore();

            cout << "        Number of Years  :  ";
            cin >> m_numYears;
            cin.ignore();

            cout << "Press any key to coninue..." << endl << endl;
            getch();    
        }
        void printYearEndBalanceReports(){
            //Here we will print two reports one after the other.

            AirgeadBankingApp::calculateReportNoDeposit();  //update the class variables with data not using montly deposits

            cout << endl; 
            cout << "==============================================================" << endl; 
            cout << "   Balance and Interest Without Additional Monthly Deposits   " << endl;
            cout << "==============================================================" << endl;
            cout << "   Year   |   Year End Balance   |   Year End Earned Interest " << endl;
            cout << "--------------------------------------------------------------" << endl;
            AirgeadBankingApp::printReportRows();

            //Then we will want to recalculate using monthly deposits
            AirgeadBankingApp::calculateReportWithDeposit(); //update the class variables with data using montly deposits

            cout << endl;
            cout << "==============================================================" << endl;
            cout << "     Balance and Interest With Additional Monthly Deposits    " << endl;
            cout << "==============================================================" << endl;
            cout << "   Year   |   Year End Balance   |   Year End Earned Interest " << endl;
            cout << "--------------------------------------------------------------" << endl;
            AirgeadBankingApp::printReportRows();

            cout << endl << "Press any key to coninue..." << endl;
            getch();  
        }

    private:
        //make these functions private because they will only be needed to when making the reporting, and isn't needed by the user of this class.

        void calculateReportNoDeposit(){
            /*
            Interest: Money earned based on the “annual interest” rate input by the user. The
                        interest based on an opening amount of $1 and a deposited amount of $50 with an
                        interest rate of 5% compounded monthly is:
                        (Opening Amount + Deposited Amount) * ((Interest Rate/100)/12)
                        OR
                        (1 + 50) * ((5/100)/12)
                        Note: Dividing by 100 converts the interest rate percentage to a decimal.
                        Note: 12 is the number of months in a year. Dividing the yearly amount by twelve gives
                        monthly compounded interest.
            */

            //Calculate annual interest without additional deposits.
            //Re-size the vectors to be sized for the new years data input
            m_year.resize(m_numYears);
            m_yearEndBalance.resize(m_numYears);
            m_yearEndEarnedInterest.resize(m_numYears);
            
            for(int year=0; year < m_numYears; year++){
                if(year==0){
                    m_year[year] = year+1;
                    m_yearEndBalance[year] = m_initialInvestment + (m_initialInvestment)*((m_annualInterest/100));
                    m_yearEndEarnedInterest[year] = (m_initialInvestment)*((m_annualInterest/100));
                }
                else{
                    m_year[year] = year+1;
                    m_yearEndBalance[year] = m_yearEndBalance[year-1] + (m_yearEndBalance[year-1])*((m_annualInterest/100));
                    m_yearEndEarnedInterest[year] = (m_yearEndBalance[year-1])*((m_annualInterest/100));
                }
            }

        }

        void calculateReportWithDeposit(){
            //Calculate annual interest without additional deposits.
            //Re-size the vectors to be sized for the new years data input
            m_year.resize(m_numYears);
            m_yearEndBalance.resize(m_numYears);
            m_yearEndEarnedInterest.resize(m_numYears);

            double tempMonthEndBalance = m_initialInvestment;
            double tempMonthEndEarnedInterest = 0.00;

            for(int year=0; year < m_numYears; year++){
                tempMonthEndEarnedInterest = 0.00;
                for(int month = 0; month < 12; month++){
                    tempMonthEndBalance = tempMonthEndBalance + m_monthlyDeposit;
                    tempMonthEndEarnedInterest = tempMonthEndEarnedInterest + (tempMonthEndBalance * ((m_annualInterest/100)/12));
                    tempMonthEndBalance = tempMonthEndBalance + (tempMonthEndBalance * ((m_annualInterest/100)/12));   
                }
                    m_yearEndBalance[year] = tempMonthEndBalance;
                    m_yearEndEarnedInterest[year] = tempMonthEndEarnedInterest;

                    //m_yearEndBalance[year] = (m_initialInvestment + m_monthlyDeposit) + (m_initialInvestment + m_monthlyDeposit)*((m_annualInterest/100));
                    //m_yearEndEarnedInterest[year] = (m_initialInvestment + m_monthlyDeposit)*((m_annualInterest/100)/12);
                    //m_yearEndBalance[year] = (m_yearEndBalance[year-1] + m_monthlyDeposit) + (m_yearEndBalance[year-1] + m_monthlyDeposit)*((m_annualInterest/100)/12);
                    //m_yearEndEarnedInterest[year] = (m_yearEndBalance[year-1] + m_monthlyDeposit)*((m_annualInterest/100)/12);
            }
        }

        void printReportRows(){
            int spacesYear = 10;
            int spacesYearEndBalance = 22;
            int spacesYearEndEarnedInterest = 28;

            stringstream numToStr;
            string strYear;
            string strYearEndBalance;
            string strYearEndEarnedInterest;
        /*
                62 spaces across the whole report
                10 spaces for the Year
                22 spaces for the Year End Balance 
                28 spaces for the Year End Earned Interest
        */
            reportRows.resize(m_numYears);
            numToStr.precision(2);

            //Convert our data to strings and handle each row of strings
            for(int i=0; i < m_numYears; i++){
                numToStr << fixed << m_year[i];
                numToStr >> strYear;

                AirgeadBankingApp::clearStringStream(numToStr);

                numToStr << fixed << m_yearEndBalance[i];
                numToStr >> strYearEndBalance;

                AirgeadBankingApp::clearStringStream(numToStr);

                numToStr << fixed << m_yearEndEarnedInterest[i];
                numToStr >> strYearEndEarnedInterest;

                AirgeadBankingApp::clearStringStream(numToStr);

                //put $ in front of dollar values
                strYearEndBalance.insert(strYearEndBalance.begin(), 1, '$');
                strYearEndEarnedInterest.insert(strYearEndEarnedInterest.begin(), 1, '$');

                //Pad the string with spaces
                //str.insert(beginning, spaces left after our new string, pad with spaces)
                strYear.insert(strYear.begin(), spacesYear - strYear.length(), ' ');
                strYearEndBalance.insert(strYearEndBalance.begin(), spacesYearEndBalance - strYearEndBalance.length(), ' ');
                strYearEndEarnedInterest.insert(strYearEndEarnedInterest.begin(), spacesYearEndEarnedInterest - strYearEndEarnedInterest.length(), ' ');

                cout << strYear << "|" << strYearEndBalance << "|" << strYearEndEarnedInterest <<endl;
            }
        }

        void clearStringStream(stringstream& stream){
                stream.str("");
                stream.clear();
            }
};

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