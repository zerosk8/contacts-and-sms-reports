#include "utils_html.h"

void UtilsHtml::HtmlWriteDocumentHead(CTML::Document & htmlDocument, 
const std::string & characterCodification, const std::string & viewport, const std::string & author, 
const std::vector<std::string> & styleSheetsPaths, const std::string & title)
{
    htmlDocument.AddNodeToHead(CTML::Node("meta").SetAttribute("charset",characterCodification));
    htmlDocument.AddNodeToHead(CTML::Node("meta").SetAttribute("name","viewport").SetAttribute("content",viewport));
    htmlDocument.AddNodeToHead(CTML::Node("meta").SetAttribute("name","author").SetAttribute("content",author));
    
    for(std::vector<std::string>::const_iterator styleSheetIterator = styleSheetsPaths.begin();
    styleSheetIterator != styleSheetsPaths.end(); ++styleSheetIterator)
    {
        htmlDocument.AddNodeToHead(CTML::Node("link").SetAttribute("href",*styleSheetIterator)
        .SetAttribute("rel","stylesheet"));
    }
    htmlDocument.AddNodeToHead(CTML::Node("title",title));
}

void UtilsHtml::HtmlWriteHeaderInDocumentBody(CTML::Document & htmlDocument, const std::string & headerTitle)
{
    CTML::Node htmlBodyHeader("header.container-fluid.bg-primary.text-light");
    htmlBodyHeader.AppendChild(CTML::Node("div.d-flex.justify-content-center")
    .AppendChild(CTML::Node("h2.py-3","Phone Contacts Report")));
    CTML::Node htmlMainNavigationBarNav("ul.nav.nav-pills.py-3");
    htmlMainNavigationBarNav.SetAttribute("id","idMainNavigationBar");
    htmlMainNavigationBarNav.AppendChild(CTML::Node("li.nav-item.mx-5")
    .AppendChild(CTML::Node("a.nav-link.active","Contacts").SetAttribute("href","#")));
    htmlMainNavigationBarNav.AppendChild(CTML::Node("li.nav-item.mx-5")
    .AppendChild(CTML::Node("a.nav-link","Sms").SetAttribute("href","#")));
    htmlBodyHeader.AppendChild(CTML::Node("div.d-flex.justify-content-center").AppendChild(htmlMainNavigationBarNav));
    htmlDocument.AddNodeToBody(htmlBodyHeader);
}

void UtilsHtml::HtmlWriteSmsReportResultInDocumentBody(CTML::Document & htmlDocument, const std::string & headerTitle, 
std::vector<Sms> listOfSms)
{
    CTML::Node htmlContainerForAllSms("div.container"), htmlListForAllSms("div.list-group");
    htmlContainerForAllSms.AppendChild(CTML::Node("h1",headerTitle))
    .AppendChild(CTML::Node("p.lead",HtmlGetNumberOfObjectsMessage(listOfSms.size(),false)));
    for(std::vector<Sms>::iterator smsIterator = listOfSms.begin(); smsIterator != listOfSms.end(); ++smsIterator)
    {
        CTML::Node htmlSmsNode("li.list-group-item");
        if((*smsIterator).GetContactName().compare("Sandy") == 0)
        {
            htmlSmsNode.ToggleClass("list-group-item-danger");
        }
        CTML::Node htmlContactNameAndTelephoneNumber("div.d-flex.w-100.justify-content-between");
        htmlContactNameAndTelephoneNumber.AppendChild(CTML::Node("h3.mb-1",(*smsIterator).GetContactName()));
        htmlContactNameAndTelephoneNumber.AppendChild(CTML::Node("p",HtmlGetTelephoneNumberString((*smsIterator)
        .GetTelephoneNumber())));
        
        htmlSmsNode.AppendChild(htmlContactNameAndTelephoneNumber);
        htmlSmsNode.AppendChild(CTML::Node("p.mb-1",(*smsIterator).GetText()));
        htmlSmsNode.AppendChild(CTML::Node("small.text-muted",
        (*smsIterator).GetDateAndTime() + " - " + HtmlGetSmsTypeString((*smsIterator).GetType())));
        
        htmlListForAllSms.AppendChild(htmlSmsNode);
    }
    htmlContainerForAllSms.AppendChild(htmlListForAllSms);
    htmlDocument.AddNodeToBody(htmlContainerForAllSms);
}

void UtilsHtml::HtmlWriteContactsReportResultInDocumentBody(CTML::Document & htmlDocument, const std::string & headerTitle, 
std::vector<Contact> listOfContacts, const unsigned char & numberOfContactsPerRow,
const std::string & directoryPathForSmsPerContactDocuments, const std::string & fileExtensionHtml)
{
    CTML::Node htmlContainerForContactsList("main.container");
    htmlContainerForContactsList.AppendChild(CTML::Node("h3.pt-3",headerTitle))
    .AppendChild(CTML::Node("p.lead",HtmlGetNumberOfObjectsMessage(listOfContacts.size(),true)));
    std::pair<CTML::Node,CTML::Node> pairOfNavigationBarAndContactsList = HtmGetContactsNavigationBarNodeAndContactsListNode(listOfContacts,numberOfContactsPerRow,
    directoryPathForSmsPerContactDocuments,fileExtensionHtml);
    htmlContainerForContactsList.AppendChild(pairOfNavigationBarAndContactsList.first);
    htmlContainerForContactsList.AppendChild(pairOfNavigationBarAndContactsList.second);
    htmlDocument.AddNodeToBody(htmlContainerForContactsList);
}

void UtilsHtml::HtmlWriteScriptsInDocumentBody(CTML::Document & htmlDocument, const std::vector<std::string> & listOfHtmlScriptsPaths)
{
    for(std::vector<std::string>::const_iterator htmlScriptPathIterator = listOfHtmlScriptsPaths.begin(); 
    htmlScriptPathIterator != listOfHtmlScriptsPaths.end(); ++htmlScriptPathIterator)
    {
        htmlDocument.AddNodeToBody(CTML::Node("script").SetAttribute("src",*htmlScriptPathIterator));
    }
}

/**************************************/

std::string UtilsHtml::HtmlGetNumberOfObjectsMessage(const unsigned int & numberOfObjects, const bool & isContactsReportResult)
{
    if(isContactsReportResult)
    {
        if(numberOfObjects > 0)
        {
             return std::to_string(numberOfObjects) + " contact(s)";
        }
        return "There are no contacts";
    }
    if(numberOfObjects > 0)
    {
         return std::to_string(numberOfObjects) + " message(s)";
    }
    return "There are no messages";
}

std::pair<CTML::Node,CTML::Node> UtilsHtml::HtmGetContactsNavigationBarNodeAndContactsListNode(std::vector<Contact> listOfContacts, const unsigned char & numberOfContactsPerRow,
const std::string & directoryPathForSmsPerContactDocuments, const std::string & fileExtensionHtml)
{
    CTML::Node htmlContainerForContactsList("div.container");
    if(listOfContacts.size() > 0)
    {
        unsigned int contactIndex = 0;
        char firstLetterOfName = listOfContacts[0].GetName()[0];
        CTML::Node htmlContainerForAllContacts("div.col"), * htmlPanelForContactsGroup = NULL;
        CTML::Node * htmlPanelHeadingForInitialLetter = NULL, * htmlPanelBodyForRowsOfContacts = NULL, * htmlRowOfContacts = NULL;
        CTML::Node htmlNavigation("nav.nav.bg-light sticky-top");
        HtmlInitializePanelForContactsGroup(firstLetterOfName,htmlPanelForContactsGroup,htmlPanelHeadingForInitialLetter,
        htmlPanelBodyForRowsOfContacts,htmlRowOfContacts);
        htmlNavigation.AppendChild(CTML::Node("a.nav-link",std::string(1,firstLetterOfName))
        .SetAttribute("href","#letter" + std::string(1,firstLetterOfName)));
        for(std::vector<Contact>::iterator contactIterator = listOfContacts.begin(); contactIterator != listOfContacts.end(); 
        ++contactIterator)
        {
            if(firstLetterOfName != (*contactIterator).GetName()[0])
            {
                HtmlFinalizePanelForContactsGroup(htmlContainerForAllContacts,htmlPanelForContactsGroup,
                htmlPanelHeadingForInitialLetter,htmlPanelBodyForRowsOfContacts,htmlRowOfContacts);
                contactIndex = 0;
                firstLetterOfName = (*contactIterator).GetName()[0];
                HtmlInitializePanelForContactsGroup(firstLetterOfName,htmlPanelForContactsGroup,htmlPanelHeadingForInitialLetter,
                htmlPanelBodyForRowsOfContacts,htmlRowOfContacts);
                htmlNavigation.AppendChild(CTML::Node("a.nav-link",std::string(1,firstLetterOfName))
                .SetAttribute("href","#letter" + std::string(1,firstLetterOfName)));
            }
            else if(contactIterator > listOfContacts.begin() && contactIndex % numberOfContactsPerRow == 0)
            {
                (*htmlPanelBodyForRowsOfContacts).AppendChild(*htmlRowOfContacts);
                htmlRowOfContacts = new CTML::Node("div.row");
                contactIndex = 0;
            }
            (*htmlRowOfContacts).AppendChild(HtmlGetContactNode(contactIterator,directoryPathForSmsPerContactDocuments,
            fileExtensionHtml));
            contactIndex++;
        }
        HtmlFinalizePanelForContactsGroup(htmlContainerForAllContacts,htmlPanelForContactsGroup,htmlPanelHeadingForInitialLetter,
        htmlPanelBodyForRowsOfContacts,htmlRowOfContacts);
        
        htmlContainerForContactsList.AppendChild(CTML::Node("div.row").AppendChild(htmlContainerForAllContacts));

        return std::pair<CTML::Node,CTML::Node>(htmlNavigation,htmlContainerForContactsList);
    }
    return std::pair<CTML::Node,CTML::Node>();
}

void UtilsHtml::HtmlInitializePanelForContactsGroup(const char & firstLetterOfName, CTML::Node * & htmlPanelForContactsGroup, 
CTML::Node * & htmlPanelHeadingForInitialLetter, CTML::Node * & htmlPanelBodyForRowsOfContacts, CTML::Node * & htmlRowOfContacts)
{
    htmlPanelForContactsGroup = new CTML::Node("div.card");
    htmlPanelHeadingForInitialLetter = new CTML::Node("div.card-header");
    (*htmlPanelHeadingForInitialLetter).AppendChild(CTML::Node("a",std::string(1,firstLetterOfName))
    .SetAttribute("id","letter" + std::string(1,firstLetterOfName)));
    htmlPanelBodyForRowsOfContacts = new CTML::Node("div.card-body");
    htmlRowOfContacts = new CTML::Node("div.row");
}

void UtilsHtml::HtmlFinalizePanelForContactsGroup(CTML::Node & htmlContainerForAllContacts, 
CTML::Node * & htmlPanelForContactsGroup, CTML::Node * & htmlPanelHeadingForInitialLetter, 
CTML::Node * & htmlPanelBodyForRowsOfContacts, CTML::Node * & htmlRowOfContacts)
{
    (*htmlPanelBodyForRowsOfContacts).AppendChild(*htmlRowOfContacts);
    (*htmlPanelForContactsGroup).AppendChild(*htmlPanelHeadingForInitialLetter);
    (*htmlPanelForContactsGroup).AppendChild(*htmlPanelBodyForRowsOfContacts);
    htmlContainerForAllContacts.AppendChild(*htmlPanelForContactsGroup);
}

CTML::Node UtilsHtml::HtmlGetContactNode(const std::vector<Contact>::iterator & contactIterator,
const std::string & directoryPathForSmsPerContactDocuments, const std::string & fileExtensionHtml)
{
    CTML::Node htmlContactNode("div.col");
    htmlContactNode.AppendChild(CTML::Node("h3",(*contactIterator).GetName()));
    std::vector<TelephoneNumber> listOfPhoneNumbers = (*contactIterator).GetTelephoneNumbers();
    for(std::vector<TelephoneNumber>::iterator phoneNumberIterator = listOfPhoneNumbers.begin(); 
    phoneNumberIterator != listOfPhoneNumbers.end(); ++phoneNumberIterator)
    {
        htmlContactNode.AppendChild(CTML::Node("p",HtmlGetTelephoneNumberString(*phoneNumberIterator)));
    }
    std::vector<std::string> listOfEmails = (*contactIterator).GetEmails();
    for(std::vector<std::string>::iterator emailIterator = listOfEmails.begin(); emailIterator != listOfEmails.end(); 
    ++emailIterator)
    {
        htmlContactNode.AppendChild(CTML::Node("p",(*emailIterator)));
    }
    htmlContactNode.AppendChild(GetSmsNode(contactIterator,directoryPathForSmsPerContactDocuments,fileExtensionHtml));
    return htmlContactNode;
}

std::string UtilsHtml::HtmlGetTelephoneNumberString(TelephoneNumber phoneNumber)
{
    return phoneNumber.ContainsCountryDialCode()?"(" + phoneNumber.GetCountryDialCode() + ") " + 
    phoneNumber.GetNumber():phoneNumber.GetNumber();
}

std::string UtilsHtml::HtmlGetSmsTypeString(const SmsType & type)
{
    switch(type)
    {
        case incoming:  return "Incoming message";
                        break;
        case outgoing:  return "Outgoing message";
                        break;
        default:        return "Unknowkn message addressing";
                        break;
    }
}

CTML::Node UtilsHtml::GetSmsNode(const std::vector<Contact>::iterator & contactIterator,
const std::string & directoryPathForSmsPerContactDocuments, const std::string & fileExtensionHtml)
{
    std::vector<Sms> listOfSms = (*contactIterator).GetListOfSms();
    if(!listOfSms.empty())
    {
        return CTML::Node("a","View " + std::to_string(listOfSms.size()) + " message(s)").SetAttribute("href",
        directoryPathForSmsPerContactDocuments + "/" + (*contactIterator).GetName() + fileExtensionHtml);
    }
    
    return CTML::Node("p","No messages");
}
