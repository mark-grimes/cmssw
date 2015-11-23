import FWCore.ParameterSet.Config as cms

#
# This object is used to make changes for different running scenarios
#
from Configuration.StandardSequences.Eras import eras

from RecoLocalTracker.SiPixelRecHits.PixelCPEESProducers_cff import *
from RecoLocalTracker.SubCollectionProducers.trackClusterRemover_cfi import *
from RecoPixelVertexing.PixelLowPtUtilities.ClusterShapeHitFilterESProducer_cfi import *
from RecoPixelVertexing.PixelLowPtUtilities.ClusterShapeTrajectoryFilter_cfi import *
from RecoPixelVertexing.PixelTriplets.PixelTripletLargeTipGenerator_cfi import *
from RecoPixelVertexing.PixelTriplets.quadrupletseedmerging_cff import *
from RecoTracker.FinalTrackSelectors.ClassifierMerger_cfi import *
from RecoTracker.FinalTrackSelectors.TrackMVAClassifierDetached_cfi import *
from RecoTracker.FinalTrackSelectors.TrackMVAClassifierPrompt_cfi import *
from RecoTracker.TkSeedGenerator.GlobalSeedsFromTriplets_cff import *
from RecoTracker.TkTrackingRegions.GlobalTrackingRegionFromBeamSpot_cfi import RegionPsetFomBeamSpotBlock
from RecoTracker.TransientTrackingRecHit.TTRHBuilders_cff import *
from TrackingTools.TrajectoryCleaning.TrajectoryCleanerBySharedHits_cfi import trajectoryCleanerBySharedHits


#
# Utility function
#
def importIterativeTrackingSequence(moduleName,subModuleName="iterativeTk_cff"):
    """
    Imports the iterative tracking sequence from the directory name supplied, but changes
    the names of all objects to have the directory name appended. For example,
    
        importIterativeTrackingSequence("Phase1PU70")
    
    will load the tracking sequence specified in Phase1PU70/iterativeTk_cff.py but all
    object names will have "_Phase1PU70" at the end.
    
    This is so that tracking sequences for several scenarios can be written without the
    worry of shadowing any names in another sequence. Several sequences can be imported
    and then the one to be used can be selected with e.g.
    
        iterTracking = cms.Sequence(iterTracking_Phase1PU70)
        
    The name of the main sequence file can optionally be specified as a second argument,
    and defaults to "iterativeTk_cff". The ".py" should not be included.
    """
    g=globals()
    _module = __import__(moduleName+"."+subModuleName, g, locals(), [], 1)
    _subModule = getattr(_module,subModuleName)
    for objectName in dir(_subModule) :
        if not objectName in g.keys() :
            g[objectName+"_"+moduleName] = getattr(_subModule,objectName)

#
# Import all of the available sequences
#
importIterativeTrackingSequence("Run1")
importIterativeTrackingSequence("Run2")
importIterativeTrackingSequence("Phase1PU70")

iterTracking = cms.Sequence(iterTracking_Run2)
#
# Change the iterative tracking sequence depending on which scenario is active
#
if eras.Run1.isChosen() : iterTracking = cms.Sequence(iterTracking_Run1)
if eras.phase1Pixel.isChosen() : iterTracking = cms.Sequence(iterTracking_Phase1PU70)
