# Originally auto-generated but heavily modified. Most of the file could probably be cut
# out, the only important parts are the 10 or so lines at the end.
#
# Mark Grimes (mark.grimes@bristol.ac.uk)
# 04/Jul/2014

# Auto generated configuration file
# using: 
# Revision: 1.20 
# Source: /local/reps/CMSSW/CMSSW/Configuration/Applications/python/ConfigBuilder.py,v 
# with command line options: remapDetIds --conditions auto:upgrade2019 -n 10 --eventcontent FEVTDEBUG --relval 10000,100 -s GEN,SIM --datatier GEN-SIM --beamspot Gauss --customise SLHCUpgradeSimulations/Configuration/combinedCustoms.cust_2019 --geometry Extended2019 --magField 38T_PostLS1 --filein file:step1_SLHC12.root --fileout file:step1Remapped.root --no_exec
import FWCore.ParameterSet.Config as cms

process = cms.Process('SIMRemap')

# import of standard configurations
process.load('Configuration.StandardSequences.Services_cff')
process.load('SimGeneral.HepPDTESSource.pythiapdt_cfi')
process.load('FWCore.MessageService.MessageLogger_cfi')
process.load('Configuration.EventContent.EventContent_cff')
process.load('SimGeneral.MixingModule.mixNoPU_cfi')
process.load('Configuration.Geometry.GeometryExtended2019Reco_cff')
process.load('Configuration.Geometry.GeometryExtended2019_cff')
process.load('Configuration.StandardSequences.MagneticField_38T_PostLS1_cff')
process.load('Configuration.StandardSequences.Generator_cff')
process.load('IOMC.EventVertexGenerators.VtxSmearedGauss_cfi')
process.load('GeneratorInterface.Core.genFilterSummary_cff')
process.load('Configuration.StandardSequences.SimIdeal_cff')
process.load('Configuration.StandardSequences.EndOfProcess_cff')
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')

process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(-1)
)

# Input source
process.source = cms.Source("PoolSource",
    secondaryFileNames = cms.untracked.vstring(),
    fileNames = cms.untracked.vstring('file:step1_SLHC12.root')
)

process.options = cms.untracked.PSet(

)

# Production Info
process.configurationMetadata = cms.untracked.PSet(
    version = cms.untracked.string('$Revision: 1.20 $'),
    annotation = cms.untracked.string('remapDetIds nevts:10'),
    name = cms.untracked.string('Applications')
)

# Output definition

process.FEVTDEBUGoutput = cms.OutputModule("PoolOutputModule",
    splitLevel = cms.untracked.int32(0),
    eventAutoFlushCompressedSize = cms.untracked.int32(5242880),
    outputCommands = process.FEVTDEBUGEventContent.outputCommands,
    fileName = cms.untracked.string('file:step1Remapped.root'),
    dataset = cms.untracked.PSet(
        filterName = cms.untracked.string(''),
        dataTier = cms.untracked.string('GEN-SIM')
    ),
#    SelectEvents = cms.untracked.PSet(
#        SelectEvents = cms.vstring('generation_step')
#    )
)

# Additional output definition

# Other statements
process.genstepfilter.triggerConditions=cms.vstring("generation_step")
from Configuration.AlCa.GlobalTag import GlobalTag
process.GlobalTag = GlobalTag(process.GlobalTag, 'auto:upgrade2019', '')

# Path and EndPath definitions
process.generation_step = cms.Path(process.pgen)
process.simulation_step = cms.Path(process.psim)
process.genfiltersummary_step = cms.EndPath(process.genFilterSummary)
process.endjob_step = cms.EndPath(process.endOfProcess)
process.FEVTDEBUGoutput_step = cms.EndPath(process.FEVTDEBUGoutput)

# Schedule definition
process.schedule = cms.Schedule(process.generation_step,process.genfiltersummary_step,process.simulation_step,process.endjob_step,process.FEVTDEBUGoutput_step)

# customisation of the process.

# Automatic addition of the customisation function from SLHCUpgradeSimulations.Configuration.combinedCustoms
from SLHCUpgradeSimulations.Configuration.combinedCustoms import cust_2019 

#call to customisation function cust_2019 imported from SLHCUpgradeSimulations.Configuration.combinedCustoms
process = cust_2019(process)

# End of customisation functions

#----------------------------------------------------------------------------
#-- Important stuff starts here. This overwrites most of the earlier lines --
#----------------------------------------------------------------------------
process.g4SimHits = cms.EDProducer("ModifyTrackerDetIds",
	mapFilename=cms.string("trackerDetIdMap.txt"),
	inputCollections=cms.VInputTag(
		cms.InputTag("g4SimHits","TrackerHitsPixelEndcapHighTof"),
		cms.InputTag("g4SimHits","TrackerHitsPixelEndcapLowTof")
	),
)
process.g4SimHits_step = cms.Path(process.g4SimHits)

process.FEVTDEBUGoutput.outputCommands.append( "keep *_g4SimHits_*_SIMRemap" )
process.FEVTDEBUGoutput.outputCommands.append( "drop *_g4SimHits_TrackerHitsPixelEndcapHighTof_SIM" )
process.FEVTDEBUGoutput.outputCommands.append( "drop *_g4SimHits_TrackerHitsPixelEndcapLowTof_SIM" )

process.schedule = cms.Schedule(process.g4SimHits_step,process.FEVTDEBUGoutput_step)
