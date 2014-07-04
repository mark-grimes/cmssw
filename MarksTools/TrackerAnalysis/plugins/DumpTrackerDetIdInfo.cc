#include <FWCore/Framework/interface/Frameworkfwd.h>
#include <FWCore/Framework/interface/EDAnalyzer.h>
#include <FWCore/Framework/interface/MakerMacros.h>
#include <FWCore/Framework/interface/ESHandle.h>
#include <FWCore/Framework/interface/EventSetup.h>
#include <DataFormats/TrackerCommon/interface/TrackerTopology.h>
#include <DataFormats/SiPixelDetId/interface/PixelSubdetector.h>
#include <Geometry/Records/interface/IdealGeometryRecord.h>
#include <Geometry/TrackerGeometryBuilder/interface/TrackerGeometry.h>
#include "Geometry/Records/interface/TrackerDigiGeometryRecord.h"
#include "Geometry/CommonDetUnit/interface/GeomDetUnit.h"

#include <iostream>
#include <limits>

namespace markstools
{
	class DumpTrackerDetIdInfo : public edm::EDAnalyzer
	{
	public:
		DumpTrackerDetIdInfo( const edm::ParameterSet& config );
		virtual void analyze( edm::Event const& event, edm::EventSetup const& setup );
	private:
		bool alreadyRun_;
	};

	DEFINE_FWK_MODULE(DumpTrackerDetIdInfo);

} // end of namespace markstools



markstools::DumpTrackerDetIdInfo::DumpTrackerDetIdInfo( const edm::ParameterSet& config )
	: alreadyRun_(false)
{
}

//struct PixelEndcapValues {
//  unsigned int sideStartBit_;
//  unsigned int diskStartBit_;
//  unsigned int bladeStartBit_;
//  unsigned int panelStartBit_;
//  unsigned int moduleStartBit_;
//  unsigned int sideMask_;
//  unsigned int diskMask_;
//  unsigned int bladeMask_;
//  unsigned int panelMask_;
//  unsigned int moduleMask_;
//};

void markstools::DumpTrackerDetIdInfo::analyze( edm::Event const& event, edm::EventSetup const& setup )
{
	if( alreadyRun_ ) return;
	alreadyRun_=true;

	edm::ESHandle<TrackerGeometry> hTrackerGeometry;
	setup.get<TrackerDigiGeometryRecord>().get( hTrackerGeometry );
	std::cout << " There are " << hTrackerGeometry->dets().size() << " detectors" << std::endl;

	edm::ESHandle<TrackerTopology> hTopology;
	setup.get<IdealGeometryRecord>().get(hTopology);

	for( const auto& pDetUnit : hTrackerGeometry->dets() )
	{
		//std::cout << "DetId " << pDetUnit->geographicalId().rawId() << " position=" << pDetUnit->position() << " rotation=" << pDetUnit->rotation() << " cock=" << pDetUnit->rotation().x() << hTopology->print(pDetUnit->geographicalId()) << std::endl;
		std::cout << pDetUnit->position().x() << " " << pDetUnit->position().y() << " " << pDetUnit->position().z()
				<< " " << pDetUnit->rotation().xx() << " " << pDetUnit->rotation().xy() << " " << pDetUnit->rotation().xz()
				<< " " << pDetUnit->rotation().yx() << " " << pDetUnit->rotation().yy() << " " << pDetUnit->rotation().yz()
				<< " " << pDetUnit->rotation().zx() << " " << pDetUnit->rotation().zy() << " " << pDetUnit->rotation().zz()
				<< " " << pDetUnit->geographicalId().rawId()
				<< " " << hTopology->print(pDetUnit->geographicalId()) << std::endl;
	}

//	const TrackerTopology* const pTopology = tTopoHandle.product();
//
//	for( uint32_t dummyDetId=DetId( DetId::Tracker, PixelSubdetector::PixelEndcap ); dummyDetId<=std::numeric_limits<uint32_t>::max(); ++dummyDetId )
//	{
//		DetId detId( dummyDetId );
//		if( detId.det()!=DetId::Tracker || detId.subdetId()!=PixelSubdetector::PixelEndcap ) break;
//
//		std::cout << dummyDetId << " " << pTopology->layer(dummyDetId) << " " << pTopology->module(dummyDetId) << std::endl;
//	}
}
