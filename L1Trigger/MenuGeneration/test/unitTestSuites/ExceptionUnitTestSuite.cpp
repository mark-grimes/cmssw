#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/config/SourcePrefix.h>

#include "l1menu/Exceptions.h"

/** @brief A cppunit TestFixture to test the exception classes error formatting.
 *
 * @author Mark Grimes (mark.grimes@bristol.ac.uk)
 * @date 29/Jan/2015
 */
class ExceptionUnitTestSuite : public CPPUNIT_NS::TestFixture
{
	CPPUNIT_TEST_SUITE(ExceptionUnitTestSuite);
	CPPUNIT_TEST(testTraceFormatting);
	CPPUNIT_TEST(testTypeConsistency);
	CPPUNIT_TEST_SUITE_END();

protected:
	void testTraceFormatting()
	{
		//
		// First check that only the message is printed if there is no
		// trace information at all.
		//
		std::string errorMessage="Oh dear, there was an error";
		{ // block to make exception temporary
			l1menu::Exception exception( errorMessage );
			CPPUNIT_ASSERT_EQUAL( errorMessage, std::string(exception.what()) );
		}

		//
		// Then check original error location is reported if supplied.
		//
		std::string file1="/file/one.cpp"; // arbitrary dummy data
		size_t line1=28;
		{ // block to make exception temporary
			l1menu::Exception exception( errorMessage, file1, line1 );
			std::string expectedMessage=errorMessage+"\n\t"+file1+":"+std::to_string(line1);
			CPPUNIT_ASSERT_EQUAL( expectedMessage, std::string(exception.what()) );
		}

		//
		// Check extra trace info is printed if supplied
		//
		std::string file2="/file/two.cpp"; // arbitrary dummy data
		size_t line2=94;
		{ // block to make exception temporary
			l1menu::Exception exception( errorMessage, file1, line1 );
			exception.addTraceEntry( file2, line2 );
			std::string expectedMessage=errorMessage+"\n\t"+file1+":"+std::to_string(line1)+"\n\t"+file2+":"+std::to_string(line2);
			CPPUNIT_ASSERT_EQUAL( expectedMessage, std::string(exception.what()) );
		}

		//
		// Try the same again with more info
		//
		std::string file3="/file/three.cpp"; // arbitrary dummy data
		size_t line3=123;
		{ // block to make exception temporary
			l1menu::Exception exception( errorMessage, file1, line1 );
			exception.addTraceEntry( file2, line2 );
			exception.addTraceEntry( file3, line3 );
			std::string expectedMessage=errorMessage+"\n\t"+file1+":"+std::to_string(line1)+"\n\t"+file2+":"+std::to_string(line2)+"\n\t"+file3+":"+std::to_string(line3);
			CPPUNIT_ASSERT_EQUAL( expectedMessage, std::string(exception.what()) );
		}
		//
		// Check that extra trace info doesn't look like the original location
		// if the original location is not supplied.
		//
		{ // block to make exception temporary
			l1menu::Exception exception( errorMessage );
			exception.addTraceEntry( file2, line2 );
			std::string expectedMessage=errorMessage+"\n\tOriginal error location unknown\n\t"+file2+":"+std::to_string(line2);
			CPPUNIT_ASSERT_EQUAL( expectedMessage, std::string(exception.what()) );
		}
	}

	void testTypeConsistency()
	{
		//
		// I'm pretty sure using just "throw" to rethrow an exception keeps the original
		// type. This is just to convince myself.
		//

		std::string errorMessage="Oh dear, there was an error.";
		std::string file1="/file/one.cpp"; // arbitrary dummy data
		size_t line1=28;
		std::string file2="/file/two.cpp"; // arbitrary dummy data
		size_t line2=94;

		//
		// Throw a subclass; catch the baseclass, add info and rethrow. Make
		// sure I can still catch the original type (hasn't changed to the
		// baseclass) and that the added info is still there.
		//
		try
		{
			try
			{
				// Throw a subclass
				throw l1menu::InvalidArgumentException( errorMessage, file1, line1 );
			}
			catch( l1menu::Exception& error ) // catch by baseclass
			{
				error.addTraceEntry( file2, line2 );
				throw;
			}
		}
		catch( l1menu::InvalidArgumentException& error )
		{
			std::string expectedMessage=errorMessage+"\n\t"+file1+":"+std::to_string(line1)+"\n\t"+file2+":"+std::to_string(line2);
			CPPUNIT_ASSERT_EQUAL( expectedMessage, std::string(error.what()) );
		}
		catch(...)
		{
			CPPUNIT_FAIL( "Exception was not caught by its original type" );
		}
	}
};

CPPUNIT_TEST_SUITE_REGISTRATION(ExceptionUnitTestSuite);
