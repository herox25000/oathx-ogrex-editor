#include "OgrePlatform.h"
#if OGRE_PLATFORM == OGRE_PLATFORM_SYMBIAN
#include <coecntrl.h>
#endif

#include "OgreAppBrowser.h"

#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
#define WIN32_LEAN_AND_MEAN
#include "windows.h"
#include "OgreString.h"
#elif OGRE_PLATFORM == OGRE_PLATFORM_APPLE
#include "SampleBrowser_OSX.h"
#elif OGRE_PLATFORM == OGRE_PLATFORM_APPLE_IOS
#include "SampleBrowser_iOS.h"
#elif OGRE_PLATFORM == OGRE_PLATFORM_NACL
#include "SampleBrowser_NaCl.h"
#endif

#if OGRE_PLATFORM != OGRE_PLATFORM_SYMBIAN  && OGRE_PLATFORM != OGRE_PLATFORM_NACL

#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
INT WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR cmdLine, INT)
#else
int main(int argc, char *argv[])
#endif
{
#if OGRE_PLATFORM == OGRE_PLATFORM_APPLE_IOS
	NSAutoreleasePool * pool = [[NSAutoreleasePool alloc] init];
	int retVal = UIApplicationMain(argc, argv, @"UIApplication", @"AppDelegate");
	[pool release];
	return retVal;
#elif (OGRE_PLATFORM == OGRE_PLATFORM_APPLE) && __LP64__
	NSAutoreleasePool * pool = [[NSAutoreleasePool alloc] init];
    
    mAppDelegate = [[AppDelegate alloc] init];
    [[NSApplication sharedApplication] setDelegate:mAppDelegate];
	int retVal = NSApplicationMain(argc, (const char **) argv);

	[pool release];

	return retVal;
#else

	try
	{
        bool nograb = false;
#if OGRE_PLATFORM != OGRE_PLATFORM_WIN32
        if (argc >= 2 && Ogre::String(argv[1]) == "nograb")
            nograb = true;
#else
        // somewhat hacky, but much simpler than other solutions
        if (Ogre::String(cmdLine).find("nograb") != Ogre::String::npos)
            nograb = true;
#endif
		Ogre::AppBrowser sb (nograb);
		sb.go();
	}
	catch (Ogre::Exception& e)
	{
#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
		MessageBoxA(NULL, e.getFullDescription().c_str(), "An exception has occurred!", MB_ICONERROR | MB_TASKMODAL);
#else
		std::cerr << "An exception has occurred: " << e.getFullDescription().c_str() << std::endl;
#endif
	}

#endif
	return 0;
}

#endif // OGRE_PLATFORM != OGRE_PLATFORM_SYMBIAN    
