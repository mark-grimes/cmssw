import FWCore.ParameterSet.Config as cms

def importIterativeTrackingSequence(moduleName,subModuleName="iterativeTk_cff",myGlobals=globals()):
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
    g=myGlobals
    _module = __import__(moduleName+"."+subModuleName, g, locals(), [], 1)
    _subModule = getattr(_module,subModuleName)
    for objectName in dir(_subModule) :
        if not (objectName.startswith("_") or objectName=="cms") :
            g[objectName+"_"+moduleName] = getattr(_subModule,objectName)

importIterativeTrackingSequence("Phase1PU70")

iterTracking = cms.Sequence(iterTracking_Phase1PU70)