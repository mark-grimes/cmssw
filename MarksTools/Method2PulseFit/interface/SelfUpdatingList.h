#ifndef MarksTools_Method2PulseFit_interface_SelfUpdatingList_h
#define MarksTools_Method2PulseFit_interface_SelfUpdatingList_h

namespace markstools
{
	template<class T_Element>
	class SelfUpdatingList
	{
	public:
		typedef std::function<bool(const T_Element&,const T_Element&)> ComparisonFunction;
		typedef std::function<bool(const T_Element&)> RequirementFunction;
	public:
		SelfUpdatingList( size_t maxSize );
		SelfUpdatingList( size_t maxSize, std::function<bool(const T_Element&,const T_Element&)> compare );
		SelfUpdatingList( size_t maxSize, std::function<bool(const T_Element&,const T_Element&)> compare, std::function<bool(const T_Element&)> requirement );
		void add( const T_Element& element );

		typename std::list<T_Element>::iterator begin();
		typename std::list<T_Element>::iterator end();
		typename std::list<T_Element>::const_iterator begin() const;
		typename std::list<T_Element>::const_iterator end() const;
	protected:
		size_t maxSize_;
		std::function<bool(const T_Element&,const T_Element&)> compare_;
		std::function<bool(const T_Element&)> requirement_;
		std::list<T_Element> elements_;
	};
} // end of namespace markstools

template<class T_Element>
markstools::SelfUpdatingList<T_Element>::SelfUpdatingList( size_t maxSize )
	: maxSize_(maxSize),
	  compare_( [](const T_Element& itemA,const T_Element& itemB){return itemA>itemB;} ),
	  requirement_( [](const int& itemA){return true;} )
{
	// No operation besides the initialiser list
}

template<class T_Element>
markstools::SelfUpdatingList<T_Element>::SelfUpdatingList( size_t maxSize, std::function<bool(const T_Element&,const T_Element&)> compare )
	: maxSize_(maxSize),
	  compare_(compare),
	  requirement_( [](const int& itemA){return true;} )
{
	// No operation besides the initialiser list
}

template<class T_Element>
markstools::SelfUpdatingList<T_Element>::SelfUpdatingList( size_t maxSize, std::function<bool(const T_Element&,const T_Element&)> compare, std::function<bool(const T_Element&)> requirement )
	: maxSize_(maxSize),
	  compare_(compare),
	  requirement_(requirement)
{
	// No operation besides the initialiser list
}

template<class T_Element>
void markstools::SelfUpdatingList<T_Element>::add( const T_Element& newItem )
{
	// Make sure the item passes the minimum requirements
	if( !requirement_(newItem) ) return;

	// Then search through the ordered list to see if it should be added somewhere
	auto iOrderedPlacing=elements_.begin();
	for( ; iOrderedPlacing!=elements_.end(); ++iOrderedPlacing )
	{
		if( compare_(newItem,*iOrderedPlacing) ) break; // newItem should appear before this one
	}

	// Insert the new item in the correct place of the ordered list.
	elements_.insert( iOrderedPlacing, newItem );

	// Make sure the list never grows larger than the predefined maximum.
	if( elements_.size()>maxSize_ ) elements_.resize(maxSize_);
}

template<class T_Element>
typename std::list<T_Element>::iterator markstools::SelfUpdatingList<T_Element>::begin()
{
	return elements_.begin();
}

template<class T_Element>
typename std::list<T_Element>::iterator markstools::SelfUpdatingList<T_Element>::end()
{
	return elements_.end();
}

template<class T_Element>
typename std::list<T_Element>::const_iterator markstools::SelfUpdatingList<T_Element>::begin() const
{
	return elements_.begin();
}

template<class T_Element>
typename std::list<T_Element>::const_iterator markstools::SelfUpdatingList<T_Element>::end() const
{
	return elements_.end();
}


#endif
