#ifndef l1menu_ITriggerAlgorithm_h
#define l1menu_ITriggerAlgorithm_h

#include <string>
#include <vector>
#include "l1menu/ITrigger.h"

// Forward declarations
namespace l1menu
{
	class TriggerPrimitives;
}


namespace l1menu
{
	/** @brief Abstract interface for triggers used for menu studies.
	 *
	 * @author Mark Grimes (from ideas by Brian Winer and Georgia Karapostoli)
	 * @date 23/Jan/2015 (copied from code written around June 2013)
	 */
	class ITriggerAlgorithm : public l1menu::ITrigger
	{
	public:
		virtual ~ITriggerAlgorithm() {}
		/** @brief Returns true if an event with the supplied TriggerPrimitives would pass the trigger.
		 *
		 * This is where the main algorithm of the trigger is applied. */
		virtual bool apply( const l1menu::TriggerPrimitives& event ) const = 0;

		/** @brief True if any of the thresholds are correlated.
		 *
		 * This is used by the internal menu code to decide how to scale different thresholds. If you
		 * are subclassing this interface and you don't know what to reply here, reply false. There can
		 * sometimes be subtle correlations that are not obvious from the code so only reply true if
		 * you're absolutely certain.
		 *
		 * If there are no correlations then it gives more flexibility to change thresholds
		 * independently. If there are correlations then the thresholds have to be locked to scale
		 * proportionally.
		 */
		virtual bool thresholdsAreCorrelated() const = 0;

		/** @brief A version of the method from ITrigger that allows the parameter to be changed. */
		virtual float& parameter( const std::string& parameterName ) = 0;

		//
		// These are the methods from ITrigger that any subclass
		// needs to implement.
		//
		virtual const std::string name() const = 0;
		virtual unsigned int version() const = 0;
		virtual const std::vector<std::string> parameterNames() const = 0;
		virtual const float& parameter( const std::string& parameterName ) const = 0;
	};

} // end of namespace l1menu

#endif
