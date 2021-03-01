#ifndef _CONTACTS_AND_SMS_REPORTS_HPP_
#define _CONTACTS_AND_SMS_REPORTS_HPP_
#include <fstream>
#include <string>
#include <vector>
#include <clocale>
#include "contact.hpp"
#include "utils_string.hpp"
#include "utils_file_system.hpp"
#include "utils_html.hpp"

// NOT "using namespace std;" BECAUSE OF THIS
// https://stackoverflow.com/questions/5527665/why-am-i-getting-string-does-not-name-a-type-error

const std::string LANGUAGE_LOCALIZATION = "en_GB.utf8";
const std::string CONTACT_START_LINE_KEYWORD = "BEGIN";
const std::string CONTACT_END_LINE_KEYWORD = "END";
const std::string CONTACT_NAME_LINE_KEYWORD = "FN";
const std::string CONTACT_TELEPHONE_NUMBER_LINE_KEYWORD = "TEL";
const std::string CONTACT_EMAIL_LINE_KEYWORD = "EMAIL";
const std::string CONTACT_FILE_LINE_FIELD_VALUE_DELIMITER = ":";
const std::string SMS_START_LINE_KEYWORD = "<sms";
const std::string SMS_TELEPHONE_NUMBER_KEYWORD = "address";
const std::string SMS_DATE_AND_TIME_KEYWORD = "time";
const std::string SMS_TEXT_KEYWORD = "body";
const std::string SMS_TYPE_KEYWORD = "type";
const std::string SMS_INCOMING_VALUE_TYPE = "1";
const std::string SMS_OUTGOING_VALUE_TYPE = "2";
const std::string SMS_CONTACT_NAME_KEYWORD = "name";
const std::string SMS_END_LINE_KEYWORD = "/>";
const std::string SMS_FILE_LINE_FIELD_VALUE_DELIMITER = "=";
const std::string SMS_FIELD_VALUE_SURROUNDING = "\"";
const std::string COUNTRY_DIAL_CODE_START = "+";
const unsigned int COUNTRY_DIAL_CODE_MAX_LENGTH = 3;
const char BLANK_CHAR = ' ';
const std::string DIR_NAME_FOR_STYLES = "styles";
const std::string DIR_NAME_FOR_REPORT_RESULTS = "Contacts and SMS report documents";
const std::string DIR_NAME_FOR_SMS_PER_CONTACT_DOCUMENTS = "SMS report documents per contact";
const std::vector<std::string> DIR_CONTENT_STYLES = {"bootstrap.min.css", "stylesheet.css", "jquery.min.js", 
"popper.min.js", "bootstrap.min.js", "contact-image.png"};
const std::string FILE_EXTENSION_HTML = ".html";
const std::string FILE_CONTACTS_REPORT_RESULT = "Contacts report document" + FILE_EXTENSION_HTML;
const std::string FILE_SMS_REPORT_RESULT = "SMS messages report document" + FILE_EXTENSION_HTML;
const std::string HTML_DOCUMENT_HEAD_TITLE = "Contacts and SMS Reports";
const std::string HTML_CONTACTS_TITLE = "Telephone contacts";
const std::string HTML_SMS_TITLE = "SMS messages";
const std::string HTML_CHAR_ENCODING = "UTF-8";
const std::string HTML_VIEWPORT = "width=device-width, initial-scale=1, shrink-to-fit=no";
const std::string HTML_AUTHOR = "Alejandro Mesa Rodríguez";
const std::vector<std::string> HTML_STYLE_SHEETS_PATHS_FROM_ROOT_DIR = 
{ "./" + DIR_NAME_FOR_STYLES + "/" + DIR_CONTENT_STYLES[0], 
"./" + DIR_NAME_FOR_STYLES + "/" + DIR_CONTENT_STYLES[1]};
const std::vector<std::string> HTML_SCRIPTS_PATHS_FROM_ROOT_DIR = 
{"./" + DIR_NAME_FOR_STYLES + "/" + DIR_CONTENT_STYLES[2],"./" + DIR_NAME_FOR_STYLES + "/" + DIR_CONTENT_STYLES[3], 
"./" + DIR_NAME_FOR_STYLES + "/" + DIR_CONTENT_STYLES[4]};
const std::vector<std::string> HTML_STYLE_SHEETS_PATHS_FROM_SMS_PER_CONTACT_DIR = 
{ "../" + DIR_NAME_FOR_STYLES + "/" + DIR_CONTENT_STYLES[0], 
"../" + DIR_NAME_FOR_STYLES + "/" + DIR_CONTENT_STYLES[1]};
const std::vector<std::string> HTML_SCRIPTS_PATHS_FROM_SMS_PER_CONTACT_DIR = 
{"../" + DIR_NAME_FOR_STYLES + "/" + DIR_CONTENT_STYLES[2],"../" + DIR_NAME_FOR_STYLES + "/" + DIR_CONTENT_STYLES[3], 
"../" + DIR_NAME_FOR_STYLES + "/" + DIR_CONTENT_STYLES[4]};
const std::vector<std::pair<std::string,std::string>> HTML_NAVIGATION_BAR_BUTTON_NAMES_AND_LINKS_FROM_ROOT_DIR = 
{ std::pair<std::string,std::string>("Contacts", FILE_CONTACTS_REPORT_RESULT), 
std::pair<std::string,std::string>("Messages", FILE_SMS_REPORT_RESULT) };
const std::vector<std::pair<std::string,std::string>> HTML_NAVIGATION_BAR_BUTTON_NAMES_AND_LINKS_FROM_SMS_PER_CONTACT_DIR = 
{ std::pair<std::string,std::string>("Contacts", "../" + FILE_CONTACTS_REPORT_RESULT), 
std::pair<std::string,std::string>("Messages", "../" + FILE_SMS_REPORT_RESULT) };

class ExecContactsAndSmsReports
{
    public:
        ExecContactsAndSmsReports();
        ExecContactsAndSmsReports(std::string contactsFilePath, std::string smsFilePath, 
        std::string destinationPathForReportsResults);
        std::pair<bool,std::string> Run();
        ~ExecContactsAndSmsReports();
    private:
        std::string contactsFilePath;
        std::string smsFilePath;
        std::string destinationPathForReportsResults;

        void setLanguageLocalization(const std::string & locale);
        std::pair<bool,std::string> CheckAndCreateReportsResultsDirectoriesStructure
        (const std::string & destinationPathForReportsResults);
        void InitializeContactInformation(std::string & contactName, 
        std::vector<TelephoneNumber> & contactPhoneNumbers, std::vector<std::string> & contactEmails);
        bool IsLineBeginOfContact(const std::string & line);
        bool IsLineEndOfContact(const std::string & line);
        bool IsLineContactName(const std::string & line);
        bool IsLineContactPhoneNumber(const std::string & line);
        bool IsLineEmailAddress(const std::string & line);
        bool IsLineSms(const std::string & line);
        bool DoLineStartsWithKeyword(const std::string & line, const std::string & keyword);
        bool DoLineEndsWithSmsEndLineKeyWord(const std::string & line);
        std::string GetValueFromContactsFileLine(const std::string & line);
        std::string GetFieldValueFromSmsFileLine(const std::string & line, const std::string & field);
        bool SaveContactInformation(std::vector<Contact> & listOfContacts,
            const std::string & contactName,
            const std::vector<TelephoneNumber> & contactPhoneNumbers,
            const std::vector<std::string> & contactEmails,
            const std::vector<Sms> & listOfSms = std::vector<Sms>());
        bool SaveSmsInformation(std::vector<Sms> & listOfSms,
            const std::string & telephoneNumber, const std::string & dateAndTime,
            const std::string & text, const std::string & smsType,
            const std::string & contactName);
        TelephoneNumber CreateTelephoneNumberValueFromString(const std::string & line);
        SmsType CreateSmsTypeValueFromString(const std::string & line);
        TelephoneNumber GetTelephoneNumberFromLineWithBlankSpaces(
            const std::string & line, const size_t & firstOccurrenceOfBlankSpace);
        TelephoneNumber GetTelephoneNumberFromLine(const std::string & line);
        std::string RemoveCharacterFromString(const std::string & stringWithCharacter, 
            const char & characterToRemove);
        std::vector<Contact> BubbleSortListOfContacts(const std::vector<Contact> & listOfContacts);
        std::vector<Contact> HeapSortListOfContacts(const std::vector<Contact> & listOfContacts);
        std::vector<Contact> MergeSorteredListsOfContacts(std::vector<Contact> firstHalfOfList, 
        std::vector<Contact> secondHalfOfList);
        void AppendRestOfHalfListToResultList(std::vector<Contact> & resultList, 
        const std::vector<Contact> & firstHalfOfList, const std::vector<Contact> & secondHalfOfList);
        std::vector<Contact> ConcatenateListsOfContacts(const std::vector<Contact> & firstList, 
        const std::vector<Contact> & secondList);
        void SwapLeftAndRightElementsOfList(std::vector<Contact> & listOfContacts);
        void RemoveDuplicatedTelephoneNumbers(std::vector<Contact> & listOfContacts);
        std::string GetNumberOfObjectsString(const std::string & title, 
        const unsigned int & numberOfObjects);
        void SaveEachSmsIntoEachContactListOfSms(std::vector<Contact> & listOfContacts, 
        std::vector<Sms> listOfSms);
        void CreateSmsPerContactDocuments(const std::string & directoryPath, 
        std::vector<Contact> listOfContacts);
};

#endif