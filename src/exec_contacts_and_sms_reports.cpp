#include "exec_contacts_and_sms_reports.h"

ExecContactsAndSmsReports::ExecContactsAndSmsReports(){}

ExecContactsAndSmsReports::ExecContactsAndSmsReports(std::string contactsFilePath, 
std::string smsFilePath, std::string destinationPathForReportsResults)
{
    this->contactsFilePath = contactsFilePath;
    this->smsFilePath = smsFilePath;
    this->destinationPathForReportsResults = destinationPathForReportsResults;
    this->setLanguageLocalization(LANGUAGE_LOCALIZATION);
}

std::pair<bool,std::string> ExecContactsAndSmsReports::ExecContactsAndSmsReports::Run()
{
    std::ifstream file;
    std::string fileLine;
    bool beginOfContact = false;
    std::string contactName;
    std::vector<TelephoneNumber> contactPhoneNumbers;
    std::vector<std::string> contactEmails;
    std::vector<Contact> listOfContacts;
    std::vector<Sms> listOfSms;
    std::pair<bool,std::string> isReportsResultsDirectoriesStructureValid;
    std::vector<std::pair<std::string,std::string>> navigationBarButtonsNamesAndLinks = 
    HTML_NAVIGATION_BAR_BUTTON_NAMES_AND_LINKS_FROM_ROOT_DIR;
    
    if(!smsFilePath.empty())
    {
        if(!UTILS_FILE_SYSTEM.OpenDestinationFile(file,smsFilePath.c_str()))
        {
            return std::pair<bool,std::string>(false,"Error opening the sms file: " + 
            std::string(strerror(errno)));
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
        CTML::Document smsHtmlDocument;
        UTILS_HTML.HtmlWriteDocumentHead(smsHtmlDocument,HTML_CHAR_ENCODING,HTML_VIEWPORT,HTML_AUTHOR,
        HTML_STYLE_SHEETS_PATHS_FROM_ROOT_DIR,HTML_DOCUMENT_HEAD_TITLE);
        if(!contactsFilePath.empty())
        {
            UTILS_HTML.HtmlWriteHeaderInDocumentBody(smsHtmlDocument,HTML_DOCUMENT_HEAD_TITLE,
            navigationBarButtonsNamesAndLinks,1);
        }
        else
        {
            navigationBarButtonsNamesAndLinks.erase(navigationBarButtonsNamesAndLinks.begin());
            UTILS_HTML.HtmlWriteHeaderInDocumentBody(smsHtmlDocument,HTML_DOCUMENT_HEAD_TITLE,
            navigationBarButtonsNamesAndLinks,0);
        }
        UTILS_HTML.HtmlWriteSmsReportResultInDocumentBody(smsHtmlDocument,HTML_SMS_TITLE,listOfSms);
        UTILS_HTML.HtmlWriteScriptsInDocumentBody(smsHtmlDocument,HTML_SCRIPTS_PATHS_FROM_ROOT_DIR);
        isReportsResultsDirectoriesStructureValid = 
        CheckAndCreateReportsResultsDirectoriesStructure(destinationPathForReportsResults);
        if(!isReportsResultsDirectoriesStructureValid.first)
        {
            return isReportsResultsDirectoriesStructureValid;
        }
        if(!smsHtmlDocument.WriteToFile(UTILS_FILE_SYSTEM.GetFileOrDirectoryPathString
        (destinationPathForReportsResults,FILE_SMS_REPORT_RESULT),CTML::Readability::MULTILINE))
        {
            return std::pair<bool,std::string>(false,"Error opening the sms report result file: " + 
            std::string(strerror(errno)));
        }
    }
    if(!contactsFilePath.empty())
    {
        if(!UTILS_FILE_SYSTEM.OpenDestinationFile(file,contactsFilePath.c_str()))
        {
            return std::pair<bool,std::string>(false,"Error opening the contacts file: " + 
            std::string(strerror(errno)));
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
            std::string directoryPathForSmsPerContactDocuments = UTILS_FILE_SYSTEM.
            GetFileOrDirectoryPathString(destinationPathForReportsResults,DIR_NAME_FOR_SMS_PER_CONTACT_DOCUMENTS);
            SaveEachSmsIntoEachContactListOfSms(listOfContacts,listOfSms);
            if(!UTILS_FILE_SYSTEM.ExistsDirectoryPath(directoryPathForSmsPerContactDocuments))
            {
                if(!UTILS_FILE_SYSTEM.CreateDirectoryPath(directoryPathForSmsPerContactDocuments))
                {
                    return std::pair<bool,std::string>(false,
                    "Error creating the directory for the sms per contact documents: " + 
                    std::string(strerror(errno)));
                }
            }
            CreateSmsPerContactDocuments(directoryPathForSmsPerContactDocuments,listOfContacts);
        }
        CTML::Document contactsHtmlDocument;
        UTILS_HTML.HtmlWriteDocumentHead(contactsHtmlDocument,HTML_CHAR_ENCODING,HTML_VIEWPORT,HTML_AUTHOR,
        HTML_STYLE_SHEETS_PATHS_FROM_ROOT_DIR,HTML_DOCUMENT_HEAD_TITLE);
        if(smsFilePath.empty())
        {
            navigationBarButtonsNamesAndLinks.pop_back();
        }
        UTILS_HTML.HtmlWriteHeaderInDocumentBody(contactsHtmlDocument,HTML_DOCUMENT_HEAD_TITLE,
        navigationBarButtonsNamesAndLinks,0);
        UTILS_HTML.HtmlWriteContactsReportResultInDocumentBody(contactsHtmlDocument,HTML_CONTACTS_TITLE,
        listOfContacts,UTILS_FILE_SYSTEM.GetFileOrDirectoryPathString(destinationPathForReportsResults,DIR_NAME_FOR_SMS_PER_CONTACT_DOCUMENTS),
        FILE_EXTENSION_HTML);
        UTILS_HTML.HtmlWriteScriptsInDocumentBody(contactsHtmlDocument,HTML_SCRIPTS_PATHS_FROM_ROOT_DIR);
        isReportsResultsDirectoriesStructureValid = 
        CheckAndCreateReportsResultsDirectoriesStructure(destinationPathForReportsResults);
        if(!isReportsResultsDirectoriesStructureValid.first)
        {
            return isReportsResultsDirectoriesStructureValid;
        }
        if(!contactsHtmlDocument.WriteToFile(UTILS_FILE_SYSTEM.GetFileOrDirectoryPathString(
        destinationPathForReportsResults,FILE_CONTACTS_REPORT_RESULT),CTML::Readability::MULTILINE))
        {
            return std::pair<bool,std::string>(false,
            "Error opening the contacts report result file: " + std::string(strerror(errno)));
        }
    }
    return std::pair<bool,std::string>(true,std::string());
}

ExecContactsAndSmsReports::~ExecContactsAndSmsReports(){}

/**************************************/

void ExecContactsAndSmsReports::setLanguageLocalization(const std::string & locale)
{
    std::setlocale(LC_ALL,locale.c_str());
}

std::pair<bool,std::string> ExecContactsAndSmsReports::CheckAndCreateReportsResultsDirectoriesStructure
(const std::string & destinationPathForReportsResults)
{
    std::string originPathForStyles = UTILS_FILE_SYSTEM.GetFileOrDirectoryPathString(".",
    DIR_NAME_FOR_STYLES);
    std::string destinationPathForStyles = UTILS_FILE_SYSTEM.
    GetFileOrDirectoryPathString(destinationPathForReportsResults,DIR_NAME_FOR_STYLES);
    if(!UTILS_FILE_SYSTEM.ExistsDirectoryPath(destinationPathForReportsResults))
    {
        if(!UTILS_FILE_SYSTEM.CreateDirectoryPath(destinationPathForReportsResults))
        {
            return std::pair<bool,std::string>(false,"Error creating the directory for the report results: " + 
            std::string(strerror(errno)));
        }
        if(!UTILS_FILE_SYSTEM.CreateDirectoryPath(destinationPathForStyles))
        {
            return std::pair<bool,std::string>(false,"Error creating the directory for the styles: " + 
            std::string(strerror(errno)));
        }
    }
    else
    {
        if(!UTILS_FILE_SYSTEM.ExistsDirectoryPath(destinationPathForStyles))
        {
            if(!UTILS_FILE_SYSTEM.CreateDirectoryPath(destinationPathForStyles))
            {
                return std::pair<bool,std::string>(false,"Error creating the directory for the styles: " + 
                std::string(strerror(errno)));
            }
        }
    }
    for(std::vector<std::string>::const_iterator fileNameIterator = DIR_CONTENT_STYLES.begin(); 
    fileNameIterator != DIR_CONTENT_STYLES.end(); ++fileNameIterator)
    {
        if(!UTILS_FILE_SYSTEM.CopyFile(UTILS_FILE_SYSTEM.GetFileOrDirectoryPathString(originPathForStyles,
        *fileNameIterator),UTILS_FILE_SYSTEM.GetFileOrDirectoryPathString(destinationPathForStyles,
        *fileNameIterator)))
        {
            return std::pair<bool,std::string>(false,"Error copying the file '" + *fileNameIterator + 
            "' in styles destination folder: " + std::string(strerror(errno)));
        }
    }
    return std::pair<bool,std::string>(true,std::string());
}

void ExecContactsAndSmsReports::InitializeContactInformation(std::string & contactName, 
std::vector<TelephoneNumber> & contactPhoneNumbers, std::vector<std::string> & contactEmails)
{
    contactName = std::string();
    contactPhoneNumbers.clear();
    contactEmails.clear();
}

bool ExecContactsAndSmsReports::IsLineBeginOfContact(const std::string & line)
{
    return DoLineStartsWithKeyword(line,CONTACT_START_LINE_KEYWORD);
}

bool ExecContactsAndSmsReports::IsLineEndOfContact(const std::string & line)
{
    return DoLineStartsWithKeyword(line,CONTACT_END_LINE_KEYWORD);
}

bool ExecContactsAndSmsReports::IsLineContactName(const std::string & line)
{
    return DoLineStartsWithKeyword(line,CONTACT_NAME_LINE_KEYWORD);
}

bool ExecContactsAndSmsReports::IsLineContactPhoneNumber(const std::string & line)
{
    return DoLineStartsWithKeyword(line,CONTACT_TELEPHONE_NUMBER_LINE_KEYWORD);
}

bool ExecContactsAndSmsReports::IsLineEmailAddress(const std::string & line)
{
    return DoLineStartsWithKeyword(line,CONTACT_EMAIL_LINE_KEYWORD);
}

bool ExecContactsAndSmsReports::IsLineSms(const std::string & line)
{
    std::string lineTrimmed = UTILS_STRING.TrimWhiteSpacesFromStartOfString(line);
    return DoLineStartsWithKeyword(lineTrimmed,SMS_START_LINE_KEYWORD) && 
    DoLineEndsWithSmsEndLineKeyWord(lineTrimmed);
}

bool ExecContactsAndSmsReports::DoLineStartsWithKeyword(const std::string & line, 
const std::string & keyword)
{
    return keyword.compare(line.substr(0,keyword.length())) == 0;
}

bool ExecContactsAndSmsReports::DoLineEndsWithSmsEndLineKeyWord(const std::string & line)
{
    size_t smsEndLineKeywordLength = SMS_END_LINE_KEYWORD.length();
    return SMS_END_LINE_KEYWORD.compare
    (line.substr(line.length() - smsEndLineKeywordLength,smsEndLineKeywordLength)) == 0;
}

std::string ExecContactsAndSmsReports::GetValueFromContactsFileLine(const std::string & line)
{
    return UTILS_STRING.TrimWhiteSpacesFromEndOfString(line
    .substr(line.find(CONTACT_FILE_LINE_FIELD_VALUE_DELIMITER) + 1));
}

std::string ExecContactsAndSmsReports::GetFieldValueFromSmsFileLine(const std::string & line, 
const std::string & field)
{
    size_t beginOfValue = line.find(field) + field.length() + SMS_FILE_LINE_FIELD_VALUE_DELIMITER.length() 
    + SMS_FIELD_VALUE_SURROUNDING.length();
    return line.substr(beginOfValue,line.find(SMS_FIELD_VALUE_SURROUNDING,beginOfValue) - beginOfValue);
}

void ExecContactsAndSmsReports::SaveContactInformation(std::vector<Contact> & listOfContacts, 
const std::string & contactName, const std::vector<TelephoneNumber> & contactPhoneNumbers, 
const std::vector<std::string> & contactEmails, const std::vector<Sms> & listOfSms)
{
    if(!contactName.empty() && !(contactPhoneNumbers.empty() && contactEmails.empty()))
    {
        listOfContacts.push_back(Contact(contactName,contactPhoneNumbers,contactEmails,listOfSms));
    }
}

void ExecContactsAndSmsReports::SaveSmsInformation(std::vector<Sms> & listOfSms, 
const std::string & telephoneNumber, const std::string & dateAndTime, const std::string & text, 
const std::string & smsType, const std::string & contactName)
{
    listOfSms.push_back(Sms(CreateTelephoneNumberValueFromString(telephoneNumber),contactName,dateAndTime,
    CreateSmsTypeValueFromString(smsType),text));
}

TelephoneNumber ExecContactsAndSmsReports::CreateTelephoneNumberValueFromString(const std::string & line)
{
    size_t firstOccurrenceOfBlankSpace = line.find(BLANK_CHAR);
    if(firstOccurrenceOfBlankSpace != std::string::npos)
    {
        return GetTelephoneNumberFromLineWithBlankSpaces(line,firstOccurrenceOfBlankSpace);
    }
    return GetTelephoneNumberFromLine(line);
}

SmsType ExecContactsAndSmsReports::CreateSmsTypeValueFromString(const std::string & line)
{
    if(SMS_INCOMING_VALUE_TYPE.compare(line) == 0)
        return incoming;
    else if(SMS_OUTGOING_VALUE_TYPE.compare(line) == 0)
        return outgoing;
    return unknown;
}

TelephoneNumber ExecContactsAndSmsReports::GetTelephoneNumberFromLineWithBlankSpaces
(const std::string & line, const size_t & firstOccurrenceOfBlankSpace)
{
    std::string countryDialCode, number;
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

std::string ExecContactsAndSmsReports::RemoveCharacterFromString(const std::string & stringWithCharacter, 
const char & characterToRemove)
{
    std::string resultString = stringWithCharacter;
    resultString.erase(remove(resultString.begin(),resultString.end(),characterToRemove),
    resultString.end());
    return resultString;
}

TelephoneNumber ExecContactsAndSmsReports::GetTelephoneNumberFromLine(const std::string & line)
{
    std::string countryDialCode, number;
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

std::vector<Contact> ExecContactsAndSmsReports::BubbleSortListOfContacts
(const std::vector<Contact> & listOfContacts)
{
    std::vector<Contact> sortedListOfContacts(listOfContacts);
    Contact temporalContact;
    std::vector<Contact>::iterator lastSelectedContactIterator = sortedListOfContacts.end() - 1;
    std::vector<Contact>::iterator lastRestOfContactsIterator = sortedListOfContacts.end();
    for(std::vector<Contact>::iterator selectedContactIterator = sortedListOfContacts.begin(); 
    selectedContactIterator != lastSelectedContactIterator; ++selectedContactIterator)
    {
        for(std::vector<Contact>::iterator restOfContactsIterator = selectedContactIterator + 1; 
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

std::vector<Contact> ExecContactsAndSmsReports::HeapSortListOfContacts
(const std::vector<Contact> & listOfContacts)
{
    std::vector<Contact> sortedListOfContacts(listOfContacts);
    unsigned int numberOfContacts = sortedListOfContacts.size();
    if(numberOfContacts <= 2)
    {
        std::string leftContactName, middleContactName, rightContactName;
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
    std::vector<Contact> firstHalfOfList(sortedListOfContacts.begin(),sortedListOfContacts.begin() 
    + halfListOfContacts);
    std::vector<Contact> secondHalfOfList(sortedListOfContacts.begin() 
    + halfListOfContacts,sortedListOfContacts.end());
    sortedListOfContacts = MergeSorteredListsOfContacts(HeapSortListOfContacts(firstHalfOfList)
    ,HeapSortListOfContacts(secondHalfOfList));
    return sortedListOfContacts;
}

std::vector<Contact> ExecContactsAndSmsReports::MergeSorteredListsOfContacts
(std::vector<Contact> firstHalfOfList, std::vector<Contact> secondHalfOfList)
{
    if(firstHalfOfList[firstHalfOfList.size() - 1].GetName().compare(secondHalfOfList[0].GetName()) <= 0)
    {
        return ConcatenateListsOfContacts(firstHalfOfList,secondHalfOfList);
    }
    if(secondHalfOfList[secondHalfOfList.size() - 1].GetName().compare(firstHalfOfList[0].GetName()) <= 0)
    {
        return ConcatenateListsOfContacts(secondHalfOfList,firstHalfOfList);
    }
    
    std::vector<Contact> resultList;
    bool isEmptyFirstHalfOfList = false, isEmptySecondHalfOfList = false;
    while(!(isEmptyFirstHalfOfList = firstHalfOfList.empty()) && 
    !(isEmptySecondHalfOfList = secondHalfOfList.empty()))
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

void ExecContactsAndSmsReports::AppendRestOfHalfListToResultList(std::vector<Contact> & resultList, 
const std::vector<Contact> & firstHalfOfList, const std::vector<Contact> & secondHalfOfList)
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

std::vector<Contact> ExecContactsAndSmsReports::ConcatenateListsOfContacts
(const std::vector<Contact> & firstList, const std::vector<Contact> & secondList)
{
    std::vector<Contact> resultList = firstList;
    resultList.insert(resultList.end(),secondList.begin(),secondList.end());
    return resultList;
}

void ExecContactsAndSmsReports::SwapLeftAndRightElementsOfList(std::vector<Contact> & listOfContacts)
{
    Contact temporalContact = listOfContacts[0];
    listOfContacts[0] = listOfContacts[1];
    listOfContacts[1] = temporalContact;
}

void ExecContactsAndSmsReports::RemoveDuplicatedTelephoneNumbers(std::vector<Contact> & listOfContacts)
{
    for(std::vector<Contact>::iterator contactsIterator = listOfContacts.begin(); 
    contactsIterator != listOfContacts.end(); ++contactsIterator)
    {
        std::vector<TelephoneNumber> listOfPhoneNumbers = (*contactsIterator).GetTelephoneNumbers();
        std::vector<TelephoneNumber>::iterator phoneNumbersIterator = listOfPhoneNumbers.begin();
        while(phoneNumbersIterator != listOfPhoneNumbers.end())
        {
            std::vector<TelephoneNumber>::iterator phoneNumbersNextIterator = phoneNumbersIterator + 1;
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

void ExecContactsAndSmsReports::SaveEachSmsIntoEachContactListOfSms(std::vector<Contact> & listOfContacts, 
std::vector<Sms> listOfSms)
{
    bool contactFound;
    for(std::vector<Sms>::iterator listOfSmsIterator = listOfSms.begin(); 
    listOfSmsIterator != listOfSms.end(); ++listOfSmsIterator)
    {
        contactFound = false;
        for(std::vector<Contact>::iterator contactsIterator = listOfContacts.begin(); !contactFound &&
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

void ExecContactsAndSmsReports::CreateSmsPerContactDocuments(const std::string & directoryPath, 
std::vector<Contact> listOfContacts)
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
            htmlDocument.WriteToFile(UTILS_FILE_SYSTEM.GetFileOrDirectoryPathString(directoryPath,
            contactName + FILE_EXTENSION_HTML),CTML::Readability::MULTILINE);
        }
    }
}