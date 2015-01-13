#include "MarksTools/Method2PulseFit/interface/FittedPulse.h"

#include <array> // Need this because PulseShapeFitOOTPileupCorrection.h doesn't include it directly
#include "RecoLocalCalo/HcalRecAlgos/interface/PulseShapeFitOOTPileupCorrection.h"
#include <FWCore/ServiceRegistry/interface/Service.h>
#include <DQMServices/Core/interface/DQMStore.h>
#include <DQMServices/Core/interface/MonitorElement.h>

markstools::FittedPulse::FittedPulse()
	: chi2_(0), fittedPedestal_(0), preSamples_(0)
{
	// No operation besides the initialiser list
}

void markstools::FittedPulse::setPulse( const std::vector<double>& pulse )
{
	pulse_=pulse;
}

void markstools::FittedPulse::setPreSamples( size_t preSamples )
{
	preSamples_=preSamples;
}

double markstools::FittedPulse::chi2() const
{
	return chi2_;
}

void markstools::FittedPulse::setChi2( double chi2 )
{
	chi2_=chi2;
}

void markstools::FittedPulse::setFittedPulse( size_t pulseNumber, double time, double charge )
{
	if( pulseNumber>=fittedPulses_.size() ) fittedPulses_.resize( pulseNumber+1 );
	fittedPulses_[pulseNumber]=std::make_pair(time,charge);
}

void markstools::FittedPulse::resetFittedPulses()
{
	chi2_=0;
	fittedPedestal_=0;
	fittedPulses_.clear();
}

void markstools::FittedPulse::setFittedPedestal( double pedestal )
{
	fittedPedestal_=pedestal;
}

void markstools::FittedPulse::plotAllQuantities( DQMStore* pDQMStore, FitterFuncs::PulseShapeFunctor pulseShapeFunctor ) const
{
	const double binWidth=25;
	const double lowEdge=-binWidth*(static_cast<double>(preSamples_)+0.5);
	const double highEdge=lowEdge+HcalConst::maxSamples*binWidth;
	//const double lowEdge= -HcalConst::iniTimeShift;
	//const double highEdge= -HcalConst::iniTimeShift+(HcalConst::maxSamples*HcalConst::nsPerBX);

	MonitorElement* pPulse=pDQMStore->book1D( "Pulse", "pulse", pulse_.size(), lowEdge, highEdge );
	for( size_t index=0; index<pulse_.size(); ++index ) pPulse->setBinContent( index+1, pulse_[index] );
	pDQMStore->bookFloat( "chi2" )->Fill( chi2_ );

	std::vector<double> combinedFittedPulses(pulse_.size());
	for( size_t pulseIndex=0; pulseIndex<fittedPulses_.size(); ++pulseIndex )
	{
		pDQMStore->bookFloat( "FittedPulse"+std::to_string(pulseIndex)+" pulse time" )->Fill( fittedPulses_[pulseIndex].first );
		pDQMStore->bookFloat( "FittedPulse"+std::to_string(pulseIndex)+" pulse height" )->Fill( fittedPulses_[pulseIndex].second );

		MonitorElement* pFittedPulse=pDQMStore->book1D( "FittedPulse"+std::to_string(pulseIndex), "FittedPulse"+std::to_string(pulseIndex), pulse_.size(), lowEdge, highEdge );
		std::array<float,HcalConst::maxSamples> result;
		pulseShapeFunctor.funcHPDShape( result, fittedPulses_[pulseIndex].first, fittedPulses_[pulseIndex].second, 0 );
		for( size_t index=0; index<result.size(); ++index )
		{
			pFittedPulse->setBinContent( index+1, result[index] );
			combinedFittedPulses[index]+=result[index];
		}
	}

	MonitorElement* pCombinedFittedPulse=pDQMStore->book1D( "CombinedFittedPulse", "CombinedFittedPulse", pulse_.size(), lowEdge, highEdge );
	for( size_t index=0; index<combinedFittedPulses.size(); ++index ) pCombinedFittedPulse->setBinContent( index+1, combinedFittedPulses[index] );


}
