#! /bin/bash

list=(4 16 32 64)

for i in ${list[@]}
do
# Copy the correct matrix to the working dir
    cp Tests/A_${i}x${i}.txt A.txt
    cp Tests/B_${i}x${i}.txt B.txt

# Execute the algorithm and redirect output to appropriate folder
    for(( q = 0 ; q < 10 ; q++ ))
    do
        mpiexec -n $i ./parallel $i $i $i >> Phase2Results/parallel/C_$i
        mpiexec -n $i ./parallelOMP $i $i $i >> Phase2Results/parallelOMP/C_$i
        mpiexec -n $i ./cannon $i $i $i >> Phase2Results/cannon/C_$i
    done
done
