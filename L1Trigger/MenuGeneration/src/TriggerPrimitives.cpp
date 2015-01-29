#include "l1menu/TriggerPrimitives.h"

l1menu::TriggerPrimitives::TriggerPrimitives()
	: hasCaloTowers_(false)
{
	// No operation besides the initialiser list.
}

bool l1menu::TriggerPrimitives::hasCaloTowers() const
{
	return hasCaloTowers_;
}

size_t l1menu::TriggerPrimitives::caloTowersSize() const
{
	return caloTowers_.size();
}

const l1t::CaloTower& l1menu::TriggerPrimitives::caloTowerAt( size_t index ) const
{
	return *caloTowers_.at(index);
}
