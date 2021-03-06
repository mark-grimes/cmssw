#ifndef Utilities_CondDBImport_h
#define Utilities_CondDBImport_h

#include "CondCore/CondDB/interface/Types.h"
#include "CondCore/CondDB/interface/Session.h"
//

namespace cond {

  namespace persistency {

    cond::Hash import( const std::string& inputTypeName, const void* inputPtr, Session& destination );

    std::pair<std::string,boost::shared_ptr<void> > fetch( const cond::Hash& payloadId, Session& session );

  }

}

#endif
