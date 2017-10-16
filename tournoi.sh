#!/bin/bash
J1=0
J2=0
for VARIABLE in {1..200}
do
    tmp=$(./main --tournoi 3 2)
    sleep 0.03
	if [[ $tmp -eq "1" ]]
    then
        let J1=$J1+1
    else
        let J2=$J2+1
    fi
done

echo $J1
echo $J2