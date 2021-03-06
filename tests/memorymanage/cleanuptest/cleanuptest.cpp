/******************************************************************************
*******************************************************************************
*******************************************************************************

    libferris
    Copyright (C) 2001 Ben Martin

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

    For more details see the COPYING file in the root directory of this
    distribution.

    $Id: cleanuptest.cpp,v 1.1 2006/12/07 07:03:31 ben Exp $

*******************************************************************************
*******************************************************************************
******************************************************************************/

#include "config.h"
#include <Ferris.hh>
#include <Ferris_private.hh>

#include "vmdebug.cpp"

using namespace Ferris;
using namespace std;

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

int main(int argc, char** argv )
{
    string path = "/tmp";
    
    if( argc >= 2 )
        path = argv[1];
    
    try
    {
        Resolve( "/" );
        ExistingContextsState st_rootOnly;
        
        {
            dumpall("Before Resolve()");

            fh_context c = Resolve( path );
            dumpcc("After  Resolve CC()");
            dumpall("After  Resolve ALL()");

            c->read();
            printentries(c);
            
            dumpall("After Resolve and Read()");

//             {
//                 fh_context childc = rootc->getSubContext("file1");
//                 fh_istream ss = childc->getIStream();

//                 dumpall("Have stream handle and childc (/tmp/file1) still");
//                 childc = 0;
//                 dumpall("Have stream handle still");
//             }
            
//             dumpall("Stream handle out of scope, rootc still in scope");
//             CacheManager* cc = getCacheManager();
//             cc->cleanUp();
//             dumpall("Stream handle out of scope, rootc still in scope (cleaned)");
            
//             {
//                 fh_context childc = rootc->getSubContext("file1");
//                 fh_attribute attr = childc->getAttribute( "name" );
//                 fh_istream ss = attr->getIStream();

//                 dumpall("Have stream handle, attr, and childc (/tmp/file1) still");
//                 childc = 0;
//                 attr = 0;
//                 dumpall("Have stream handle still");
//             }
            
         }

        fullyReclaim( "reclaiming all" );
        
        cerr << "_________getting rootc again" << endl;
        {
            fh_context c = Resolve( path );
            c->read();
            printentries(c);
//             fh_context childc = rootc->getSubContext("file1");
//             fh_istream ss = childc->getIStream();
//             cerr << StreamToString(ss) << endl;
            
            dumpall("After second resolve. All ");
            dumpcc("After second resolve. FreeList ");

            fullyReclaim( "reclaiming while holding" );
        }

        fullyReclaim( "reclaiming final" );
        st_rootOnly.equalsCurrent();
    }
    catch( exception& e )
    {
        ++errors;
        cerr << "ERROR:" << e.what() << endl;
    }
    
    dumpall("Exiting all");
    dumpcc("Exiting FreeList");
    
    if( !errors )
        cout << "FULL Success" << endl;
    return errors;
}
