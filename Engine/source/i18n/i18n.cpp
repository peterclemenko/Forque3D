//-----------------------------------------------------------------------------
// Copyright (c) 2012 GarageGames, LLC
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to
// deal in the Software without restriction, including without limitation the
// rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
// sell copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
// FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
// IN THE SOFTWARE.
//-----------------------------------------------------------------------------

#include "platform/platform.h"
#include "core/stream/stream.h"
#include "core/stream/fileStream.h"
#include "console/console.h"

#include "i18n/i18n.h"
#include "i18n/lang.h"

//-----------------------------------------------------------------------------
// Globals
//-----------------------------------------------------------------------------

// [tom, 3/17/2005] Note: This is created in script
static LangTable* gCoreLangTable = NULL;

// [tom, 3/17/2005] Defined in CoreStringsDefaults.cc, which is generated by langc
//extern const UTF8 *gI18NDefaultStrings[];

// [tom, 5/2/2005] Note: Temporary kludge to keep this compilable while
// the core localization isn't finished.
static const UTF8* gI18NDefaultStrings[] =
{
    NULL
};

//-----------------------------------------------------------------------------

const UTF8* getCoreString( S32 id )
{
    if( gCoreLangTable )
        return gCoreLangTable->getString( id );
    else
        return gI18NDefaultStrings[id];
}

//-----------------------------------------------------------------------------

ConsoleFunction( getCoreLangTable, S32, 1, 1, "()"
                 "@brief Gets the primary LangTable used by the game\n\n"
                 "@return ID of the core LangTable\n"
                 "@ingroup Localization" )
{
    if( gCoreLangTable )
        return gCoreLangTable->getId();
    else
        return 0;
}

ConsoleFunction( setCoreLangTable, void, 2, 2, "(string LangTable)"
                 "@brief Sets the primary LangTable used by the game\n\n"
                 "@param LangTable ID of the core LangTable\n"
                 "@ingroup Localization" )
{
    LangTable* lt;
    
    if( Sim::findObject( argv[1], lt ) )
        gCoreLangTable = lt;
    else
        Con::errorf( "setCoreLangTable - Unable to find LanTable '%s'", argv[1] );
}

//-----------------------------------------------------------------------------
