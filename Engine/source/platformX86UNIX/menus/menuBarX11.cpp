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

#include "platformX86UNIX/platformX86UNIX.h"
#include "platform/menus/menuBar.h"
#include "platform/menus/popupMenu.h"
#include "gui/core/guiCanvas.h"
#include "windowManager/platformWindowMgr.h"
#include "windowManager/x11/x11WindowMgr.h"
#include "core/util/safeDelete.h"


//-----------------------------------------------------------------------------
// MenuBar Methods
//-----------------------------------------------------------------------------

void MenuBar::createPlatformPopupMenuData()
{
    mData = NULL;
}

void MenuBar::deletePlatformPopupMenuData()
{
}

//-----------------------------------------------------------------------------

void MenuBar::updateMenuBar( PopupMenu* menu /* = NULL */ )
{
    //AssertFatal( 0, "Not Implemented" );
}

//-----------------------------------------------------------------------------

void MenuBar::attachToCanvas( GuiCanvas* owner, S32 pos )
{
    AssertFatal( 0, "Not Implemented" );
}

void MenuBar::removeFromCanvas()
{
    AssertFatal( 0, "Not Implemented" );
}
