import FWCore.ParameterSet.Config as cms

produceMenuGenerationSample = cms.EDAnalyzer('MenuGenerationSampleCreator',
  clusterToken = cms.InputTag('caloStage2Digis', 'MP'),
  egToken = cms.InputTag('caloStage2Digis'),
  etSumToken = cms.InputTag('caloStage2Digis'),
  jetToken = cms.InputTag('caloStage2Digis'),
  tauToken = cms.InputTag('caloStage2Digis'),
  towerToken = cms.InputTag('caloStage2Digis', 'MP'),
  muonToken = cms.InputTag('caloStage2Digis')
)
