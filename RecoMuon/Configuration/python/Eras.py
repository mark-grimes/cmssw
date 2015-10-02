import FWCore.ParameterSet.Config as cms

class Eras (object):
    """
    Dummy container for all the RecoMuon specific cms.Modifier instances
    that config fragments can use to selectively configure depending on what
    scenario is active.
    """
    def __init__(self):
        self.me0 = cms.Modifier()

        # The names of these eras are fixed, because the central config code
        # in Configuration.StandardSequences.Eras pulls them in. Whether these
        # are single cms.Modifiers, or cms.ModifierChains made of sub-eras is
        # up to muon DPG.
        self.phase2 = cms.ModifierChain(self.me0)

eras=Eras()
