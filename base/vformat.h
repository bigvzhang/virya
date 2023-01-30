// ----------------------------------------------------------------------------
// format.hpp :  primary header
// ----------------------------------------------------------------------------
#pragma once

#include <vector>
#include <string>

#include <cctype>  // we'll use the non-locale  <cctype>'s std::isdigit(int)

// ****  Forward declarations ----------------------------------
#include "format/format_fwd.hpp"     // basic_format<Ch,Tr>, and other frontends
//#include <boost/format/internals_fwd.hpp>  // misc forward declarations for internal use

// ****  Auxiliary structs (stream_format_state<Ch,Tr> , and format_item<Ch,Tr> )
//#include <boost/format/internals.hpp>    

// ****  Format  class  interface --------------------------------
//#include <boost/format/format_class.hpp>

// **** Exceptions -----------------------------------------------
//#include <boost/format/exceptions.hpp>

// **** Implementation -------------------------------------------
//#include <boost/format/format_implementation.hpp>   // member functions
//#include <boost/format/group.hpp>                   // class for grouping arguments
//#include <boost/format/feed_args.hpp>               // argument-feeding functions
//#include <boost/format/parsing.hpp>                 // format-string parsing (member-)functions

// **** Implementation of the free functions ----------------------
//#include <boost/format/free_funcs.hpp>


// *** Undefine 'local' macros :
//#include <boost/format/detail/unset_macros.hpp>

