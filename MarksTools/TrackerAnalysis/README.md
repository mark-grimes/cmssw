Very brief instructions.

In an SLHC14/15/whatever release cd to the test directory and execute

    cmsRun dumpDetIds_cfg.py > trackerDetIdsSLHC14.log

Do the same in an SLHC11/12/whatever. Trim off the first few lines at the top so you just have the detector info. For the next step, each line in the SLHC14 file has to match the SLHC12. The easiest way to do this is:

    sort trackerDetIdsSLHC14.log > trackerDetIdsSLHC14_sorted.log
    sort trackerDetIdsSLHC12.log > trackerDetIdsSLHC12_sorted.log

Each file should then have the detector at a particular position and rotation on the same line. You can do a diff on the files and should see that the only difference is in the DetIds for the PixelEndcap. Also differences in the reported disc or whatever but that's just extracted from the DetId.

Next step is to extract just the DetIds that are different. The script createDetIdMap.py just print out the DetIds for every line where they're different.

    ./createDetIdMap.py trackerDetIdsSLHC12_sorted.log trackerDetIdsSLHC14_sorted.log > trackerDetIdMap.txt

Then use that file as input to remapDetIds_cfg.py, changing the input to an SLHC12 GEN-SIM file.

    cmsRun remapDetIds_cfg.py

