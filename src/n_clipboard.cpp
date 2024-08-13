// File: n_utils.cpp
#include "n_clipboard.h"
// Include required headers
#include <Carbon/Carbon.h>

bool n_clipboard::copy_to_clipboard(const char *buffer)
{
    OSStatus status;
    PasteboardRef pasteboard;
    CFDataRef textData;

    // Create a pasteboard reference
    status = PasteboardCreate(kPasteboardClipboard, &pasteboard);
    if (status != noErr) return false;

    // Clear the pasteboard
    status = PasteboardClear(pasteboard);
    if (status != noErr) {
        CFRelease(pasteboard);
        return false;
    }

    // Create a CFData object from the input string
    textData = CFDataCreate(nullptr, 
                            reinterpret_cast<const UInt8*>(buffer), 
                            strlen(buffer));
    if (textData == nullptr) {
        CFRelease(pasteboard);
        return false;
    }

    // Add the text data to the pasteboard
    status = PasteboardPutItemFlavor(pasteboard, 
                                     (PasteboardItemID)1, 
                                     CFSTR("public.utf8-plain-text"), 
                                     textData, 
                                     0);

    // Clean up
    CFRelease(textData);
    CFRelease(pasteboard);

    return (status == noErr);
}
