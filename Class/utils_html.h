#ifndef _UTILS_HTML_H_
#define _UTILS_HTML_H_
#include <string>
#include <string.h>
#include "CTML.h"
#include "contact.h"
#include "sms.h"

// NOT "using namespace std;" BECAUSE OF THIS
// https://stackoverflow.com/questions/5527665/why-am-i-getting-string-does-not-name-a-type-error

class UtilsHtml
{
    public:
        void HtmlWriteHead(CTML::Document & htmlDocument, const std::string & title, const std::string & characterCodification,
        const std::string & author, const std::string & styleSheetFile);
        void HtmlWriteSmsReportResult(CTML::Document & htmlDocument, const std::string & headerTitle, std::vector<Sms> listOfSms);
        void HtmlWriteContactsReportResult(CTML::Document & htmlDocument, const std::string & headerTitle,
        std::vector<Contact> listOfContacts, const unsigned char & numberOfContactsPerRow,
        const std::string & directoryPathForSmsPerContactDocuments, const std::string & fileExtensionHtml);
    private:
        std::string HtmlGetNumberOfObjectsMessage(const unsigned int & numberOfObjects, const bool & isContactsReportResult);
        CTML::Node HtmGetContactsListNode(std::vector<Contact> listOfContacts, const unsigned char & numberOfContactsPerRow,
        const std::string & directoryPathForSmsPerContactDocuments, const std::string & fileExtensionHtml);
        void HtmlInitializePanelForContactsGroup(const char & firstLetterOfName, CTML::Node * & htmlPanelForContactsGroup, 
        CTML::Node * & htmlPanelHeadingForInitialLetter, CTML::Node * & htmlPanelBodyForRowsOfContacts, 
        CTML::Node * & htmlRowOfContacts);
        void HtmlFinalizePanelForContactsGroup(CTML::Node& htmlContainerForAllContacts, CTML::Node* & htmlPanelForContactsGroup, 
        CTML::Node* & htmlPanelHeadingForInitialLetter, CTML::Node* & htmlPanelBodyForRowsOfContacts, 
        CTML::Node* & htmlRowOfContacts);
        CTML::Node HtmlGetContactNode(const std::vector<Contact>::iterator & contactIterator,
        const std::string & directoryPathForSmsPerContactDocuments, const std::string & fileExtensionHtml);
        std::string HtmlGetTelephoneNumberString(TelephoneNumber phoneNumber);
        std::string HtmlGetSmsTypeString(const SmsType & type);
        CTML::Node GetSmsNode(const std::vector<Contact>::iterator & contactIterator,
        const std::string & directoryPathForSmsPerContactDocuments, const std::string & fileExtensionHtml);
};

#endif
