#include "CrossTrigger.h"

#include "l1menu/Exceptions.h"

l1menu::triggers::CrossTrigger::CrossTrigger( l1menu::ITriggerAlgorithm& leg1Trigger, l1menu::ITriggerAlgorithm& leg2Trigger )
	: leg1_( leg1Trigger ), leg2_( leg2Trigger )
{
	// No operation besides the initialiser list
}

l1menu::triggers::CrossTrigger::~CrossTrigger()
{
	// No operation
}

const std::vector<std::string> l1menu::triggers::CrossTrigger::parameterNames() const
{
	std::vector<std::string> returnValue;

	std::vector<std::string> legParameterNames=leg1_.parameterNames();
	for( const auto& parameterName : legParameterNames ) returnValue.push_back( "leg1"+parameterName );

	legParameterNames=leg2_.parameterNames();
	for( const auto& parameterName : legParameterNames ) returnValue.push_back( "leg2"+parameterName );

	return returnValue;
}

float& l1menu::triggers::CrossTrigger::parameter( const std::string& parameterName )
{
	std::string firstFourCharacters=parameterName.substr(0,4);
	std::string everythingElse=parameterName.substr(4);

	if( firstFourCharacters=="leg1" ) return leg1_.parameter(everythingElse);
	else if( firstFourCharacters=="leg2" ) return leg2_.parameter(everythingElse);
	else throw l1menu::InvalidArgumentException( "Not a valid parameter name (\""+parameterName+"\") for "+name(), __FILE__, __LINE__ );
}

const float& l1menu::triggers::CrossTrigger::parameter( const std::string& parameterName ) const
{
	std::string firstFourCharacters=parameterName.substr(0,4);
	std::string everythingElse=parameterName.substr(4);

	if( firstFourCharacters=="leg1" ) return leg1_.parameter(everythingElse);
	else if( firstFourCharacters=="leg2" ) return leg2_.parameter(everythingElse);
	else throw l1menu::InvalidArgumentException( "Not a valid parameter name (\""+parameterName+"\") for "+name(), __FILE__, __LINE__ );
}

bool l1menu::triggers::CrossTrigger::apply( const l1menu::TriggerPrimitives& event ) const
{
	return leg1_.apply(event) && leg2_.apply(event);
}

bool l1menu::triggers::CrossTrigger::thresholdsAreCorrelated() const
{
	// If any thresholds in either of the legs are correlated then the say the whole trigger is
	return leg1_.thresholdsAreCorrelated() || leg2_.thresholdsAreCorrelated();
}
