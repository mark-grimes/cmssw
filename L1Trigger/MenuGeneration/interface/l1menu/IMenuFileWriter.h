#ifndef l1menu_IMenuFileWriter_h
#define l1menu_IMenuFileWriter_h

#include <vector>
#include <memory>

namespace l1menu
{
	class TriggerMenu;
	class IMenuRate;
}

namespace l1menu
{
	/** @brief Interface for the different implementations of the output file formats.
	 *
	 * @author Mark Grimes (from ideas by Brian Winer and Georgia Karapostoli)
	 * @date 27/Jan/2015
	 */
	class IMenuFileWriter
	{
	public:
		virtual ~IMenuFileWriter() {}
		virtual void add( const l1menu::TriggerMenu& menu ) = 0;
		virtual void add( const l1menu::IMenuRate& menuRate ) = 0;
	};

} // end of namespace l1menu

#endif
