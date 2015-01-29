#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/config/SourcePrefix.h>

#include "../../src/menufileformats/XMLMenuFileReader.h"

/** @brief A cppunit TestFixture to test input and output of XML menu files.
 *
 * Note that this is for the custom XML format used by this package. The XML format
 * used by the L1 during operations will use a different file reader (once I've written
 * it).
 *
 * @author Mark Grimes (mark.grimes@bristol.ac.uk)
 * @date 29/Jan/2015
 */
class XMLMenuFileUnitTestSuite : public CPPUNIT_NS::TestFixture
{
	CPPUNIT_TEST_SUITE(XMLMenuFileUnitTestSuite);
	CPPUNIT_TEST(testTraceFormatting);
	CPPUNIT_TEST_SUITE_END();

protected:
	void testTraceFormatting()
	{
	}

};

CPPUNIT_TEST_SUITE_REGISTRATION(XMLMenuFileUnitTestSuite);
