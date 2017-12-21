#include "CTML.h"

using namespace CTML;

int main()
{
    Document htmlDocument;
    
    htmlDocument.AddNodeToHead(Node("title","Telephone Contacts"));
    htmlDocument.AddNodeToHead(Node("meta").SetAttribute("name","author").SetAttribute("content","Alejandro Mesa"));
    htmlDocument.AddNodeToHead(Node("link").SetAttribute("href","../Bootstrap/bootstrap-3.3.7-dist/css/bootstrap.min.css").SetAttribute("rel","stylesheet"));
    htmlDocument.AddNodeToHead(Node("link").SetAttribute("href","../Bootstrap/bootstrap-3.3.7-dist/css/bootstrap-theme.min.css").SetAttribute("rel","stylesheet"));
    
    //htmlDocument.AddNodeToBody(Node("a.link").SetContent("Anchor").SetAttribute("href", "http://www.example.com"));
    
    Node header("div.bs-docs-header");
    header.SetAttribute("tabindex","-1").AppendChild(Node("h1","Telephone Contacts"));
    header.AppendChild(Node("p.lead","X contacts"));
    htmlDocument.AddNodeToBody(header);
    
    return htmlDocument.WriteToFile("index.html", Readability::MULTILINE);
}

