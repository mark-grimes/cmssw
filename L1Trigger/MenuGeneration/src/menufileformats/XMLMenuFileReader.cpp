#include "XMLMenuFileReader.h"

#include "l1menu/TriggerMenu.h"
#include "l1menu/ITriggerAlgorithm.h"
#include "l1menu/TriggerConstraint.h"
#include "l1menu/Exceptions.h"

l1menu::menufileformats::XMLMenuFileReader::XMLMenuFileReader( const std::string& filename )
{
	inputFile_.parseFromFile(filename);
}

l1menu::menufileformats::XMLMenuFileReader::~XMLMenuFileReader()
{
	// No operation
}

std::vector< std::unique_ptr<l1menu::TriggerMenu> > l1menu::menufileformats::XMLMenuFileReader::getMenus() const
{
	std::vector<l1menu::tools::XMLElement> childElements=inputFile_.rootElement().getChildren("TriggerMenu");

	std::vector< std::unique_ptr<l1menu::TriggerMenu> > returnValue;
	for( const auto& menuElement : childElements )
	{
		std::unique_ptr<l1menu::TriggerMenu> pNewMenu( new l1menu::TriggerMenu );

		std::vector<l1menu::tools::XMLElement> triggerElements=menuElement.getChildren("Trigger");
		for( const auto& triggerElement : triggerElements )
		{
			std::vector<l1menu::tools::XMLElement> parameterElements=triggerElement.getChildren("name");
			if( parameterElements.size()!=1 ) throw l1menu::IncorrectFileFormatException( "Trigger doesn't have one and only one subelement called 'name'", __FILE__, __LINE__ );
			std::string triggerName=parameterElements.front().getValue();

			parameterElements=triggerElement.getChildren("version");
			if( parameterElements.size()!=1 ) throw l1menu::IncorrectFileFormatException( "Trigger doesn't have one and only one subelement called 'version'" );
			size_t version=parameterElements.front().getIntValue();

			l1menu::ITriggerAlgorithm& newTrigger=pNewMenu->addTrigger( triggerName, version );
			// Now loop over all of the parameters and set them
			parameterElements=triggerElement.getChildren("parameter");
			for( const auto& parameterElement : parameterElements )
			{
				std::string parameterName=parameterElement.getAttribute("name");
				float parameterValue=parameterElement.getFloatValue();
				newTrigger.parameter(parameterName)=parameterValue;
			}

			//
			// If the menu has any information about constraints when
			// scaling, include those as well.
			//
			if( triggerElement.hasAttribute("fractionOfTotalBandwidth") )
			{
				float fraction=triggerElement.getFloatAttribute("fractionOfTotalBandwidth");
				l1menu::TriggerConstraint& newConstraint=pNewMenu->getTriggerConstraint(pNewMenu->numberOfTriggers()-1);
				newConstraint.type( l1menu::TriggerConstraint::Type::FRACTION_OF_BANDWIDTH );
				newConstraint.value( fraction );
			}
			else if( triggerElement.hasAttribute("fixedRate") )
			{
				float rate=triggerElement.getFloatAttribute("fixedRate");
				l1menu::TriggerConstraint& newConstraint=pNewMenu->getTriggerConstraint(pNewMenu->numberOfTriggers()-1);
				newConstraint.type( l1menu::TriggerConstraint::Type::FIXED_RATE );
				newConstraint.value( rate );
			}
		}

		returnValue.push_back( std::move(pNewMenu) );
	}

	return returnValue;
}

std::vector< std::unique_ptr<l1menu::IMenuRate> > l1menu::menufileformats::XMLMenuFileReader::getRates() const
{
	throw l1menu::NotImplementedException( "Not implemented yet "+std::string(__FILE__)+"("+std::to_string(__LINE__)+")");
}
