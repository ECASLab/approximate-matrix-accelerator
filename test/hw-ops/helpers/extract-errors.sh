#!/bin/bash
############################################################
## Copyright 2021
## Author: Luis G. Leon-Vega <lleon95@estudiantec.cr>
############################################################

cd measurements

rm maxerrs*

PROC_FOLDER=processed
mkdir ${PROC_FOLDER}

for file in $(ls *.log);
do
  MIN_ERR=$(cat ${file} | grep "TestMinVal" | awk '{print $3}')
  MAX_ERR=$(cat ${file} | grep "TestMaxVal" | awk '{print $3}')
  MEAN_ERR=$(cat ${file} | grep "TestMeanVal" | awk '{print $3}')
  STD_ERR=$(cat ${file} | grep "TestStdVal" | awk '{print $3}')
  ACCEL=$(echo ${file} | awk -F  "_" '{print $1}')
  Q_DIM=$(echo ${file} | awk -F  "_" '{print $2}')
  Q_WL=$(echo ${file} | awk -F  "_" '{print $4}' | sed 's/.log//g')
  echo "$ACCEL $Q_DIM $Q_WL $MIN_ERR $MAX_ERR $MEAN_ERR $STD_ERR" >> ${PROC_FOLDER}/maxerrs_${ACCEL}.data

  # Get histogram
  HIST_BINS=$(cat ${file} | grep -e "Hist" | awk '{print $2}')
  HIST_PERC=$(cat ${file} | grep -e "Hist" | awk '{print $4}' | sed -e "s/://g")
  HIST_DATA=$(cat ${file} | grep -e "Hist" | awk -F "[" '{print $2}' | sed -e "s/; /\n/g" -e "s/\[//g" -e "s/\]//g")

  # Export histogram
  echo "${HIST_DATA}" > ${PROC_FOLDER}/hist_${HIST_BINS}_${HIST_PERC}_${Q_DIM}_${Q_WL}_${ACCEL}.data
done

# Process plots
cd ${PROC_FOLDER}
bash datatypes-histogram.sh
bash consumptions.sh
