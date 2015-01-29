#ifndef l1menu_Exceptions_h
#define l1menu_Exceptions_h

#include <exception>
#include <string>
#include <vector>


namespace l1menu
{
	/** @brief Base class for all exceptions directly thrown by the menu studies package.
	 *
	 * Note that library code used by this package can still throw different exceptions.
	 * @author Mark Grimes (from ideas by Brian Winer and Georgia Karapostoli)
	 * @date 28/Jan/2015
	 */
	class Exception : public std::exception
	{
	public:
		Exception( const std::string& message );
		Exception( const std::string& message, const std::string& filename, size_t lineNumber );
		virtual ~Exception();

		/** @brief Implementation of the standard library base class method.
		 *
		 * If no filename or line number were provided this is exactly the same as message().
		 * If they were provided then these are appended to the message. */
		virtual const char* what() const noexcept;

		/** @brief The error message. Same as what() if no location details were provided. */
		virtual const std::string& message() const noexcept;

		/** @brief The file where the original error occurred.
		 *
		 * If a filename wasn't specified by the throwing code this will be an empty string. */
		virtual const std::string& filename() const noexcept;

		/** @brief The line where the original error occurred.
		 *
		 * If the location wasn't specified by the throwing code this will be zero. */
		virtual size_t lineNumber() const noexcept;

		/** @brief Allow code to add information about the error trace.
		 *
		 * Allows code to add information about what led to the original error. Code would do
		 * something like
		 *
		 * @code
		 * try
		 * {
		 *     // ... code that throws original error here ...
		 * }
		 * catch( l1menu::Exception& error )
		 * {
		 *     error.addTraceEntry( __FILE__, __LINE__ );
		 *     throw;
		 * }
		 * @endcode
		 *
		 * Clearly the trace info there is for where the error is caught rather than thrown, but it
		 * should be enough information to hone in on where the error is.
		 */
		virtual void addTraceEntry( const std::string& filename, size_t lineNumber );
	protected:
		const std::string message_; ///< @brief Original error message.

		/** @brief Source filename and line number for points along the stack.
		 *
		 * Note that it's not a full stack trace, it only provides information explicitly added with
		 * addTraceEntry(). There will always be at least one entry for where the exception was
		 * originally thrown. This entry might be ("",0) however if no location information was provided
		 * in the constructor. */
		std::vector< std::pair<std::string,size_t> > stackTrace_;

		/** @brief The string returned by what(), i.e. message_ with any stack trace information added.
		 *
		 * Since what() returns a char* I'm pretty sure I can't use a temporary in there to formulate the
		 * message, so it's stored in this member. */
		std::string fullMessage_;
	};

	/** @brief @todo describe
	 *
	 * @author Mark Grimes (from ideas by Brian Winer and Georgia Karapostoli)
	 * @date 28/Jan/2015
	 */
	class NotImplementedException : public l1menu::Exception
	{
	public:
		NotImplementedException( const std::string& message );
		NotImplementedException( const std::string& message, const std::string& filename, size_t lineNumber );
		virtual ~NotImplementedException();
	};

	/** @brief @todo describe
	 *
	 * @author Mark Grimes (from ideas by Brian Winer and Georgia Karapostoli)
	 * @date 28/Jan/2015
	 */
	class IncorrectFileFormatException : public l1menu::Exception
	{
	public:
		IncorrectFileFormatException( const std::string& message );
		IncorrectFileFormatException( const std::string& message, const std::string& filename, size_t lineNumber );
		virtual ~IncorrectFileFormatException();
	};

	/** @brief @todo describe
	 *
	 * @author Mark Grimes (from ideas by Brian Winer and Georgia Karapostoli)
	 * @date 29/Jan/2015
	 */
	class DataNotAvailableException : public l1menu::Exception
	{
	public:
		DataNotAvailableException( const std::string& message );
		DataNotAvailableException( const std::string& message, const std::string& filename, size_t lineNumber );
		virtual ~DataNotAvailableException();
	};

	/** @brief @todo describe
	 *
	 * @author Mark Grimes (from ideas by Brian Winer and Georgia Karapostoli)
	 * @date 29/Jan/2015
	 */
	class InvalidArgumentException : public l1menu::Exception
	{
	public:
		InvalidArgumentException( const std::string& message );
		InvalidArgumentException( const std::string& message, const std::string& filename, size_t lineNumber );
		virtual ~InvalidArgumentException();
	};

} // end of namespace l1menu

#endif
