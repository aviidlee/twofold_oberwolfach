#! /bin/bash -l
#
#$ -N twofoldstarters
#$ -S /bin/bash
#$ -cwd
#$ -M youremail@uq.edu.au # email notifications are disabled
#$ -m es # due to overloading of mail servers
#$ -q low.q
###$ -l gpu=0 # needed for CPU only calc on asterix system
###$ -l gpu=1 # requests 1 GPU on asterix system
#
#$ -pe threaded 1 # single core calculation
#$ -R y

echo 'running with NSLOTS=' $NSLOTS # number of SGE calcs
echo 'running with machines=' $TMPDIR/machines # outputs machine list

# Arg1 - input file, full path. 
# Arg2 - output file, full path. 

infile=$1
execPath=/data/uqalee21/findstarterc/TwofoldStarter/src/starter
outdir=/data/uqalee21/starter_runners
outfile=$outdir/$2

echo 'Input file is ' $infile
echo 'Output file is ' $outfile

while IFS='' read -r line || [[ -n "$line" ]]; do
	$execPath $line $outfile
done < $infile
