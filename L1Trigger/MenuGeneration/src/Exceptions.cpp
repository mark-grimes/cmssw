#include "l1menu/Exceptions.h"

//---------------------------------------------
//--------- Definitions for Exception ---------
//---------------------------------------------

l1menu::Exception::Exception( const std::string& message )
	: message_(message)
{
	// No information about the location of the error. Want to always have an
	// entry for the original error so add an empty string and 0 as the line number.
	addTraceEntry( "", 0 );
}

l1menu::Exception::Exception( const std::string& message, const std::string& filename, size_t lineNumber )
	: message_(message)
{
	addTraceEntry( filename, lineNumber );
}

l1menu::Exception::~Exception()
{
	// No operation
}

const char* l1menu::Exception::what() const noexcept
{
	return fullMessage_.c_str();
}

const std::string& l1menu::Exception::message() const noexcept
{
	return message_;
}

const std::string& l1menu::Exception::filename() const noexcept
{
	return stackTrace_[0].first;
}

size_t l1menu::Exception::lineNumber() const noexcept
{
	return stackTrace_[0].second;
}

void l1menu::Exception::addTraceEntry( const std::string& filename, size_t lineNumber )
{
	stackTrace_.push_back( std::make_pair(filename,lineNumber) );

	// Since "what()" is const, I'll formulate fullMessage_ here. I store the message
	// in a member rather than using a temporary because "what()" returns a char *.
	// Even though the compiler doesn't complain I'm pretty sure that could potentially
	// lead to a segfault.

	// I can't be bothered with logic to check the state of the message, I'll just
	// reformulate it each time.
	fullMessage_=message_;

	for( size_t index=0; index<stackTrace_.size(); ++index )
	{
		if( index==0 && stackTrace_[index].second==0 ) // If no information about the original position
		{
			// If there is no other info don't bother printing anything
			if( stackTrace_.size()!=1 ) fullMessage_+="\n\tOriginal error location unknown";
		}
		else fullMessage_+="\n\t"+stackTrace_[index].first+":"+std::to_string(stackTrace_[index].second);
	}
}

//-----------------------------------------------------------
//--------- Definitions for NotImplementedException ---------
//-----------------------------------------------------------
l1menu::NotImplementedException::NotImplementedException( const std::string& message )
	: l1menu::Exception(message)
{
	// No operation besides the initialiser list.
}

l1menu::NotImplementedException::NotImplementedException( const std::string& message, const std::string& filename, size_t lineNumber )
	: l1menu::Exception(message,filename,lineNumber)
{
	// No operation besides the initialiser list.
}

l1menu::NotImplementedException::~NotImplementedException()
{
	// No operation
}




//----------------------------------------------------------------
//--------- Definitions for IncorrectFileFormatException ---------
//----------------------------------------------------------------
l1menu::IncorrectFileFormatException::IncorrectFileFormatException( const std::string& message )
	: l1menu::Exception(message)
{
	// No operation besides the initialiser list.
}

l1menu::IncorrectFileFormatException::IncorrectFileFormatException( const std::string& message, const std::string& filename, size_t lineNumber )
	: l1menu::Exception(message,filename,lineNumber)
{
	// No operation besides the initialiser list.
}

l1menu::IncorrectFileFormatException::~IncorrectFileFormatException()
{
	// No operation
}




//----------------------------------------------------------------
//--------- Definitions for DataNotAvailableException ---------
//----------------------------------------------------------------
l1menu::DataNotAvailableException::DataNotAvailableException( const std::string& message )
	: l1menu::Exception(message)
{
	// No operation besides the initialiser list.
}

l1menu::DataNotAvailableException::DataNotAvailableException( const std::string& message, const std::string& filename, size_t lineNumber )
	: l1menu::Exception(message,filename,lineNumber)
{
	// No operation besides the initialiser list.
}

l1menu::DataNotAvailableException::~DataNotAvailableException()
{
	// No operation
}




//----------------------------------------------------------------
//--------- Definitions for InvalidArgumentException ---------
//----------------------------------------------------------------
l1menu::InvalidArgumentException::InvalidArgumentException( const std::string& message )
	: l1menu::Exception(message)
{
	// No operation besides the initialiser list.
}

l1menu::InvalidArgumentException::InvalidArgumentException( const std::string& message, const std::string& filename, size_t lineNumber )
	: l1menu::Exception(message,filename,lineNumber)
{
	// No operation besides the initialiser list.
}

l1menu::InvalidArgumentException::~InvalidArgumentException()
{
	// No operation
}
