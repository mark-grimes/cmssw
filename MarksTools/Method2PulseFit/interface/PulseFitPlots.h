#ifndef MarksTools_Method2PulseFit_interface_PulseFitPlots_h
#define MarksTools_Method2PulseFit_interface_PulseFitPlots_h

#include <vector>

//
// Forward declarations
//
class DQMStore;
class MonitorElement;
namespace markstools
{
	class FittedPulse;
}

namespace markstools
{
	/** @brief Container for all the plots for a pulse fit.
	 * @author Mark Grimes
	 * @date 08/Jan/2015
	 */
	class PulseFitPlots
	{
	public:
		PulseFitPlots( DQMStore* pDQMStore );
		~PulseFitPlots();
		void fill( const markstools::FittedPulse& pulse );
	protected:
		MonitorElement* pChargeValFit_;
		MonitorElement* pTimeValFit_;
		MonitorElement* pPedValFit_;
		MonitorElement* pChi2_;
		MonitorElement* pDeltaTime_;
	};

} // end of namespace markstools


#endif
