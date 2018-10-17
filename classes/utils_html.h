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
        void HtmlWriteDocumentHead(CTML::Document & htmlDocument, 
        const std::string & characterCodification, const std::string & viewport, 
        const std::string & author, const std::vector<std::string> & styleSheetsPaths, 
        const std::string & title);
        void HtmlWriteHeaderInDocumentBody(CTML::Document & htmlDocument, const std::string & headerTitle, 
        const std::vector<std::pair<std::string,std::string>> & listOfNavigationBarLinksNamesAndUrls, 
        const unsigned int & indexOfSelectedNavigationBarLink);
        void HtmlWriteSmsReportResultInDocumentBody(CTML::Document & htmlDocument, 
        const std::string & headerTitle, std::vector<Sms> listOfSms);
        void HtmlWriteContactsReportResultInDocumentBody(CTML::Document & htmlDocument, 
        const std::string & headerTitle, std::vector<Contact> listOfContacts, 
        const std::string & directoryPathForSmsPerContactDocuments, const std::string & fileExtensionHtml);
        void HtmlWriteScriptsInDocumentBody(CTML::Document & htmlDocument, 
        const std::vector<std::string> & listOfHtmlScriptsPaths);
    private:
        std::string HtmlGetNumberOfObjectsMessage(const unsigned int & numberOfObjects, 
        const bool & isContactsReportResult);
        std::pair<CTML::Node,CTML::Node> HtmGetContactsNavigationBarNodeAndContactsListNode(
        std::vector<Contact> listOfContacts, const std::string & directoryPathForSmsPerContactDocuments, 
        const std::string & fileExtensionHtml);
        void InitializeAndAppendNodes(char & firstLetterOfName, const std::string & contactName, 
        CTML::Node & htmlNavigation, CTML::Node & htmlContainerForAllContacts, 
        CTML::Node * htmlRowOfContacts);
        CTML::Node HtmlGetContactNode(const std::vector<Contact>::iterator & contactIterator,
        const std::string & directoryPathForSmsPerContactDocuments, const std::string & fileExtensionHtml);
        std::string HtmlGetTelephoneNumberString(TelephoneNumber phoneNumber);
        std::string HtmlGetSmsTypeString(const SmsType & type);
        CTML::Node GetSmsNode(const std::vector<Contact>::iterator & contactIterator,
        const std::string & directoryPathForSmsPerContactDocuments, const std::string & fileExtensionHtml);
};

#endif
