#ifndef l1menu_TriggerPrimitives_h
#define l1menu_TriggerPrimitives_h

#include <vector>
#include <memory>

//
// Forward declarations
//
namespace l1t
{
	class CaloTower; // This declared properly in DataFormats/L1TCalorimeter/interface/CaloTower.h
} // end of namespace l1t



namespace l1menu
{
	/** @brief Class to bundle all the trigger primitives for one event together.
	 *
	 * @author mark.grimes@bristol.ac.uk (from ideas by Brian Winer and Georgia Karapostoli)
	 * @date 21/Jan/2015
	 */
	class TriggerPrimitives
	{
	public:
		TriggerPrimitives();

		/** @brief Whether or not there is a CaloTower collection present.
		 *
		 * This is used to distinguish between cases where a collection with no elements has been set,
		 * and where a collection has not been set at all.
		 */
		bool hasCaloTowers() const;
		size_t caloTowersSize() const;
		const l1t::CaloTower& caloTowerAt( size_t index ) const;

		template<class T_TowerIterator>
		void setTowerCollection( T_TowerIterator caloTowersStart, T_TowerIterator caloTowersEnd );
	private:
		bool hasCaloTowers_; ///< States whether a tower collection is present (not the same as a collection with no towers)
		std::vector<l1t::CaloTower*> caloTowers_;
	};
} // end of namespace l1menu


//
// Templates require the definition here. Everything else is in the .cpp file.
//
template<class T_TowerIterator>
void l1menu::TriggerPrimitives::setTowerCollection( T_TowerIterator caloTowersStart, T_TowerIterator caloTowersEnd )
{
	caloTowers_.clear();
	hasCaloTowers_=true; // Set this to true even if there are no elements

	while( caloTowersStart!=caloTowersEnd )
	{
		caloTowers_.emplace_back( &(*caloTowersStart) );
		++caloTowersStart;
	}
}

#endif // end of "#ifndef l1menu_TriggerPrimitives_h"
