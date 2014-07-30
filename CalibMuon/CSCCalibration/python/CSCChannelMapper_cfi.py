import FWCore.ParameterSet.Config as cms

CSCChannelMapperESSource = cms.ESSource("EmptyESSource",
 recordName = cms.string("CSCChannelMapperRecord"),
 firstValid = cms.vuint32(1),
 iovIsRunNotTime = cms.bool(True)  )

CSCChannelMapperESProducer = cms.ESProducer("CSCChannelMapperESProducer",
  AlgoName = cms.string("CSCChannelMapperStartup")
)

# Customise for different running scenarios
from SLHCUpgradeSimulations.Configuration.eraModifiers_cff import eraPostLS1

eraPostLS1.toModify( CSCChannelMapperESProducer, AlgoName="CSCChannelMapperPostls1" )
