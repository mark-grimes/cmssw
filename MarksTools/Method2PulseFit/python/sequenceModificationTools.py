import FWCore.ParameterSet.Config as cms

class FindAllObjectsAfterVisitor :
    """
    A visitor that takes a single object in the constructor. When visiting it ignores everything
    until that object is found. Once it is found it records every object that occurs after it.
    """
    def __init__( self, objectToFind ) :
        self.objectToFind=objectToFind
        self.recordEverything=False
        self.entriesFound=[]
    def enter(self,item) :
        if self.recordEverything :
            self.entriesFound.append(item)
        else :
            if item==self.objectToFind : self.recordEverything=True
    def leave(self,item) :
        pass

class ListAllObjectsVisitor :
    """
    A visitor that just creates a list of everything it visits.
    """
    def __init__( self ) :
        self.entriesFound=[]
    def enter(self,item) :
        self.entriesFound.append(item)
    def leave(self,item) :
        pass

def cutSequenceAfterModule( process, module, exceptionsToKeep=[] ) :
    """
    Takes a process object and trims the sequence to only run until the supplied module.
    You can also specify modules to keep even if they are after the module with exceptionsToKeep.
    """
    alreadyFound=False
    # Loop over all the steps in the sequence and find the one with the module in it
    for step in range(0,len(process.schedule)) :
        try :
            if alreadyFound :
                # module was already in a previous step, so need to remove everything
                # unless it is in the list of exceptionsToKeep.
                visitor=ListAllObjectsVisitor()
                process.schedule[step].visit( visitor )
                # Remove every module in this list from the current step
                for entry in visitor.entriesFound :
                    if exceptionsToKeep.count( entry )==0 :
                        process.schedule[step].remove( entry )
            else :
                index=process.schedule[step].index(module)
                # If not found an exception is thrown and the next lines don't get run
                alreadyFound=True

                ## First remove all following steps
                #for stepToRemove in range(len(process.schedule)-1,step,-1) :
                #    process.schedule.remove( process.schedule[stepToRemove] )
                
                # Then create a list of all modules which follow the module in the current step
                visitor=FindAllObjectsAfterVisitor( module )
                process.schedule[step].visit( visitor )
                # Finally remove every module in this list from the current step
                for entry in visitor.entriesFound :
                    if exceptionsToKeep.count( entry )==0 :
                        process.schedule[step].remove( entry )
        
    
        except ValueError :
            # This happens when process.hbheUpgradeReco is not in the list. In that
            # case I went to do nothing and try the next step.
            pass
