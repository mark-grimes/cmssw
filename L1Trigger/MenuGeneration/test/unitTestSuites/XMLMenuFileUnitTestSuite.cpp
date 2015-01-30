#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/config/SourcePrefix.h>

#include "../../src/menufileformats/XMLMenuFileReader.h"
#include <FWCore/ParameterSet/interface/FileInPath.h>
#include "l1menu/TriggerMenu.h"
#include "l1menu/Exceptions.h"

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
	CPPUNIT_TEST(testLoadingInvalidFile);
	CPPUNIT_TEST(testLoadingValidFile);
	CPPUNIT_TEST_SUITE_END();

protected:
	void testLoadingInvalidFile()
	{
		std::unique_ptr<l1menu::menufileformats::XMLMenuFileReader> pReader;

		edm::FileInPath filename1("L1Trigger/MenuGeneration/examples/L1Menu_Collisions2015_50ns_v0_L1T_Scales_20141121_Imp0_0x1031.xml");
		CPPUNIT_ASSERT_THROW( pReader.reset( new l1menu::menufileformats::XMLMenuFileReader(filename1.fullPath()) ), l1menu::IncorrectFileFormatException );

		edm::FileInPath filename2("L1Trigger/MenuGeneration/src/TriggerMenu.cpp");
		CPPUNIT_ASSERT_THROW( pReader.reset( new l1menu::menufileformats::XMLMenuFileReader(filename2.fullPath()) ), l1menu::IncorrectFileFormatException );

	}
	void testLoadingValidFile()
	{
		edm::FileInPath filename("L1Trigger/MenuGeneration/examples/L1Menu_std2012_v1p1.xml");
		std::unique_ptr<l1menu::menufileformats::XMLMenuFileReader> pReader;
		CPPUNIT_ASSERT_NO_THROW( pReader.reset( new l1menu::menufileformats::XMLMenuFileReader(filename.fullPath()) ) );

		auto result=pReader->getMenus();
		CPPUNIT_ASSERT_EQUAL( static_cast<size_t>(1), result.size() );
	}

};

CPPUNIT_TEST_SUITE_REGISTRATION(XMLMenuFileUnitTestSuite);
