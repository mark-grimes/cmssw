#include "MenuGenerationSampleCreator.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "DataFormats/L1TCalorimeter/interface/CaloTower.h"

namespace l1menu
{
	DEFINE_FWK_MODULE(MenuGenerationSampleCreator);
}

l1menu::MenuGenerationSampleCreator::MenuGenerationSampleCreator( const edm::ParameterSet& config )
{
	clusterToken_=consumes< BXVector<l1t::CaloCluster> >( config.getParameter<edm::InputTag>("clusterToken") );
	egToken_=consumes< BXVector<l1t::EGamma> >( config.getParameter<edm::InputTag>("egToken") );
	towerToken_=consumes< BXVector<l1t::CaloTower> >( config.getParameter<edm::InputTag>("towerToken") );
	etSumToken_=consumes< BXVector<l1t::EtSum> >( config.getParameter<edm::InputTag>("etSumToken") );
	jetToken_=consumes< BXVector<l1t::Jet> >( config.getParameter<edm::InputTag>("jetToken") );
	tauToken_=consumes< BXVector<l1t::Tau> >( config.getParameter<edm::InputTag>("tauToken") );
	muonToken_=consumes< BXVector<l1t::Muon> >( config.getParameter<edm::InputTag>("muonToken") );
}

l1menu::MenuGenerationSampleCreator::~MenuGenerationSampleCreator()
{
	// No operation
}

void l1menu::MenuGenerationSampleCreator::fillDescriptions( edm::ConfigurationDescriptions& descriptions )
{
	edm::ParameterSetDescription defaultDescription;

	defaultDescription.add<edm::InputTag>( "clusterToken", edm::InputTag("caloStage2Digis","MP") );
	defaultDescription.add<edm::InputTag>( "egToken", edm::InputTag("caloStage2Digis") );
	defaultDescription.add<edm::InputTag>( "etSumToken", edm::InputTag("caloStage2Digis") );
	defaultDescription.add<edm::InputTag>( "jetToken", edm::InputTag("caloStage2Digis") );
	defaultDescription.add<edm::InputTag>( "tauToken", edm::InputTag("caloStage2Digis") );
	defaultDescription.add<edm::InputTag>( "towerToken", edm::InputTag("caloStage2Digis","MP") )->setComment("The input tower collection to use");
	defaultDescription.add<edm::InputTag>( "muonToken", edm::InputTag("caloStage2Digis") );

	descriptions.add("produceMenuGenerationSample",defaultDescription);
}

void l1menu::MenuGenerationSampleCreator::beginJob()
{

}

void l1menu::MenuGenerationSampleCreator::analyze( const edm::Event& event, const edm::EventSetup& eventSetup )
{
	std::cout << "------- Started analyze" << std::endl;
	edm::Handle< BXVector<l1t::CaloTower> > towers;
	event.getByToken(towerToken_,towers);
	std::cout << "towers.size()=" << towers->size(0) << std::endl;
	std::cout << "------- Finished analyze" << std::endl;
}

void l1menu::MenuGenerationSampleCreator::endJob()
{

}
