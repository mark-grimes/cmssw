#include <cppunit/extensions/HelperMacros.h>


/** @brief A cppunit TestFixture to test the string manipulation functions in the "tools" directory.
 *
 * @author Mark Grimes (mark.grimes@bristol.ac.uk)
 * @date 04/Aug/2013
 */
class TriggerPrimitivesUnitTestSuite : public CPPUNIT_NS::TestFixture
{
	CPPUNIT_TEST_SUITE(TriggerPrimitivesUnitTestSuite);
	CPPUNIT_TEST(addEmptyCaloTowersTest);
	CPPUNIT_TEST(addCaloTowersTest);
	CPPUNIT_TEST_SUITE_END();

protected:

public:
	void setUp();

protected:
	void addEmptyCaloTowersTest();
	void addCaloTowersTest();
};





#include <cppunit/config/SourcePrefix.h>
#include "l1menu/TriggerPrimitives.h"
#include <DataFormats/L1TCalorimeter/interface/CaloTower.h>

//
// Use the unnamed namespace for things only used in this file
//
namespace
{
	//
	// The CppUnit assertions require equality operators and stream output operators
	// to work with user defined types. These are them.
	//
	bool operator==( const l1t::CaloTower& tower1, const l1t::CaloTower& tower2 )
	{
		return ( tower1.etEm()==tower2.etEm() )
			&& ( tower1.etHad()==tower2.etHad() )
			&& ( tower1.hwEtEm()==tower2.hwEtEm() )
			&& ( tower1.hwEtHad()==tower2.hwEtHad() )
			&& ( tower1.hwEtRatio()==tower2.hwEtRatio() ) // end of CaloTower qualities
			&& ( tower1.hwPt()==tower2.hwPt() )
			&& ( tower1.hwEta()==tower2.hwEta() )
			&& ( tower1.hwPhi()==tower2.hwPhi() )
			&& ( tower1.hwQual()==tower2.hwQual() )
			&& ( tower1.hwIso()==tower2.hwIso() ) // end of L1Candidate qualities
			&& ( tower1.pt()==tower2.pt() ); // as far as I can tell this is the only thing from higher base classes used
	}
	std::ostream& operator<<( std::ostream& stream, const l1t::CaloTower& tower )
	{
		// Don't know what to put. Just print a python style object type and address
		stream << "[l1t::CaloTower object at 0x" << std::hex << reinterpret_cast<long>(&tower) << "]";
		return stream;
	}
} // end of the unnamed namespace


CPPUNIT_TEST_SUITE_REGISTRATION(TriggerPrimitivesUnitTestSuite);

void TriggerPrimitivesUnitTestSuite::setUp()
{
	// No operation
}

void TriggerPrimitivesUnitTestSuite::addEmptyCaloTowersTest()
{
	// Make a few small checks on the empty event
	l1menu::TriggerPrimitives triggerPrimitives;
	CPPUNIT_ASSERT( !triggerPrimitives.hasCaloTowers() );
	CPPUNIT_ASSERT_EQUAL( triggerPrimitives.caloTowersSize(), static_cast<size_t>(0) );

	// Try adding a collection with no elements
	std::vector<l1t::CaloTower> testTowers;
	CPPUNIT_ASSERT_NO_THROW( triggerPrimitives.setTowerCollection( testTowers.begin(), testTowers.end() ) );

	CPPUNIT_ASSERT( triggerPrimitives.hasCaloTowers() ); // Should now report that it has a collection
	CPPUNIT_ASSERT_EQUAL( triggerPrimitives.caloTowersSize(), static_cast<size_t>(0) );
}

void TriggerPrimitivesUnitTestSuite::addCaloTowersTest()
{
	// First create a series of CaloTowers to test with using randome data
	std::vector<l1t::CaloTower> testTowers;
	for( size_t index=0; index<10; ++index )
	{
		testTowers.emplace_back( reco::Candidate::LorentzVector(), std::rand()*100, std::rand()*100, std::rand()*100,
				std::rand()*100, std::rand()*100, std::rand()*100, std::rand()*100, std::rand()*100, std::rand()*100 );
	}

	// Make a few small checks on the empty event
	l1menu::TriggerPrimitives triggerPrimitives;
	CPPUNIT_ASSERT( !triggerPrimitives.hasCaloTowers() );
	CPPUNIT_ASSERT_EQUAL( triggerPrimitives.caloTowersSize(), static_cast<size_t>(0) );

	// Add these towers to the event
	CPPUNIT_ASSERT_NO_THROW( triggerPrimitives.setTowerCollection( testTowers.begin(), testTowers.end() ) );
	CPPUNIT_ASSERT( triggerPrimitives.hasCaloTowers() ); // Should now report that it has a collection
	CPPUNIT_ASSERT_EQUAL( triggerPrimitives.caloTowersSize(), testTowers.size() );

	for( size_t index=0; index<triggerPrimitives.caloTowersSize() && index<testTowers.size(); ++index )
	{
		// Make sure all of the objects match what was put in.
		CPPUNIT_ASSERT_EQUAL( triggerPrimitives.caloTowerAt(index), testTowers[index] );

		// Check that the pointer points to the same object. Currently, l1menu::TriggerPrimitives references
		// the objects. This might change to copying them in the future, in which case this check will have
		// to be removed. This makes the test above redundant, but keep it anyway because this could be removed
		// soon.
		CPPUNIT_ASSERT_EQUAL( &triggerPrimitives.caloTowerAt(index), const_cast<const l1t::CaloTower*>(&testTowers[index]) );
	}

}


