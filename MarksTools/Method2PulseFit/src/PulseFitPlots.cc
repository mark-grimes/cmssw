#include "MarksTools/Method2PulseFit/interface/PulseFitPlots.h"

#include <FWCore/ServiceRegistry/interface/Service.h>
#include <DQMServices/Core/interface/DQMStore.h>
#include <DQMServices/Core/interface/MonitorElement.h>

markstools::PulseFitPlots::PulseFitPlots( DQMStore* pDQMStore ) :
		chargeValFitLimits_( 999999, -999999 ), timeValFitLimits_( 999999, -999999 ), pedValFitLimits_( 999999, -999999 ), chi2Limits_( 999999, -999999 ), NaNInFitLimits_( 999999, -999999 )
{
	pChargeValFit_=pDQMStore->book1D( "ChargeValFit", "ChargeValFit", 200, 0, 200 );
	pTimeValFit_=pDQMStore->book1D( "TimeValFit", "TimeValFit", 200, -100, 100 );
	pPedValFit_=pDQMStore->book1D( "PedValFit", "PedValFit", 200, -1, 5 );
	pChi2_=pDQMStore->book1D( "Chi2", "Chi2", 200, 0, 22000 );
	pNaNInFit_=pDQMStore->book1D( "NaNInFit", "NaNInFit", 200, 0, 100 );
}

markstools::PulseFitPlots::~PulseFitPlots()
{
	std::cout << "----- chargeValFitLimits_ " << chargeValFitLimits_.first << " " << chargeValFitLimits_.second << "\n"
			<< "----- timeValFitLimits_ " << timeValFitLimits_.first << " " << timeValFitLimits_.second << "\n" << "----- pedValFitLimits_ "
			<< pedValFitLimits_.first << " " << pedValFitLimits_.second << "\n" << "----- chi2Limits_ " << chi2Limits_.first << " "
			<< chi2Limits_.second << "\n" << "----- NaNInFitLimits_ " << NaNInFitLimits_.first << " " << NaNInFitLimits_.second << std::endl;
}

void markstools::PulseFitPlots::fill( const std::vector<double>& fitParsVec )
{
	if( fitParsVec[0] < chargeValFitLimits_.first ) chargeValFitLimits_.first=fitParsVec[0];
	if( fitParsVec[0] > chargeValFitLimits_.second ) chargeValFitLimits_.second=fitParsVec[0];

	if( fitParsVec[1] < timeValFitLimits_.first ) timeValFitLimits_.first=fitParsVec[1];
	if( fitParsVec[1] > timeValFitLimits_.second ) timeValFitLimits_.second=fitParsVec[1];

	if( fitParsVec[2] < pedValFitLimits_.first ) pedValFitLimits_.first=fitParsVec[2];
	if( fitParsVec[2] > pedValFitLimits_.second ) pedValFitLimits_.second=fitParsVec[2];

	if( fitParsVec[3] < chi2Limits_.first ) chi2Limits_.first=fitParsVec[3];
	if( fitParsVec[3] > chi2Limits_.second ) chi2Limits_.second=fitParsVec[3];

	if( fitParsVec[4] < NaNInFitLimits_.first ) NaNInFitLimits_.first=fitParsVec[4];
	if( fitParsVec[4] > NaNInFitLimits_.second ) NaNInFitLimits_.second=fitParsVec[4];

	pChargeValFit_->Fill( fitParsVec[0] );
	pTimeValFit_->Fill( fitParsVec[1] );
	pPedValFit_->Fill( fitParsVec[2] );
	pChi2_->Fill( fitParsVec[3] );
	pNaNInFit_->Fill( fitParsVec[4] );
}
