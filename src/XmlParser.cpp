#include "XmlParser.h"
#include <iostream>     // USES cerr
#include <xercesc/util/PlatformUtils.hpp>       // USES Initialize()
#include <stdexcept>        // USES std::exception

namespace xml_parser {    

XmlParser::XmlParser(const char* configFile) :
    mFileName(configFile),
    mParser(nullptr) {
}

XmlParser::~XmlParser() {
    XMLPlatformUtils::Terminate();
}

bool XmlParser::init() {
    bool ret = true;
    try {
        XMLPlatformUtils::Initialize();
        mParser = new SAXParser();
        
        mParser->setDoSchema(true);
        mParser->setDoNamespaces(true);
        mParser->setValidationScheme(SAXParser::Val_Always);
        mParser->setValidationConstraintFatal(true);
        mParser->setExternalNoNamespaceSchemaLocation("/home/yonatan10/development/xml_parser/xml_files/config.xsd");
        if (mParser->loadGrammar("/home/yonatan10/development/xml_parser/xml_files/config.xsd", Grammar::SchemaGrammarType) == NULL) {
            ret = false;
            return ret;
        }
        mParser->setDocumentHandler(this);
        mParser->setErrorHandler(this);
        
    }
    catch (const XMLException& toCatch) {
        char* message = XMLString::transcode(toCatch.getMessage());
        std::cerr << "Exception message is: \n"
            << message << "\n";
        XMLString::release(&message);
        ret = false;
    }
    return ret;
}

bool XmlParser::parseFile() {
    bool ret = true;
    try {
        std::cout << "attempting to parse: " << mFileName << "\n";
        mParser->parse(mFileName);
    }
    catch (const XMLException& toCatch) {
        char* message = XMLString::transcode(toCatch.getMessage());
        std::cerr << "Exception message is: \n"
            << message << "\n";
        XMLString::release(&message);
        ret = false;
    }
    catch (const SAXParseException& toCatch) {
        char* message = XMLString::transcode(toCatch.getMessage());
        std::cerr << "Exception message is: \n"
            << message << "\n";
        XMLString::release(&message);
        ret = false;
    }
    catch (...) {
        std::cerr << "Unexpected Exception \n" ;
        ret = false;
    }
    return ret;
}

/**************************Protected Methods **********************************/

void XmlParser::startDocument() {
    std::cout << "I entered document" << std::endl;
}

void XmlParser::endDocument() {
    std::cout << "I exited document" << std::endl;
}

void XmlParser::startElement(const XMLCh* const name, AttributeList&   attributes) {
    char* message = XMLString::transcode(name);
    std::cout << "I saw element: "<< message << std::endl;
    
    size_t attributeListSize = attributes.getLength();
    for (size_t i = 0; i < attributeListSize; ++i) {
        char *attributeName = XMLString::transcode(attributes.getName(i));
        char *attributeValue = XMLString::transcode(attributes.getValue(attributeName));
        std::cout << "Attribute " << attributeName << " = " << attributeValue << "\n";
        XMLString::release(&attributeValue);
        XMLString::release(&attributeName);
    }
    
    XMLString::release(&message);
}

void XmlParser::endElement(const XMLCh* const name) {
    char* message = XMLString::transcode(name);
    std::cout << "I exited element: "<< message << std::endl;
    XMLString::release(&message);
}

void XmlParser::fatalError(const SAXParseException& exc) {
    char *message = XMLString::transcode(exc.getMessage());
    std::cout << "Fatal Error: " << message
         << " at line: " << exc.getLineNumber() << " column: " << exc.getColumnNumber() << std::endl;
    XMLString::release(&message);
}

void XmlParser::error(const SAXParseException& exc) {
    char *message = XMLString::transcode(exc.getMessage());
    std::cout << "Error: " << message
         << " at line: " << exc.getLineNumber() << " column: " << exc.getColumnNumber() << std::endl;
    XMLString::release(&message);
}

void XmlParser::warning(const SAXParseException& exc) {
    char *message = XMLString::transcode(exc.getMessage());
    std::cout << "Warning: " << message
         << " at line: " << exc.getLineNumber() << " column: " << exc.getColumnNumber() << std::endl;
    XMLString::release(&message);
}

} // namespace xml_parser