#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "contact.h"
#include "utils_html.h"
#include "utils_file_system.h"
#include "CTML.h"

using namespace std;
using namespace CTML;

const string PROGRAM_OPTIONS_FOR_CONTACTS_FILE_LOADING = "-c --contacts";
const string PROGRAM_OPTIONS_FOR_SMS_FILE_LOADING = "-s --sms";
const string PROGRAM_OPTIONS_FOR_OUTPUT_PATH = "-o --output";
const string CONTACT_START_LINE_KEYWORD = "BEGIN";
const string CONTACT_END_LINE_KEYWORD = "END";
const string CONTACT_NAME_LINE_KEYWORD = "FN";
const string CONTACT_TELEPHONE_NUMBER_LINE_KEYWORD = "TEL";
const string CONTACT_EMAIL_LINE_KEYWORD = "EMAIL";
const string CONTACT_FILE_LINE_FIELD_VALUE_DELIMITER = ":";
const string SMS_START_LINE_KEYWORD = "<sms";
const string SMS_TELEPHONE_NUMBER_KEYWORD = "address";
const string SMS_DATE_AND_TIME_KEYWORD = "time";
const string SMS_TEXT_KEYWORD = "body";
const string SMS_TYPE_KEYWORD = "type";
const string SMS_INCOMING_VALUE_TYPE = "1";
const string SMS_OUTGOING_VALUE_TYPE = "2";
const string SMS_CONTACT_NAME_KEYWORD = "name";
const string SMS_END_LINE_KEYWORD = "/>";
const string SMS_FILE_LINE_FIELD_VALUE_DELIMITER = "=";
const string SMS_FIELD_VALUE_SURROUNDING = "\"";
const string COUNTRY_DIAL_CODE_START = "+";
const unsigned int COUNTRY_DIAL_CODE_MAX_LENGTH = 3;
const char BLANK_CHAR = ' ';
const string WHITE_SPACES_CHARS = " \t\r\n";
const string DIR_NAME_FOR_STYLES = "styles";
const string DIR_NAME_FOR_REPORT_RESULTS = "PhoneContactsSmsReportsResults";
const string DIR_NAME_FOR_SMS_PER_CONTACT_DOCUMENTS = "Sms";
const vector<string> DIR_CONTENT_STYLES = {"bootstrap.min.css", "stylesheet.css", "jquery.min.js", 
"popper.min.js", "bootstrap.min.js", "contact-image.png"};
const string FILE_EXTENSION_HTML = ".html";
const string FILE_CONTACTS_REPORT_RESULT = "contactsReportResult" + FILE_EXTENSION_HTML;
const string FILE_SMS_REPORT_RESULT = "smsReportResult" + FILE_EXTENSION_HTML;
const string HTML_DOCUMENT_HEAD_TITLE = "Phone Contacts Report";
const string HTML_CONTACTS_TITLE = "Telephone contacts";
const string HTML_SMS_TITLE = "SMS messages";
const string HTML_CHAR_ENCODING = "UTF-8";
const string HTML_VIEWPORT = "width=device-width, initial-scale=1, shrink-to-fit=no";
const string HTML_AUTHOR = "Alejandro Mesa";
const vector<string> HTML_STYLE_SHEETS_PATHS_FROM_ROOT_DIR = 
{ "./" + DIR_NAME_FOR_STYLES + "/" + DIR_CONTENT_STYLES[0], 
"./" + DIR_NAME_FOR_STYLES + "/" + DIR_CONTENT_STYLES[1]};
const vector<string> HTML_SCRIPTS_PATHS_FROM_ROOT_DIR = 
{"./" + DIR_NAME_FOR_STYLES + "/" + DIR_CONTENT_STYLES[2],"./" + DIR_NAME_FOR_STYLES + "/" + DIR_CONTENT_STYLES[3], 
"./" + DIR_NAME_FOR_STYLES + "/" + DIR_CONTENT_STYLES[4]};
const vector<string> HTML_STYLE_SHEETS_PATHS_FROM_SMS_PER_CONTACT_DIR = 
{ "../" + DIR_NAME_FOR_STYLES + "/" + DIR_CONTENT_STYLES[0], 
"../" + DIR_NAME_FOR_STYLES + "/" + DIR_CONTENT_STYLES[1]};
const vector<string> HTML_SCRIPTS_PATHS_FROM_SMS_PER_CONTACT_DIR = 
{"../" + DIR_NAME_FOR_STYLES + "/" + DIR_CONTENT_STYLES[2],"../" + DIR_NAME_FOR_STYLES + "/" + DIR_CONTENT_STYLES[3], 
"../" + DIR_NAME_FOR_STYLES + "/" + DIR_CONTENT_STYLES[4]};
const vector<pair<string,string>> HTML_NAVIGATION_BAR_BUTTON_NAMES_AND_LINKS_FROM_ROOT_DIR = 
{ pair<string,string>("Contacts", FILE_CONTACTS_REPORT_RESULT), 
pair<string,string>("Messages", FILE_SMS_REPORT_RESULT) };
const vector<pair<string,string>> HTML_NAVIGATION_BAR_BUTTON_NAMES_AND_LINKS_FROM_SMS_PER_CONTACT_DIR = 
{ pair<string,string>("Contacts", "../" + FILE_CONTACTS_REPORT_RESULT), 
pair<string,string>("Messages", "../" + FILE_SMS_REPORT_RESULT) };
static UtilsHtml UTILS_HTML;
static UtilsFileSystem UTILS_FILE_SYSTEM;

string GetDestinationPathForReportsResults(const int & numberOfProgramArguments, 
char ** programArguments);
signed char GetOptionIndexFromProgramArguments(const int & numberOfProgramArguments, 
char ** programArguments, const string & programOption);
bool CheckAndCreateReportsResultsDirectoriesStructure(const string & destinationPathForReportsResults);
bool WriteHtmlDocumentToReportResultFile(const Document & htmlDocument, const string & reportResultFileName, 
const string & errorMessageAtFailedOpenFile = "Error: Could not open the report result file");
void InitializeContactInformation(string & contactName, vector<TelephoneNumber> & contactPhoneNumbers, 
vector<string> & contactEmails);
bool IsLineBeginOfContact(const string & line);
bool IsLineEndOfContact(const string & line);
bool IsLineContactName(const string & line);
bool IsLineContactPhoneNumber(const string & line);
bool IsLineEmailAddress(const string & line);
bool IsLineSms(const string & line);
string TrimWhiteSpacesFromStartOfString(const string & line);
string TrimWhiteSpacesFromEndOfString(const string & line);
bool DoLineStartsWithKeyword(const string & line, const string & keyword);
bool DoLineEndsWithSmsEndLineKeyWord(const string & line);
string GetValueFromContactsFileLine(const string & line);
string GetFieldValueFromSmsFileLine(const string & line, const string & field);
void SaveContactInformation(vector<Contact> & listOfContacts, const string & contactName, 
const vector<TelephoneNumber> & contactPhoneNumbers, const vector<string> & contactEmails, 
const vector<Sms> & listOfSms = vector<Sms>());
void SaveSmsInformation(vector<Sms> & listOfSms, const string & telephoneNumber, const string & dateAndTime, const string & text, 
const string & smsType, const string & contactName);
TelephoneNumber CreateTelephoneNumberValueFromString(const string & line);
SmsType CreateSmsTypeValueFromString(const string & line);
TelephoneNumber GetTelephoneNumberFromLineWithBlankSpaces(const string & line, const size_t & firstOccurrenceOfBlankSpace);
string RemoveCharacterFromString(const string & stringWithCharacter);
TelephoneNumber GetTelephoneNumberFromLine(const string & line);
vector<Contact> BubbleSortListOfContacts(const vector<Contact> & listOfContacts);
vector<Contact> HeapSortListOfContacts(const vector<Contact> & listOfContacts);
vector<Contact> MergeSorteredListsOfContacts(vector<Contact> firstHalfOfList, vector<Contact> secondHalfOfList);
void AppendRestOfHalfListToResultList(vector<Contact> & resultList, const vector<Contact> & firstHalfOfList, 
const vector<Contact> & secondHalfOfList);
vector<Contact> ConcatenateListsOfContacts(const vector<Contact> & firstList, const vector<Contact> & secondList);
void SwapLeftAndRightElementsOfList(vector<Contact> & listOfContacts);
void RemoveDuplicatedTelephoneNumbers(vector<Contact> & listOfContacts);
string GetNumberOfObjectsString(const string & title, const unsigned int & numberOfObjects);
void SaveEachSmsIntoEachContactListOfSms(vector<Contact> & listOfContacts, vector<Sms> listOfSms);
void CreateSmsPerContactDocuments(const string & directoryPath, vector<Contact> listOfContacts);

int main(int argc, char ** argv)
{
    signed char indexInProgramArguments;
    ifstream file;
    string fileLine;
    bool beginOfContact = false;
    string contactName;
    vector<TelephoneNumber> contactPhoneNumbers;
    vector<string> contactEmails;
    vector<Contact> listOfContacts;
    vector<Sms> listOfSms;
    string destinationPathForReportsResults;
    
    destinationPathForReportsResults = GetDestinationPathForReportsResults(argc,argv);
    if((indexInProgramArguments = GetOptionIndexFromProgramArguments(argc,argv,
    PROGRAM_OPTIONS_FOR_SMS_FILE_LOADING)) != -1)
    {
        if(!UTILS_FILE_SYSTEM.OpenDestinationFile(file,argv[indexInProgramArguments]))
        {
            cerr << "Error: Could not open the sms file" << endl;
            cerr << "Error: " << strerror(errno) << endl;
            return -1;
        }
        while(!file.eof())
        {
            getline(file,fileLine);
            if(IsLineSms(fileLine))
            {
                SaveSmsInformation(listOfSms,GetFieldValueFromSmsFileLine(fileLine,SMS_TELEPHONE_NUMBER_KEYWORD),
                GetFieldValueFromSmsFileLine(fileLine,SMS_DATE_AND_TIME_KEYWORD),
                GetFieldValueFromSmsFileLine(fileLine,SMS_TEXT_KEYWORD),
                GetFieldValueFromSmsFileLine(fileLine,SMS_TYPE_KEYWORD),
                GetFieldValueFromSmsFileLine(fileLine,SMS_CONTACT_NAME_KEYWORD));
            }
        }
        file.close();
        Document smsHtmlDocument;
        UTILS_HTML.HtmlWriteDocumentHead(smsHtmlDocument,HTML_CHAR_ENCODING,HTML_VIEWPORT,HTML_AUTHOR,
        HTML_STYLE_SHEETS_PATHS_FROM_ROOT_DIR,HTML_DOCUMENT_HEAD_TITLE);
        UTILS_HTML.HtmlWriteHeaderInDocumentBody(smsHtmlDocument,HTML_DOCUMENT_HEAD_TITLE,
        HTML_NAVIGATION_BAR_BUTTON_NAMES_AND_LINKS_FROM_ROOT_DIR,1);
        UTILS_HTML.HtmlWriteSmsReportResultInDocumentBody(smsHtmlDocument,HTML_SMS_TITLE,listOfSms);
        UTILS_HTML.HtmlWriteScriptsInDocumentBody(smsHtmlDocument,HTML_SCRIPTS_PATHS_FROM_ROOT_DIR);
        if(!CheckAndCreateReportsResultsDirectoriesStructure(destinationPathForReportsResults))
        {
            return -1;
        }
        if(!WriteHtmlDocumentToReportResultFile(smsHtmlDocument,UTILS_FILE_SYSTEM.
        GetFileOrDirectoryPathString(destinationPathForReportsResults,FILE_SMS_REPORT_RESULT),
        "Error: Could not open the sms report result file"))
        {
            return -1;
        }
    }
    if((indexInProgramArguments = GetOptionIndexFromProgramArguments(argc,argv,
    PROGRAM_OPTIONS_FOR_CONTACTS_FILE_LOADING)) != -1)
    {
        if(!UTILS_FILE_SYSTEM.OpenDestinationFile(file,argv[indexInProgramArguments]))
        {
            cerr << "Error: Could not open the contacts file" << endl;
            cerr << "Error: " << strerror(errno) << endl;
            return -1;
        }
        while(!file.eof())
        {
            getline(file,fileLine);
            if(!beginOfContact)
            {
                if(IsLineBeginOfContact(fileLine))
                {
                    beginOfContact = true;
                    InitializeContactInformation(contactName,contactPhoneNumbers,contactEmails);
                }
            }
            else
            {
                if(IsLineContactName(fileLine))
                {
                    contactName = GetValueFromContactsFileLine(fileLine);
                }
                else if(IsLineContactPhoneNumber(fileLine))
                {
                    contactPhoneNumbers.push_back(CreateTelephoneNumberValueFromString(GetValueFromContactsFileLine(fileLine)));
                    
                }
                else if(IsLineEmailAddress(fileLine))
                {
                    contactEmails.push_back(GetValueFromContactsFileLine(fileLine));
                }
                else if(IsLineEndOfContact(fileLine) && beginOfContact)
                {
                    beginOfContact = false;
                    SaveContactInformation(listOfContacts,contactName,contactPhoneNumbers,contactEmails);
                }
            }
        }
        file.close();
        listOfContacts = HeapSortListOfContacts(listOfContacts);
        RemoveDuplicatedTelephoneNumbers(listOfContacts);
        if(!listOfSms.empty())
        {
            string directoryPathForSmsPerContactDocuments = UTILS_FILE_SYSTEM.
            GetFileOrDirectoryPathString(destinationPathForReportsResults,DIR_NAME_FOR_SMS_PER_CONTACT_DOCUMENTS);
            SaveEachSmsIntoEachContactListOfSms(listOfContacts,listOfSms);
            if(!UTILS_FILE_SYSTEM.ExistsDirectoryPath(directoryPathForSmsPerContactDocuments))
            {
                if(!UTILS_FILE_SYSTEM.CreateDirectoryPath(directoryPathForSmsPerContactDocuments))
                {
                    cerr << "Error: Could not create the directory for the sms per contact documents" 
                    << endl;
                    cerr << "Error: " << strerror(errno) << endl;
                    return -1;
                }
            }
            CreateSmsPerContactDocuments(directoryPathForSmsPerContactDocuments,listOfContacts);
        }
        Document contactsHtmlDocument;
        UTILS_HTML.HtmlWriteDocumentHead(contactsHtmlDocument,HTML_CHAR_ENCODING,HTML_VIEWPORT,HTML_AUTHOR,
        HTML_STYLE_SHEETS_PATHS_FROM_ROOT_DIR,HTML_DOCUMENT_HEAD_TITLE);
        UTILS_HTML.HtmlWriteHeaderInDocumentBody(contactsHtmlDocument,HTML_DOCUMENT_HEAD_TITLE,
        HTML_NAVIGATION_BAR_BUTTON_NAMES_AND_LINKS_FROM_ROOT_DIR,0);
        UTILS_HTML.HtmlWriteContactsReportResultInDocumentBody(contactsHtmlDocument,HTML_CONTACTS_TITLE,
        listOfContacts,UTILS_FILE_SYSTEM.GetFileOrDirectoryPathString(destinationPathForReportsResults,DIR_NAME_FOR_SMS_PER_CONTACT_DOCUMENTS),
        FILE_EXTENSION_HTML);
        UTILS_HTML.HtmlWriteScriptsInDocumentBody(contactsHtmlDocument,HTML_SCRIPTS_PATHS_FROM_ROOT_DIR);
        if(!CheckAndCreateReportsResultsDirectoriesStructure(destinationPathForReportsResults))
        {
            return -1;
        }
        if(!WriteHtmlDocumentToReportResultFile(contactsHtmlDocument,UTILS_FILE_SYSTEM.
        GetFileOrDirectoryPathString(destinationPathForReportsResults,FILE_CONTACTS_REPORT_RESULT),
        "Error: Could not open the contacts report result file"))
        {
            return -1;
        }
    }
}

/**************************************/

string GetDestinationPathForReportsResults(const int & numberOfProgramArguments, char ** programArguments)
{
    signed char indexInProgramArguments;
    if((indexInProgramArguments = GetOptionIndexFromProgramArguments(numberOfProgramArguments,
    programArguments,PROGRAM_OPTIONS_FOR_OUTPUT_PATH)) != -1)
    {
        return UTILS_FILE_SYSTEM.
        GetFileOrDirectoryPathString(string(programArguments[indexInProgramArguments]),
        DIR_NAME_FOR_REPORT_RESULTS);
    }
    else
    {
        return UTILS_FILE_SYSTEM.GetFileOrDirectoryPathString(UTILS_FILE_SYSTEM.GetCurrentDirectoryPath(),
        DIR_NAME_FOR_REPORT_RESULTS);
    }
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

bool CheckAndCreateReportsResultsDirectoriesStructure(const string & destinationPathForReportsResults)
{
    string originPathForStyles = UTILS_FILE_SYSTEM.GetFileOrDirectoryPathString(".",
    DIR_NAME_FOR_STYLES);
    string destinationPathForStyles = UTILS_FILE_SYSTEM.
    GetFileOrDirectoryPathString(destinationPathForReportsResults,DIR_NAME_FOR_STYLES);
    if(!UTILS_FILE_SYSTEM.ExistsDirectoryPath(destinationPathForReportsResults))
    {
        if(!UTILS_FILE_SYSTEM.CreateDirectoryPath(destinationPathForReportsResults))
        {
            cerr << "Error: Could not create the directory for the reports results" << endl;
            cerr << "Error: " << strerror(errno) << endl;
            return false;
        }
        if(!UTILS_FILE_SYSTEM.CreateDirectoryPath(destinationPathForStyles))
        {
            cerr << "Error: Could not create the directory for the styles" << endl;
            cerr << "Error: " << strerror(errno) << endl;
            return false;
        }
    }
    else
    {
        if(!UTILS_FILE_SYSTEM.ExistsDirectoryPath(destinationPathForStyles))
        {
            if(!UTILS_FILE_SYSTEM.CreateDirectoryPath(destinationPathForStyles))
            {
                cerr << "Error: Could not create the directory for the styles" << endl;
                cerr << "Error: " << strerror(errno) << endl;
                return false;
            }
        }
    }
    for(vector<string>::const_iterator fileNameIterator = DIR_CONTENT_STYLES.begin(); 
    fileNameIterator != DIR_CONTENT_STYLES.end(); ++fileNameIterator)
    {
        if(!UTILS_FILE_SYSTEM.CopyFile(UTILS_FILE_SYSTEM.GetFileOrDirectoryPathString(originPathForStyles,
        *fileNameIterator),UTILS_FILE_SYSTEM.GetFileOrDirectoryPathString(destinationPathForStyles,
        *fileNameIterator)))
        {
            cerr << "Error: Could not copy the file '" + *fileNameIterator + 
            "' in styles destination folder" << endl;
            cerr << "Error: " << strerror(errno) << endl;
            return false;
        }
    }
    return true;
}

bool WriteHtmlDocumentToReportResultFile(const Document & htmlDocument, const string & reportResultFileName, 
const string & errorMessageAtFailedOpenFile)
{
    if(!htmlDocument.WriteToFile(reportResultFileName,Readability::MULTILINE))
    {
        cerr << errorMessageAtFailedOpenFile << endl;
        cerr << "Error: " << strerror(errno) << endl;
        return false;
    }
    return true;
}

void InitializeContactInformation(string & contactName, vector<TelephoneNumber> & contactPhoneNumbers, 
vector<string> & contactEmails)
{
    contactName = string();
    contactPhoneNumbers.clear();
    contactEmails.clear();
}

bool IsLineBeginOfContact(const string & line)
{
    return DoLineStartsWithKeyword(line,CONTACT_START_LINE_KEYWORD);
}

bool IsLineEndOfContact(const string & line)
{
    return DoLineStartsWithKeyword(line,CONTACT_END_LINE_KEYWORD);
}

bool IsLineContactName(const string & line)
{
    return DoLineStartsWithKeyword(line,CONTACT_NAME_LINE_KEYWORD);
}

bool IsLineContactPhoneNumber(const string & line)
{
    return DoLineStartsWithKeyword(line,CONTACT_TELEPHONE_NUMBER_LINE_KEYWORD);
}

bool IsLineEmailAddress(const string & line)
{
    return DoLineStartsWithKeyword(line,CONTACT_EMAIL_LINE_KEYWORD);
}

bool IsLineSms(const string & line)
{
    string lineTrimmed = TrimWhiteSpacesFromStartOfString(line);
    return DoLineStartsWithKeyword(lineTrimmed,SMS_START_LINE_KEYWORD) && DoLineEndsWithSmsEndLineKeyWord(lineTrimmed);
}

string TrimWhiteSpacesFromStartOfString(const string & line)
{
    string lineTrimmed = line;
    if(!line.empty())
    {
         lineTrimmed = lineTrimmed.substr(lineTrimmed.find_first_not_of(WHITE_SPACES_CHARS));
    }
    return lineTrimmed;
}

string TrimWhiteSpacesFromEndOfString(const string & line)
{
    string lineTrimmed = line;
    if(!line.empty())
    {
         lineTrimmed = lineTrimmed.substr(0,lineTrimmed.find_last_not_of(WHITE_SPACES_CHARS) + 1);
    }
    return lineTrimmed;
}

bool DoLineStartsWithKeyword(const string & line, const string & keyword)
{
    return keyword.compare(line.substr(0,keyword.length())) == 0;
}

bool DoLineEndsWithSmsEndLineKeyWord(const string & line)
{
    size_t smsEndLineKeywordLength = SMS_END_LINE_KEYWORD.length();
    return SMS_END_LINE_KEYWORD.compare(line.substr(line.length() - smsEndLineKeywordLength,smsEndLineKeywordLength)) == 0;
}

string GetValueFromContactsFileLine(const string & line)
{
    return TrimWhiteSpacesFromEndOfString(line.substr(line.find(CONTACT_FILE_LINE_FIELD_VALUE_DELIMITER) + 1));
}

string GetFieldValueFromSmsFileLine(const string & line, const string & field)
{
    size_t beginOfValue = line.find(field) + field.length() + SMS_FILE_LINE_FIELD_VALUE_DELIMITER.length() + 
    SMS_FIELD_VALUE_SURROUNDING.length();
    return line.substr(beginOfValue,line.find(SMS_FIELD_VALUE_SURROUNDING,beginOfValue) - beginOfValue);
}

void SaveContactInformation(vector<Contact> & listOfContacts, const string & contactName, 
const vector<TelephoneNumber> & contactPhoneNumbers, const vector<string> & contactEmails, const vector<Sms> & listOfSms)
{
    if(!contactName.empty() && !(contactPhoneNumbers.empty() && contactEmails.empty()))
    {
        listOfContacts.push_back(Contact(contactName,contactPhoneNumbers,contactEmails,listOfSms));
    }
}

void SaveSmsInformation(vector<Sms> & listOfSms, const string & telephoneNumber, const string & dateAndTime, const string & text, 
const string & smsType, const string & contactName)
{
    listOfSms.push_back(Sms(CreateTelephoneNumberValueFromString(telephoneNumber),contactName,dateAndTime,
    CreateSmsTypeValueFromString(smsType),text));
}

TelephoneNumber CreateTelephoneNumberValueFromString(const string & line)
{
    size_t firstOccurrenceOfBlankSpace = line.find(BLANK_CHAR);
    if(firstOccurrenceOfBlankSpace != string::npos)
    {
        return GetTelephoneNumberFromLineWithBlankSpaces(line,firstOccurrenceOfBlankSpace);
    }
    return GetTelephoneNumberFromLine(line);
}

SmsType CreateSmsTypeValueFromString(const string & line)
{
    if(SMS_INCOMING_VALUE_TYPE.compare(line) == 0)
        return incoming;
    else if(SMS_OUTGOING_VALUE_TYPE.compare(line) == 0)
        return outgoing;
    return unknown;
}

TelephoneNumber GetTelephoneNumberFromLineWithBlankSpaces(const string & line, const size_t & firstOccurrenceOfBlankSpace)
{
    string countryDialCode, number;
    if(COUNTRY_DIAL_CODE_START.compare(line.substr(0,COUNTRY_DIAL_CODE_START.length())) == 0)
    {
        countryDialCode = line.substr(0,firstOccurrenceOfBlankSpace);
        number = line.substr(firstOccurrenceOfBlankSpace);
    }
    else
    {
        number = line;
    }
    number.erase(remove(number.begin(),number.end(),BLANK_CHAR),number.end());
    return TelephoneNumber(number,countryDialCode);
}

string RemoveCharacterFromString(const string & stringWithCharacter, const char & characterToRemove)
{
    string resultString = stringWithCharacter;
    resultString.erase(remove(resultString.begin(),resultString.end(),characterToRemove),resultString.end());
    return resultString;
}

TelephoneNumber GetTelephoneNumberFromLine(const string & line)
{
    string countryDialCode, number;
    if(COUNTRY_DIAL_CODE_START.compare(line.substr(0,COUNTRY_DIAL_CODE_START.length())) == 0)
    {
        countryDialCode = line.substr(0,COUNTRY_DIAL_CODE_MAX_LENGTH);
        number = line.substr(COUNTRY_DIAL_CODE_MAX_LENGTH);
    }
    else
    {
        number = line;
    }
    return TelephoneNumber(number,countryDialCode);
}

vector<Contact> BubbleSortListOfContacts(const vector<Contact> & listOfContacts)
{
    vector<Contact> sortedListOfContacts(listOfContacts);
    Contact temporalContact;
    vector<Contact>::iterator lastSelectedContactIterator = sortedListOfContacts.end() - 1;
    vector<Contact>::iterator lastRestOfContactsIterator = sortedListOfContacts.end();
    for(vector<Contact>::iterator selectedContactIterator = sortedListOfContacts.begin(); 
    selectedContactIterator != lastSelectedContactIterator; ++selectedContactIterator)
    {
        for(vector<Contact>::iterator restOfContactsIterator = selectedContactIterator + 1; 
        restOfContactsIterator != lastRestOfContactsIterator; ++restOfContactsIterator)
        {
            if((*selectedContactIterator).GetName().compare((*restOfContactsIterator).GetName()) > 0)
            {
                temporalContact = *selectedContactIterator;
                *selectedContactIterator = *restOfContactsIterator;
                *restOfContactsIterator = temporalContact;
            }
        }
    }
    return sortedListOfContacts;
}

vector<Contact> HeapSortListOfContacts(const vector<Contact> & listOfContacts)
{
    vector<Contact> sortedListOfContacts(listOfContacts);
    unsigned int numberOfContacts = sortedListOfContacts.size();
    if(numberOfContacts <= 2)
    {
        string leftContactName, middleContactName, rightContactName;
        switch(numberOfContacts)
        {
            case 2: if(sortedListOfContacts[0].GetName().compare(sortedListOfContacts[1].GetName()) > 0)
                    {
                        SwapLeftAndRightElementsOfList(sortedListOfContacts);
                    }
            case 1: return sortedListOfContacts;
                    break;
        }
    }
    unsigned int halfListOfContacts = numberOfContacts / 2;
    vector<Contact> firstHalfOfList(sortedListOfContacts.begin(),sortedListOfContacts.begin() + halfListOfContacts);
    vector<Contact> secondHalfOfList(sortedListOfContacts.begin() + halfListOfContacts,sortedListOfContacts.end());
    sortedListOfContacts = MergeSorteredListsOfContacts(HeapSortListOfContacts(firstHalfOfList),HeapSortListOfContacts(secondHalfOfList));
    return sortedListOfContacts;
}

vector<Contact> MergeSorteredListsOfContacts(vector<Contact> firstHalfOfList, vector<Contact> secondHalfOfList)
{
    if(firstHalfOfList[firstHalfOfList.size() - 1].GetName().compare(secondHalfOfList[0].GetName()) <= 0)
    {
        return ConcatenateListsOfContacts(firstHalfOfList,secondHalfOfList);
    }
    if(secondHalfOfList[secondHalfOfList.size() - 1].GetName().compare(firstHalfOfList[0].GetName()) <= 0)
    {
        return ConcatenateListsOfContacts(secondHalfOfList,firstHalfOfList);
    }
    
    vector<Contact> resultList;
    bool isEmptyFirstHalfOfList = false, isEmptySecondHalfOfList = false;
    while(!(isEmptyFirstHalfOfList = firstHalfOfList.empty()) && !(isEmptySecondHalfOfList = secondHalfOfList.empty()))
    {
        if(firstHalfOfList[0].GetName().compare(secondHalfOfList[0].GetName()) <= 0)
        {
            resultList.push_back(firstHalfOfList[0]);
            firstHalfOfList.erase(firstHalfOfList.begin());
        }
        else
        {
            resultList.push_back(secondHalfOfList[0]);
            secondHalfOfList.erase(secondHalfOfList.begin());
        }
    }
    AppendRestOfHalfListToResultList(resultList,firstHalfOfList,secondHalfOfList);
    return resultList;
}

void AppendRestOfHalfListToResultList(vector<Contact> & resultList, const vector<Contact> & firstHalfOfList, 
const vector<Contact> & secondHalfOfList)
{
    if(!firstHalfOfList.empty())
    {
        resultList.insert(resultList.end(),firstHalfOfList.begin(),firstHalfOfList.end());
    }
    else
    {
        resultList.insert(resultList.end(),secondHalfOfList.begin(),secondHalfOfList.end());
    }
}

vector<Contact> ConcatenateListsOfContacts(const vector<Contact> & firstList, const vector<Contact> & secondList)
{
    vector<Contact> resultList = firstList;
    resultList.insert(resultList.end(),secondList.begin(),secondList.end());
    return resultList;
}

void SwapLeftAndRightElementsOfList(vector<Contact> & listOfContacts)
{
    Contact temporalContact = listOfContacts[0];
    listOfContacts[0] = listOfContacts[1];
    listOfContacts[1] = temporalContact;
}

void RemoveDuplicatedTelephoneNumbers(vector<Contact> & listOfContacts)
{
    for(vector<Contact>::iterator contactsIterator = listOfContacts.begin(); contactsIterator != listOfContacts.end(); 
    ++contactsIterator)
    {
        vector<TelephoneNumber> listOfPhoneNumbers = (*contactsIterator).GetTelephoneNumbers();
        vector<TelephoneNumber>::iterator phoneNumbersIterator = listOfPhoneNumbers.begin();
        while(phoneNumbersIterator != listOfPhoneNumbers.end())
        {
            vector<TelephoneNumber>::iterator phoneNumbersNextIterator = phoneNumbersIterator + 1;
            if(phoneNumbersNextIterator != listOfPhoneNumbers.end() && 
            ((*phoneNumbersIterator).GetNumber().compare((*phoneNumbersNextIterator).GetNumber()) == 0))
            {
                if((*phoneNumbersIterator).ContainsCountryDialCode())
                {
                    listOfPhoneNumbers.erase(phoneNumbersNextIterator);
                    ++phoneNumbersIterator;
                }
                else
                {
                    phoneNumbersIterator = listOfPhoneNumbers.erase(phoneNumbersIterator);
                }
            }
            else
            {
                ++phoneNumbersIterator;
            }
        }
        (*contactsIterator).SetTelephoneNumbers(listOfPhoneNumbers);
    }
}

void SaveEachSmsIntoEachContactListOfSms(vector<Contact> & listOfContacts, vector<Sms> listOfSms)
{
    bool contactFound;
    for(vector<Sms>::iterator listOfSmsIterator = listOfSms.begin(); listOfSmsIterator != listOfSms.end();
    ++listOfSmsIterator)
    {
        contactFound = false;
        for(vector<Contact>::iterator contactsIterator = listOfContacts.begin(); !contactFound &&
        contactsIterator != listOfContacts.end(); ++contactsIterator)
        {
            if((*listOfSmsIterator).GetContactName().compare((*contactsIterator).GetName()) == 0)
            {
                contactFound = true;
                (*contactsIterator).AddSms(*listOfSmsIterator);
                listOfSmsIterator = listOfSms.erase(listOfSmsIterator);
                if(listOfSmsIterator != listOfSms.begin())
                {
                    --listOfSmsIterator;
                }
            }
        }
    }
}

void CreateSmsPerContactDocuments(const string & directoryPath, vector<Contact> listOfContacts)
{
    std::vector<Sms> listOfSms;
    for(std::vector<Contact>::iterator listOfContactsIterator = listOfContacts.begin();
    listOfContactsIterator != listOfContacts.end(); ++listOfContactsIterator)
    {
        listOfSms = (*listOfContactsIterator).GetListOfSms();
        if(!listOfSms.empty())
        {
            std::string contactName = (*listOfContactsIterator).GetName();
            CTML::Document htmlDocument;
            UTILS_HTML.HtmlWriteDocumentHead(htmlDocument,HTML_CHAR_ENCODING,HTML_VIEWPORT,HTML_AUTHOR,
            HTML_STYLE_SHEETS_PATHS_FROM_SMS_PER_CONTACT_DIR,HTML_DOCUMENT_HEAD_TITLE);
            UTILS_HTML.HtmlWriteHeaderInDocumentBody(htmlDocument,HTML_DOCUMENT_HEAD_TITLE,
            HTML_NAVIGATION_BAR_BUTTON_NAMES_AND_LINKS_FROM_SMS_PER_CONTACT_DIR,-1);
            UTILS_HTML.HtmlWriteSmsReportResultInDocumentBody(htmlDocument,
            contactName + " " + HTML_SMS_TITLE,(*listOfContactsIterator).GetListOfSms());
            UTILS_HTML.HtmlWriteScriptsInDocumentBody(htmlDocument,
            HTML_SCRIPTS_PATHS_FROM_SMS_PER_CONTACT_DIR);
            htmlDocument.WriteToFile(UTILS_FILE_SYSTEM.GetFileOrDirectoryPathString(directoryPath,contactName + FILE_EXTENSION_HTML),
            Readability::MULTILINE);
        }
    }
}