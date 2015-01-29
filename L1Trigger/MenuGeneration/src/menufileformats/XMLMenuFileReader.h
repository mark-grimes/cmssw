#ifndef l1menu_XMLMenuFileReader_h
#define l1menu_XMLMenuFileReader_h

#include "l1menu/IMenuFileReader.h"
#include "l1menu/tools/XMLElement.h"
#include "l1menu/tools/XMLFile.h"
#include <string>

//
// Forward declarations
//
namespace l1menu
{
	class ITriggerRate;
	class ITriggerDescription;
	class ITriggerDescriptionWithErrors;
}


namespace l1menu
{
	namespace menufileformats
	{
		/** @brief Implementation of the IMenuFileReader interface for XML files.
		 *
		 * @author Mark Grimes (from ideas by Brian Winer and Georgia Karapostoli)
		 * @date 27/Jan/2015
		 */
		class XMLMenuFileReader : public l1menu::IMenuFileReader
		{
		public:
			XMLMenuFileReader( const std::string& filename );
			virtual ~XMLMenuFileReader();
			virtual std::vector< std::unique_ptr<l1menu::TriggerMenu> > getMenus() const;
			virtual std::vector< std::unique_ptr<l1menu::IMenuRate> > getRates() const;
		protected:
			l1menu::tools::XMLFile inputFile_;
		};

	} // end of the menufileformats namespace
} // end of the l1menu namespace
#endif
