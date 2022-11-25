#ifndef XMLPARSER_H_
#define XMLPARSER_H_

#include <xercesc/sax/HandlerBase.hpp>      // USES HandlerBase
#include <xercesc/parsers/SAXParser.hpp>    // USES SAXParser

using namespace xercesc;

namespace xml_parser {

class XmlParser : public HandlerBase {
public:
    explicit XmlParser(const char *configFile);
    virtual ~XmlParser();
    
    bool init();
    bool parseFile();

protected:
    virtual void startDocument() override;
    virtual void endDocument() override;
    virtual void startElement(const XMLCh* const name, AttributeList&   attributes) override;
    virtual void endElement(const XMLCh* const name) override;
    virtual void fatalError(const SAXParseException& exc) override;
    virtual void error(const SAXParseException& exc) override;
    virtual void warning(const SAXParseException& exc) override;
    
    const char* mFileName;
    SAXParser* mParser;
};

} // namespace xml_parser

#endif // XMLPARSER_H_