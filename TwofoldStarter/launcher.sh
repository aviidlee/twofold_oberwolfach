### USAGE ###############################
# ./launcher.sh <problem-instance-file> #
#########################################

# number of problems each job should try to solve
NUMPROBS=1
# Number of jobs we want to run at a time 
MAXJOBS=32
# file from which to get problem instances 
MAIN_IN=$1

if [ $# -eq 0 ]
then
    echo Missing argument: problem instance file.
    exit 1
fi 

while true; do
    # Check how many jobs we have running/queued. 
    let numRunning=$(qstat | wc -l)-2
    while [ $numRunning -lt $MAXJOBS ]
    do
        
        # Count the number of lines in input file
        numLeft=$(echo $(wc -l $MAIN_IN) | cut -d ' ' -f1)
        echo Number of problems left: $numLeft
        
        # Stop if we don't have any problems left
        if [ $numLeft -lt 1 ]
        then
           echo No problems left.
           exit 0 
        fi

        # Make separate input file
        inFile=${MAIN_IN}_${numLeft}.in
        outFile=${MAIN_IN}_${numLeft}.out
        tail -$NUMPROBS $MAIN_IN > $inFile

        # Delete problem instances we've done
        for i in `seq 1 $NUMPROBS`;
            do
                sed --in-place '$d' $MAIN_IN
            done
        
        # Launch!!!
        qsub runner.sh $inFile $outFile
        let numRunning=$(qstat | wc -l)-2

    done

    # Sleep for a bit before checking again. 
    sleep 10m
done
	
