/*
--------------------------------------------------------------------------------
This source file is part of Hydrax editor.
Visit ---

Copyright (C) 2007 Xavier Verguín González <xavierverguin@hotmail.com>
                                           <xavyiy@gmail.com>

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software Foundation, Inc.,
59 Temple Place - Suite 330, Boston, MA  02111-1307, USA, or go to
http://www.gnu.org/copyleft/gpl.html.
--------------------------------------------------------------------------------
*/

#ifndef _Singleton_H_
#define _Singleton_H_

#include <iostream>

namespace HydraxEditor
{
	using namespace std;

	/** Use our Singleton class, I don't like very much Ogre's Singleton implementation
     */
    template<class T> class Singleton
    {
    protected:
        Singleton(){};

    public:
       static T * Instance;

       inline static T * getSingleton()
       {
           if (Instance == NULL)
		   {
               Instance = new T();
		   }

           return Instance;
       };
    };

    template<class T> T* Singleton <T>::Instance = NULL;
};

#endif