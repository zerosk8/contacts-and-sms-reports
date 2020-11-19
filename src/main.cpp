#include <iostream>
#include <string>
#include "exec_contacts_and_sms_reports.hpp"
#include "gui_contacts_and_sms_reports.hpp"

using namespace std;

const string PROGRAM_OPTIONS_FOR_CONTACTS_FILE_LOADING = "-c --contacts";
const string PROGRAM_OPTIONS_FOR_SMS_FILE_LOADING = "-s --sms";
const string PROGRAM_OPTIONS_FOR_OUTPUT_PATH = "-o --output";

string GetDestinationPathForReportsResults(const int & numberOfProgramArguments, char ** programArguments);
string GetOptionValueFromProgramArguments(const int & numberOfProgramArguments, char ** programArguments, 
const string & programOption);
signed char GetOptionIndexFromProgramArguments(const int & numberOfProgramArguments, 
char ** programArguments, const string & programOption);

int main(int argc, char ** argv)
{
    string contactsFilePath = GetOptionValueFromProgramArguments(argc,argv,
    PROGRAM_OPTIONS_FOR_CONTACTS_FILE_LOADING);
    string smsFilePath = GetOptionValueFromProgramArguments(argc,argv,
    PROGRAM_OPTIONS_FOR_SMS_FILE_LOADING);
    string destinationPathForReportsResults;
    ExecContactsAndSmsReports applicationExec;
    pair<bool,string> applicationExecResult;
    GUIContactsAndSmsReports applicationGUI;

    if(contactsFilePath.empty() && smsFilePath.empty())
    {
        applicationGUI = GUIContactsAndSmsReports("org.gtkmm.contacts_and_sms_reports");
        applicationGUI.Run();
    }
    else
    {
        destinationPathForReportsResults = GetDestinationPathForReportsResults(argc,argv);
        applicationExec = ExecContactsAndSmsReports(contactsFilePath,smsFilePath,
        destinationPathForReportsResults);
        applicationExecResult = applicationExec.Run();
        if(!applicationExecResult.first)
        {
            cerr << applicationExecResult.second << endl;
            return -1;
        }
    }

    return 0;
}

/**************************************/

string GetDestinationPathForReportsResults(const int & numberOfProgramArguments, char ** programArguments)
{
    string destinationPathForReportsResults = GetOptionValueFromProgramArguments
    (numberOfProgramArguments,programArguments,PROGRAM_OPTIONS_FOR_OUTPUT_PATH);
    if(destinationPathForReportsResults.empty())
    {
        return UTILS_FILE_SYSTEM.GetFileOrDirectoryPathString
        (UTILS_FILE_SYSTEM.GetCurrentDirectoryPath(),DIR_NAME_FOR_REPORT_RESULTS);
    }
    return UTILS_FILE_SYSTEM.GetFileOrDirectoryPathString
    (destinationPathForReportsResults,DIR_NAME_FOR_REPORT_RESULTS);
}

string GetOptionValueFromProgramArguments(const int & numberOfProgramArguments, char ** programArguments, 
const string & programOption)
{
    signed char argumentIndex;
    if((argumentIndex = GetOptionIndexFromProgramArguments(numberOfProgramArguments,programArguments,
    programOption)) == -1)
    {
        return string();
    }
    return programArguments[argumentIndex];
}

signed char GetOptionIndexFromProgramArguments(const int & numberOfProgramArguments, 
char ** programArguments, const string & programOption)
{
    signed char argumentIndex = 0;
    bool contactsOptionFound = false;
    while(argumentIndex < numberOfProgramArguments && !contactsOptionFound)
    {
        contactsOptionFound = programOption.find(programArguments[argumentIndex]) != string::npos;
        argumentIndex++;
    }
    
    if(contactsOptionFound && argumentIndex < numberOfProgramArguments)
    {
        return argumentIndex;
    }
    return -1;
}