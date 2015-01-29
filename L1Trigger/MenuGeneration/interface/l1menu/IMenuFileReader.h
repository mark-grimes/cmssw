#ifndef l1menu_IMenuFileReader_h
#define l1menu_IMenuFileReader_h

#include <vector>
#include <memory>

namespace l1menu
{
	class TriggerMenu;
	class IMenuRate;
}

namespace l1menu
{
	/** @brief Interface for the different implementations of the file formats.
	 *
	 * @author Mark Grimes (from ideas by Brian Winer and Georgia Karapostoli)
	 * @date 27/Jan/2015
	 */
	class IMenuFileReader
	{
	public:
		virtual ~IMenuFileReader() {}
		virtual std::vector< std::unique_ptr<l1menu::TriggerMenu> > getMenus() const = 0;
		virtual std::vector< std::unique_ptr<l1menu::IMenuRate> > getRates() const = 0;
	};

} // end of namespace l1menu

#endif
