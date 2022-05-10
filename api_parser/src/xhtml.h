#pragma once
#include <tidy.h>
#include <buffio.h>
#include <string>


// https://shestero.livejournal.com/180590.html
// Convert HTML to XHTML and clean up using libTidy
std::string CleanHTML(const char *html)
{
    // Initialize a Tidy document
    TidyDoc tidyDoc = tidyCreate();
    TidyBuffer tidyOutputBuffer = {0};

    // Configure Tidy
    // The flags tell Tidy to output XML and disable showing warnings
    bool configSuccess = tidyOptSetBool(tidyDoc, TidyXmlOut, yes)
        && tidyOptSetBool(tidyDoc, TidyQuiet, yes)
        && tidyOptSetBool(tidyDoc, TidyNumEntities, yes)
        && tidyOptSetBool(tidyDoc, TidyShowWarnings, no)
        && tidyOptSetBool(tidyDoc, TidyUseCustomTags, yes)
        && tidyOptSetBool(tidyDoc, TidyForceOutput, yes)
        ;//&& tidyOptSetValue(tidyDoc,TidyCharEncoding, "utf8");
    int tidyResponseCode = -1;

    // Parse input
    if (configSuccess)
        tidyResponseCode = tidyParseString(tidyDoc, html);

    // Process HTML
    if (tidyResponseCode >= 0)
        tidyResponseCode = tidyCleanAndRepair(tidyDoc);

    // Output the HTML to our buffer
    if (tidyResponseCode >= 0)
        tidyResponseCode = tidySaveBuffer(tidyDoc, &tidyOutputBuffer);

    // Any errors from Tidy?
    if (tidyResponseCode < 0) // Tidy encountered an error while parsing an HTML
        throw tidyResponseCode;

    // Grab the result from the buffer and then free Tidy's memory
    std::string tidyResult = (char*)tidyOutputBuffer.bp;
    tidyBufFree(&tidyOutputBuffer);
    tidyRelease(tidyDoc);

    return tidyResult;
}

//	Bool ok;
//	TidyDoc tdoc = tidyCreate();                     // Initialize "document"
//	std::cout << "Tidying:\t%s\n" << input;
//	ok = tidyOptSetBool( tdoc, TidyXhtmlOut, yes );  // Convert to XHTML
//	if (!ok) { return -1;}
