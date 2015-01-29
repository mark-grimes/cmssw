#ifndef l1menu_triggers_CrossTrigger_h
#define l1menu_triggers_CrossTrigger_h

#include "l1menu/ITriggerAlgorithm.h"

namespace l1menu
{
	namespace triggers
	{
		/** @brief Abstract utility class for cross triggers.
		 *
		 * Combines two triggers and only fires if both fire. The parameters for each are
		 * accessed by prepending "leg1" or "leg2" to the parameter name. E.g. requesting
		 * parameter "leg1threshold1" will get parameter "threshold1" from the first trigger.
		 *
		 * Some cross triggers need to check that the two legs are not firing on the same
		 * object. In this case this class is not appropriate and a full implementation of
		 * ITriggerAlgorithm should be written that takes account of this.
		 *
		 * References are kept to the two triggers passed in the constructor, so they have to
		 * stay in scope for the whole duration the CrossTrigger does. The envisioned use is
		 * that this class is sub-classed, with the required triggers held as members of the
		 * derived class. The derived class also needs to provide the name and version methods.
		 *
		 * @author Mark Grimes (from ideas by Brian Winer and Georgia Karapostoli)
		 * @date 26/Jan/2015 (copied from code written 03/Jun/2013)
		 */
		class CrossTrigger : public l1menu::ITriggerAlgorithm
		{
		public:
			CrossTrigger( l1menu::ITriggerAlgorithm& leg1Trigger, l1menu::ITriggerAlgorithm& leg2Trigger );
			virtual ~CrossTrigger();
			virtual const std::vector<std::string> parameterNames() const;
			virtual float& parameter( const std::string& parameterName );
			virtual const float& parameter( const std::string& parameterName ) const;
			virtual bool apply( const l1menu::TriggerPrimitives& event ) const;
			virtual bool thresholdsAreCorrelated() const;
		protected:
			l1menu::ITriggerAlgorithm& leg1_;
			l1menu::ITriggerAlgorithm& leg2_;
		};

	} // end of namespace triggers

} // end of namespace l1menu

#endif
