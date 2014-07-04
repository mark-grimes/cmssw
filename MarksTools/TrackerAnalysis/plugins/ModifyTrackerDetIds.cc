#include <FWCore/Framework/interface/Frameworkfwd.h>
#include <FWCore/Framework/interface/EDProducer.h>
#include <FWCore/Framework/interface/MakerMacros.h>
#include <DataFormats/Common/interface/Handle.h>
#include <FWCore/Framework/interface/Event.h>

#include <iostream>
#include <limits>
#include <fstream>
#include <stdexcept>

#include "SimDataFormats/TrackingHit/interface/PSimHit.h"

namespace markstools
{
	class ModifyTrackerDetIds : public edm::EDProducer
	{
	public:
		ModifyTrackerDetIds( const edm::ParameterSet& config );
		virtual void produce( edm::Event& event, edm::EventSetup const& setup );
	private:
		std::map<uint32_t,uint32_t> detIdMap_;
		std::vector<edm::InputTag> inputCollectionNames_;
	};

	DEFINE_FWK_MODULE(ModifyTrackerDetIds);

} // end of namespace markstools


markstools::ModifyTrackerDetIds::ModifyTrackerDetIds( const edm::ParameterSet& config )
{
	std::string remapFilename=config.getParameter<std::string>( "mapFilename" );
	inputCollectionNames_=config.getParameter<std::vector<edm::InputTag> >( "inputCollections" );

	std::ifstream inputFile( remapFilename );
	if( !inputFile.is_open() ) throw std::runtime_error( "ModifyTrackerDetIds - unable to load the input file "+remapFilename );

	uint32_t oldDetId;
	uint32_t newDetId;
	while( inputFile.good() )
	{
		inputFile >> oldDetId >> newDetId;
		detIdMap_[oldDetId]=newDetId;
	}

	for( const auto& inputTag : inputCollectionNames_ ) produces<std::vector<PSimHit> >( inputTag.instance() );
}

void markstools::ModifyTrackerDetIds::produce( edm::Event& event, edm::EventSetup const& setup )
{
	for( const auto& inputTag : inputCollectionNames_ )
	{
		edm::Handle<std::vector<PSimHit> > hInputCollection;
		event.getByLabel( inputTag, hInputCollection );

		std::cout << "Collection " << inputTag << " has " << hInputCollection->size() << " entries." << std::endl;
		std::auto_ptr<std::vector<PSimHit> > pOutputCollection( new std::vector<PSimHit>() );

		for( const auto& simHit : *hInputCollection )
		{
			uint32_t oldDetId=simHit.detUnitId();
			uint32_t newDetId;
			std::map<uint32_t,uint32_t>::const_iterator iFindResult=detIdMap_.find( oldDetId );
			if( iFindResult!=detIdMap_.end() )
			{
				newDetId=iFindResult->second;
				std::cout << "    Modifying " << oldDetId << " to " << newDetId << std::endl;
			}
			else
			{
				newDetId=oldDetId;
				std::cout << "    Leaving " << oldDetId << " alone" << std::endl;
			}

			PSimHit modifiedSimHit( simHit.entryPoint(), simHit.exitPoint(),
					simHit.pabs(), simHit.tof(), simHit.energyLoss(),
					simHit.particleType(), newDetId, simHit.trackId(),
					simHit.thetaAtEntry(), simHit.phiAtEntry(), simHit.processType() );

			modifiedSimHit.setEventId( simHit.eventId() );

			pOutputCollection->push_back( std::move(modifiedSimHit) );
		} // end of loop over PSimHits

		event.put( pOutputCollection, inputTag.instance() );
	} // end of loop over InputTags
}
