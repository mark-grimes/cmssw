#include "MarksTools/Method2PulseFit/interface/PulseFitPlots.h"

#include "MarksTools/Method2PulseFit/interface/FittedPulse.h"
#include <FWCore/ServiceRegistry/interface/Service.h>
#include <DQMServices/Core/interface/DQMStore.h>
#include <DQMServices/Core/interface/MonitorElement.h>

markstools::PulseFitPlots::PulseFitPlots( DQMStore* pDQMStore )
{
	pChargeValFit_=pDQMStore->book1D( "ChargeValFit", "ChargeValFit", 200, 0, 200 );
	pTimeValFit_=pDQMStore->book1D( "TimeValFit", "TimeValFit", 200, -100, 100 );
	pPedValFit_=pDQMStore->book1D( "PedValFit", "PedValFit", 200, -1, 5 );
	pChi2_=pDQMStore->book1D( "Chi2", "Chi2", 200, 0, 22000 );
	pDeltaTime_=pDQMStore->book2D( "deltaTime", "deltaTime", 8, 0, 200, 8, 0, 200 );
}

markstools::PulseFitPlots::~PulseFitPlots()
{
	// No operation
}

void markstools::PulseFitPlots::fill( const markstools::FittedPulse& pulse )
{
	if( pulse.chosenPulse_!=-1 ) // If a pulse was successfully chosen
	{
		pChargeValFit_->Fill( pulse.fittedPulses_[pulse.chosenPulse_].second );
		pTimeValFit_->Fill( pulse.fittedPulses_[pulse.chosenPulse_].first );

		if( pulse.fittedPulses_.size()==3 ) // If it was a 3 pulse fit, plot the difference in time between the pulses
		{
			std::vector<double> timeDifferences;
			for( size_t index=0; index<pulse.fittedPulses_.size(); ++index )
			{
				if( static_cast<int>(index)==pulse.chosenPulse_ ) continue; // don't work out difference to itself
				timeDifferences.push_back( std::abs(pulse.fittedPulses_[pulse.chosenPulse_].first-pulse.fittedPulses_[index].first) );
			}
			// Presumably this vector has only 2 entries. Sort in ascending order.
			std::sort( timeDifferences.begin(), timeDifferences.end() );

			pDeltaTime_->Fill( timeDifferences[0], timeDifferences[1] );
		}
	}
	pPedValFit_->Fill( pulse.fittedPedestal_ );
	pChi2_->Fill( pulse.chi2_ );
}
