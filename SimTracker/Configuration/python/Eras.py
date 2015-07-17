import FWCore.ParameterSet.Config as cms

class Eras (object):
    """
    Dummy container for all the SimTracker specific cms.Modifier instances
    that config fragments can use to selectively configure depending on what
    scenario is active.
    """
    def __init__(self):
        # The names of these eras are fixed, because the central config code
        # in Configuration.StandardSequences.Eras pulls them in. Whether these
        # are single cms.Modifiers, or cms.ModifierChains made of sub-eras is
        # up to Tracker/ing.
        self.phase1_2017 = cms.Modifier()

eras=Eras()
