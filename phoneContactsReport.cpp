#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "contact.h"
#include "utils_html.h"
#include "CTML.h"

using namespace std;
using namespace CTML;

const string PROGRAM_OPTIONS_FOR_CONTACTS_FILE_LOADING = "-c --contacts";
const string PROGRAM_OPTIONS_FOR_SMS_FILE_LOADING = "-s --sms";
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
const string HTML_CONTACTS_DOCUMENT_HEAD_TITLE = "Telephone Contacts";
const string HTML_SMS_DOCUMENT_HEAD_TITLE = "SMS Messages";
const string HTML_CHAR_ENCODING = "UTF-8";
const string HTML_AUTHOR = "Alejandro Mesa";
const string HTML_STYLE_SHEET_PATH_FOR_CONTACTS_AND_SMS_DOCUMENTS =
"../Bootstrap/bootstrap-4.0.0-beta.2-dist/css/bootstrap.min.css";
const string HTML_HEAD_STYLE_SHEET_PATH_FOR_SMS_PER_CONTACT_DOCUMENTS =
"../../Bootstrap/bootstrap-4.0.0-beta.2-dist/css/bootstrap.min.css";
const string DIR_PATH_FOR_SMS_PER_CONTACT_DOCUMENTS = "./Sms";
const string FILE_EXTENSION_HTML = ".html";
const string FILE_CONTACTS_REPORT_RESULT = "contactsReportResult" + FILE_EXTENSION_HTML;
const string FILE_SMS_REPORT_RESULT = "smsReportResult" + FILE_EXTENSION_HTML;
const unsigned char NUMBER_OF_COLUMNS_TABLE = 4;
const unsigned char NUMBER_OF_CONTACTS_PER_ROW = 4;
static UtilsHtml UTILS_HTML;

signed char GetValueIndexOfOptionFromProgramArguments(int numberOfProgramArguments, char ** programArguments, 
const string & programOption);
bool OpenFile(ifstream & file, char * fileName, const string & errorMessageAtFailedOpenFile = "Error: Could not open the file");
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
void CreateSmsPerContactDocuments(vector<Contact> listOfContacts, const string & title, const string & characterCodification, 
const string & author, const string & styleSheetFile, const string & smsDirectoryPath, const string & htmlFileExtension);

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
    
    if((indexInProgramArguments = GetValueIndexOfOptionFromProgramArguments(argc,argv,PROGRAM_OPTIONS_FOR_SMS_FILE_LOADING)) != -1)
    {
        if(!OpenFile(file,argv[indexInProgramArguments],"Error: Could not open the sms file"))
        {
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
        UTILS_HTML.HtmlWriteHead(smsHtmlDocument,HTML_SMS_DOCUMENT_HEAD_TITLE,HTML_CHAR_ENCODING,HTML_AUTHOR,
        HTML_STYLE_SHEET_PATH_FOR_CONTACTS_AND_SMS_DOCUMENTS);
        UTILS_HTML.HtmlWriteSmsReportResult(smsHtmlDocument,HTML_SMS_DOCUMENT_HEAD_TITLE,listOfSms);
        if(!WriteHtmlDocumentToReportResultFile(smsHtmlDocument,FILE_SMS_REPORT_RESULT,
        "Error: Could not open the sms report result file"))
        {
            return -1;
        }
    }
    if((indexInProgramArguments = GetValueIndexOfOptionFromProgramArguments(argc,argv,PROGRAM_OPTIONS_FOR_CONTACTS_FILE_LOADING)) != -1)
    {
        if(!OpenFile(file,argv[indexInProgramArguments],"Error: Could not open the contacts file"))
        {
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
            SaveEachSmsIntoEachContactListOfSms(listOfContacts,listOfSms);
            CreateSmsPerContactDocuments(listOfContacts,HTML_SMS_DOCUMENT_HEAD_TITLE,HTML_CHAR_ENCODING,HTML_AUTHOR,
            HTML_HEAD_STYLE_SHEET_PATH_FOR_SMS_PER_CONTACT_DOCUMENTS,DIR_PATH_FOR_SMS_PER_CONTACT_DOCUMENTS,FILE_EXTENSION_HTML);
        }
        Document contactsHtmlDocument;
        UTILS_HTML.HtmlWriteHead(contactsHtmlDocument,HTML_CONTACTS_DOCUMENT_HEAD_TITLE,HTML_CHAR_ENCODING,HTML_AUTHOR,
        HTML_STYLE_SHEET_PATH_FOR_CONTACTS_AND_SMS_DOCUMENTS);
        UTILS_HTML.HtmlWriteContactsReportResult(contactsHtmlDocument,HTML_CONTACTS_DOCUMENT_HEAD_TITLE,listOfContacts,
        NUMBER_OF_CONTACTS_PER_ROW,DIR_PATH_FOR_SMS_PER_CONTACT_DOCUMENTS,FILE_EXTENSION_HTML);
        if(!WriteHtmlDocumentToReportResultFile(contactsHtmlDocument,FILE_CONTACTS_REPORT_RESULT,
        "Error: Could not open the contacts report result file"))
        {
            return -1;
        }
    }
}

/**************************************/

signed char GetValueIndexOfOptionFromProgramArguments(int numberOfProgramArguments, char ** programArguments, 
const string & programOption)
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

bool OpenFile(ifstream & file, char * fileName, const string & errorMessageAtFailedOpenFile)
{
    file.open(fileName,ios::in);
    if(file.fail())
    {
        cerr << errorMessageAtFailedOpenFile << endl;
        cerr << "Error: " << strerror(errno) << endl;
        return false;
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

void CreateSmsPerContactDocuments(vector<Contact> listOfContacts, const string & title, const string & characterCodification, 
const string & author, const string & styleSheetFile, const string & smsDirectoryPath, const string & htmlFileExtension)
{
    std::vector<Sms> listOfSms;
    for(std::vector<Contact>::iterator listOfContactsIterator = listOfContacts.begin();
    listOfContactsIterator != listOfContacts.end(); ++listOfContactsIterator)
    {
        listOfSms = (*listOfContactsIterator).GetListOfSms();
        if(!listOfSms.empty())
        {
            std::string contactName = (*listOfContactsIterator).GetName(), documentTitle = contactName + " " + title;
            CTML::Document htmlDocument;
            UTILS_HTML.HtmlWriteHead(htmlDocument,documentTitle,characterCodification,author,styleSheetFile);
            UTILS_HTML.HtmlWriteSmsReportResult(htmlDocument,documentTitle,(*listOfContactsIterator).GetListOfSms());
            htmlDocument.WriteToFile(smsDirectoryPath + "/" + contactName + htmlFileExtension,Readability::MULTILINE);
        }
    }
}
