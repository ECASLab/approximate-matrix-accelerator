#!/bin/bash
############################################################
## Copyright 2021
## Author: Luis G. Leon-Vega <lleon95@estudiantec.cr>
############################################################

cd measurements

rm maxerrs*

for file in $(ls *.log);
do
  MAX_ERR=$(cat ${file} | grep "MaxErrorTh" | awk '{print $2}')
  ACCEL=$(echo ${file} | awk -F  "_" '{print $1}')
  Q_R=$(echo ${file} | awk -F  "_" '{print $2}')
  Q_BW=$(echo ${file} | awk -F  "_" '{print $3}' | sed 's/.log//g')
  echo "$ACCEL $Q_R $Q_BW $MAX_ERR" >> maxerrs_${ACCEL}.data
done
