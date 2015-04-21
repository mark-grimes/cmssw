#ifndef l1menu_triggers_SingleJetCentral_h
#define l1menu_triggers_SingleJetCentral_h

#include <string>
#include <vector>
#include "l1menu/ITriggerAlgorithm.h"

namespace l1menu
{
	namespace triggers
	{
		/** @brief Base class for all versions of the SingleJetCentral trigger.
		 *
		 * Note that this class is abstract because it doesn't implement the "version"
		 * and "apply" methods. That's left up to the implementations of the different
		 * versions.
		 *
		 * @author Mark Grimes (adapted from code written by Brian Winer)
		 * @date 02/Jun/2013
		 */
		class SingleJetCentral : public l1menu::ITriggerAlgorithm
		{
		public:
			SingleJetCentral();

			virtual const std::string name() const;
			virtual const std::vector<std::string> parameterNames() const;
			virtual float& parameter( const std::string& parameterName );
			virtual const float& parameter( const std::string& parameterName ) const;
		protected:
			float threshold1_;
			float etaCut_;
		}; // end of the SingleJetCentral base class

		/** @brief First version of the SingleJetCentral trigger.
		 *
		 * @author probably Brian Winer
		 * @date sometime
		 */
		class SingleJetCentral_v0 : public SingleJetCentral
		{
		public:
			virtual unsigned int version() const;
			virtual bool apply( const l1menu::TriggerPrimitives& event ) const;
			virtual bool thresholdsAreCorrelated() const;
		}; // end of version 0 class

	} // end of namespace triggers

} // end of namespace l1menu

#endif
