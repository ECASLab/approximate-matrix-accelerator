#!/bin/bash
############################################################
## Copyright 2021
## Author: Luis G. Leon-Vega <lleon95@estudiantec.cr>
############################################################

cd measurements

rm maxerrs*

for file in $(ls *.log);
do
  MIN_ERR=$(cat ${file} | grep "TestMinVal" | awk '{print $3}')
  MAX_ERR=$(cat ${file} | grep "TestMaxVal" | awk '{print $3}')
  MEAN_ERR=$(cat ${file} | grep "TestMeanVal" | awk '{print $3}')
  STD_ERR=$(cat ${file} | grep "TestStdVal" | awk '{print $3}')
  ACCEL=$(echo ${file} | awk -F  "_" '{print $1}')
  Q_DIM=$(echo ${file} | awk -F  "_" '{print $2}')
  Q_WL=$(echo ${file} | awk -F  "_" '{print $4}' | sed 's/.log//g')
  echo "$ACCEL $Q_DIM $Q_WL $MIN_ERR $MAX_ERR $MEAN_ERR $STD_ERR" >> maxerrs_${ACCEL}.data
done
