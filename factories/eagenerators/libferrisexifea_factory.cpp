/******************************************************************************
*******************************************************************************
*******************************************************************************

    libferris
    Copyright (C) 2003 Ben Martin

    libferris is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    libferris is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with libferris.  If not, see <http://www.gnu.org/licenses/>.

    For more details see the COPYING file in the root directory of this
    distribution.

    $Id: libferrisexifea_factory.cpp,v 1.3 2010/09/24 21:31:27 ben Exp $

    *******************************************************************************
    *******************************************************************************
    ******************************************************************************/

#include <FerrisEAPlugin.hh>

using namespace std;

namespace Ferris
{
    static Factory::EndingList EL()
    {
        static Factory::EndingList r;
        static bool virgin = true;

        if( virgin )
        {
            virgin = false;
        
            r.push_back( make_pair( string("name"), string(".jpeg") ));
            r.push_back( make_pair( string("name"), string(".jpg") ));
            r.push_back( make_pair( string("name"), string(".tiff") ));
            r.push_back( make_pair( string("name"), string(".tif") ));
        }
    
        return r;
    }
    
    /**
     *
     * New method that allows the factory itself to be statically bound
     * to libferris but the plugin to be dynamically loaded. (1.1.10)+
     *
     */
    namespace 
    {
        static bool r = RegisterEAGeneratorModule(
            Factory::ComposeEndsWithMatcher( EL() ),
            AUTOTOOLS_CONFIG_LIBDIR + "/ferris/plugins/eagenerators/libferrisexifea.so",
            "exif",
            false, // dynamic
            true,  // hasState
            AttributeCreator::CREATE_PRI_MED );
    };
};
