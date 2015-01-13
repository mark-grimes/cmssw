# Signal sample from /RelValQCDForPF_14TeV/CMSSW_6_2_0_SLHC22_patch1-PU_PH2_1K_FB_V6_SHNoTaperPU140-v1/GEN-SIM-DIGI-RAW (first file)
xrdcp root://eoscms//eos/cms/store/relval/CMSSW_6_2_0_SLHC22_patch1/RelValQCDForPF_14TeV/GEN-SIM-DIGI-RAW/PU_PH2_1K_FB_V6_SHNoTaperPU140-v1/00000/023EE68C-2F96-E411-8B34-02163E01039E.root ./step2.root


# Original config file is available at https://cmsweb.cern.ch/couchdb/reqmgr_config_cache/2ea20540c1c1aeec49a7c7e157a5c2f2/configFile
# Just modified:
#     - removed io command
cmsDriver.py step3 --conditions PH2_1K_FB_V6::All --pileup_input das:/RelValMinBias_TuneZ2star_14TeV/CMSSW_6_2_0_SLHC20_patch1-DES23_62_V1_refSHNoTaper-v1/GEN-SIM -n 10 --eventcontent FEVTDEBUGHLT,DQM -s RAW2DIGI,L1Reco,RECO,DQM --datatier GEN-SIM-RECO,DQMIO --pileup AVE_140_BX_25ns --customise SLHCUpgradeSimulations/Configuration/combinedCustoms.cust_2023SHCal --geometry Extended2023SHCalNoTaper,Extended2023SHCalNoTaperReco --magField 38T_PostLS1 --python RecoFullPU_Extended2023SHCalNoTaperPU.py --no_exec --filein file:step2.root --fileout file:step3.root

# Modify the process to only run until the module I'm testing
echo "from MarksTools.Method2PulseFit.sequenceModificationTools import cutSequenceAfterModule" >> RecoFullPU_Extended2023SHCalNoTaperPU.py
echo "cutSequenceAfterModule( process, process.hbheUpgradeReco )" >> RecoFullPU_Extended2023SHCalNoTaperPU.py
echo "process.load('Configuration.StandardSequences.EDMtoMEAtRunEnd_cff')" >> RecoFullPU_Extended2023SHCalNoTaperPU.py
echo "process.dqmsave_step = cms.Path(process.DQMSaver)" >> RecoFullPU_Extended2023SHCalNoTaperPU.py
echo "process.schedule.append( process.dqmsave_step )" >> RecoFullPU_Extended2023SHCalNoTaperPU.py
