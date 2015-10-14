#! /usr/bin/env python

# A Pyrelval Wrapper

def run():
        import sys
        import os
        import Configuration.Applications
        from Configuration.Applications.ConfigBuilder import ConfigBuilder
        from Configuration.Applications.cmsDriverOptions import OptionsFromCommandLine
        basicModules = sys.modules.keys() # Make a note of the modules before doing any configuration
        options = OptionsFromCommandLine()
        
        # after cleanup of all config parameters pass it to the ConfigBuilder
        configBuilder = ConfigBuilder(options, with_output = True, with_input = True)
        configBuilder.prepare()
        # fetch the results and write it to file
        config = file(options.python_filename,"w")
        config.write(configBuilder.pythonCfgCode)
        config.close()

        # handle different dump options
        if options.dump_python:
            # Need to unload any modules loaded during the previous configuration parse,
            # otherwise any statements in the modules will not be run on the new file
            # (python only executes them on first import). This means any era commands
            # will not be applied when loading the file back in.
            for moduleName in sys.modules.keys() :
                if not moduleName in basicModules :
                    del sys.modules[moduleName]
            result = {}
            execfile(options.python_filename, result)
            process = result["process"]
            expanded = process.dumpPython()
            expandedFile = file(options.python_filename,"w")
            expandedFile.write(expanded)
            expandedFile.close()
            print "Expanded config file", options.python_filename, "created"
            sys.exit(0)           
  
        if options.no_exec_flag:
            print "Config file "+options.python_filename+ " created"
            sys.exit(0)
        else:
            commandString = options.prefix+" cmsRun "+options.suffix
            print "Starting "+commandString+' '+options.python_filename
            commands = commandString.lstrip().split()
            os.execvpe(commands[0],commands+[options.python_filename],os.environ)
            sys.exit()

run()


    
