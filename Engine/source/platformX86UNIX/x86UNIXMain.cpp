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
#include "platform/platformInput.h"
#include "console/console.h"
#include "gfx/gfxInit.h"
#include "gfx/gfxDevice.h"
#include "core/strings/unicode.h"
#include "platformX86UNIX/platformX86UNIX.h"
#include "platformX86UNIX/x86UNIXStdConsole.h"
#include "platformX86UNIX/x86UNIXState.h"

#ifndef DEDICATED
#include <SDL/SDL.h>
#include <SDL/SDL_syswm.h>
#include <SDL/SDL_version.h>
#endif

extern void InitWindowingSystem();

#ifndef DEDICATED

//------------------------------------------------------------------------------
bool InitSDL()
{
    if( SDL_Init( SDL_INIT_VIDEO ) != 0 )
        return false;
        
    atexit( SDL_Quit );
    
    SDL_SysWMinfo sysinfo;
    SDL_VERSION( &sysinfo.version );
    if( SDL_GetWMInfo( &sysinfo ) == 0 )
        return false;
        
    x86UNIXState->setDisplayPointer( sysinfo.info.x11.display );
    DisplayPtrManager::setDisplayLockFunction( sysinfo.info.x11.lock_func );
    DisplayPtrManager::setDisplayUnlockFunction( sysinfo.info.x11.unlock_func );
    
    DisplayPtrManager xdisplay;
    Display* display = xdisplay.getDisplayPointer();
    
    x86UNIXState->setScreenNumber(
        DefaultScreen( display ) );
    x86UNIXState->setScreenPointer(
        DefaultScreenOfDisplay( display ) );
        
    x86UNIXState->setDesktopSize(
        ( S32 ) DisplayWidth(
            display,
            x86UNIXState->getScreenNumber() ),
        ( S32 ) DisplayHeight(
            display,
            x86UNIXState->getScreenNumber() )
    );
    x86UNIXState->setDesktopBpp(
        ( S32 ) DefaultDepth(
            display,
            x86UNIXState->getScreenNumber() ) );
            
    // indicate that we want sys WM messages
    SDL_EventState( SDL_SYSWMEVENT, SDL_ENABLE );
    
    return true;
}
#endif

//------------------------------------------------------------------------------
void Platform::init()
{
    StdConsole::create();
    stdConsole->enable( true );
    
    Con::printf( "Initializing platform..." );
    
    // Set the platform variable for the scripts
    Con::setVariable( "$platform", "x86UNIX" );
#if defined(__linux__)
    Con::setVariable( "$platformUnixType", "Linux" );
#elif defined(__OpenBSD__)
    Con::setVariable( "$platformUnixType", "OpenBSD" );
#else
    Con::setVariable( "$platformUnixType", "Unknown" );
#endif
    
    StdConsole::create();
    
    Input::init();
    
    //installRedBookDevices();
    
#ifndef DEDICATED
    // if we're not dedicated do more initialization
    if( !x86UNIXState->isDedicated() )
    {
        InitWindowingSystem();
    }
#endif
    
    Con::printf( "Done" );
}

//------------------------------------------------------------------------------
void Platform::shutdown()
{
    //Cleanup();
    Input::destroy();
    
    GFXDevice::destroy();
    
    // Dushan - we should destroy console on shutdown
    StdConsole::destroy();
}

//------------------------------------------------------------------------------


extern "C"
{
    bool torque_engineinit( int argc, const char** argv );
    int  torque_enginetick();
    bool torque_engineshutdown();
    
    int torque_unixmain( int argc, const char** argv )
    {
        if( !torque_engineinit( argc, argv ) )
            return 1;
            
        while( torque_enginetick() )
        {
        
        }
        
        torque_engineshutdown();
        
        return 0;
        
    }
}

#ifndef TORQUE_SHARED

extern S32 TorqueMain( S32 argc, const char** argv );

S32 main( int argc, const char** argv )
{
    return TorqueMain( argc, argv );
}

#endif

