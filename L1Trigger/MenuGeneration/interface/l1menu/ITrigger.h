#ifndef l1menu_ITrigger_h
#define l1menu_ITrigger_h

#include <string>
#include <vector>


namespace l1menu
{
	/** @brief Abstract interface for a description. This interface should give enough information to
	 * uniquely describe a specific trigger.
	 *
	 * This will give enough information to create a specific algorithm and set all the parameters, but not
	 * actually contain the code. The code will be in specific subclass of the l1menu::ITriggerAlgorithm class.
	 *
	 * @author Mark Grimes (from ideas by Brian Winer and Georgia Karapostoli)
	 * @date 23/Jan/2015 (copied from code written 14/Oct/2013)
	 */
	class ITrigger
	{
	public:
		virtual ~ITrigger() {}
		virtual const std::string name() const = 0;
		virtual unsigned int version() const = 0;
		virtual const std::vector<std::string> parameterNames() const = 0;
		virtual const float& parameter( const std::string& parameterName ) const = 0;
	};

} // end of namespace l1menu

#endif
