#ifndef L1Trigger_MenuGeneration_plugins_MenuGenerationSampleCreator_h
#define L1Trigger_MenuGeneration_plugins_MenuGenerationSampleCreator_h

#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "DataFormats/L1Trigger/interface/BXVector.h"

//
// Forward declarations
//
namespace l1t
{
	class CaloCluster;
	class EGamma;
	class CaloTower;
	class EtSum;
	class Jet;
	class Tau;
	class Muon;
}


namespace l1menu
{
	class MenuGenerationSampleCreator : public edm::EDAnalyzer
	{
	public:
		explicit MenuGenerationSampleCreator( const edm::ParameterSet& config );
		~MenuGenerationSampleCreator();

		static void fillDescriptions( edm::ConfigurationDescriptions& descriptions );
	private:
		virtual void beginJob() override;
		virtual void analyze( const edm::Event& event, const edm::EventSetup& eventSetup ) override;
		virtual void endJob() override;

		edm::EDGetTokenT< BXVector<l1t::CaloCluster> > clusterToken_;
		edm::EDGetTokenT< BXVector<l1t::EGamma> > egToken_;
		edm::EDGetTokenT< BXVector<l1t::CaloTower> > towerToken_;
		edm::EDGetTokenT< BXVector<l1t::EtSum> > etSumToken_;
		edm::EDGetTokenT< BXVector<l1t::Jet> > jetToken_;
		edm::EDGetTokenT< BXVector<l1t::Tau> > tauToken_;
		edm::EDGetTokenT< BXVector<l1t::Muon> > muonToken_;
	};

} // end of namespace l1menu

#endif
