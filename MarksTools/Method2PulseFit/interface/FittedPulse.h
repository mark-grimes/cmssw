#ifndef MarksTools_Method2PulseFit_interface_FittedPulse_h
#define MarksTools_Method2PulseFit_interface_FittedPulse_h

#include <vector>
#include <cstddef>
#include <functional>

// Need this include for HcalConst
#include "RecoLocalCalo/HcalRecAlgos/interface/PulseShapeFitOOTPileupCorrection.h"

//
// Forward declarations
//
class DQMStore;
namespace markstools
{
	class PulseFitPlots;
}

namespace markstools
{
	/** @brief Class to hold all information about a pulse and its fit.
	 * Used to contain the data while a decision is made about whether to plot it or not, e.g.
	 * the ten instances with the highest chi2 are stored, then plots made from them at the end
	 * of the run.
	 * @author Mark Grimes
	 * @date 09/Jan/2015
	 */
	class FittedPulse
	{
		friend class markstools::PulseFitPlots;
		typedef std::function<void(std::array<float,HcalConst::maxSamples>& ntmpbin,const double &pulseTime,const double &pulseHeight,const double &slew)> PulseShapeFunction;
	public:
		FittedPulse();
		void setPulse( const std::vector<double>& pulse );
		void setPreSamples( size_t preSamples );
		double chi2() const;
		void setChi2( double chi2 );
		void setFittedPulse( size_t pulseNumber, double time, double charge );
		void setChosenPulse( int pulseNumber );
		void resetFittedPulses();
		void setFittedPedestal( double pedestal );
		void plotAllQuantities( DQMStore* pDQMStore, PulseShapeFunction pulseShapeFunction ) const;
	protected:
		std::vector<double> pulse_;
		double chi2_;
		std::vector< std::pair<double,double> > fittedPulses_;
		int chosenPulse_;
		double fittedPedestal_;
		size_t preSamples_; // The number of samples before the triggered bunch crossing
	};

} // end of namespace markstools


#endif
