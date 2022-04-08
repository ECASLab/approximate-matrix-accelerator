#!/usr/bin/env python3
############################################################
# Copyright 2021
# Author: Luis G. Leon-Vega <lleon95@estudiantec.cr>
############################################################

import matplotlib.pyplot as plt
import numpy as np
from xml.etree import ElementTree as ET
import os
import glob
import csv

if os.environ.get("theme"):
    plt.style.use(os.environ["theme"])
else:
    plt.style.use('tableau-colorblind10')

latency = {"min": [], "max": [], "avg": []}
resources = {"dsp": [], "lut": [], "bram": [], "ff": []}
available_resources = {}
labels = []


def fill_data(file, label=""):
    # Get the tree
    print("Processing: ", file)
    tree = ET.parse(file)
    root = tree.getroot()
    if root is None:
        print("Cannot load data")
        return

    labels.append(label)
    # Get latency
    for p in root.findall('.//SummaryOfOverallLatency'):
        latency["min"].append(int(p.find('Best-caseLatency').text))
        latency["max"].append(int(p.find('Worst-caseLatency').text))
        latency["avg"].append(int(p.find('Average-caseLatency').text))

    # Get resources
    for p in root.findall('.//Resources'):
        resources["dsp"].append(int(p.find('DSP48E').text))
        resources["lut"].append(int(p.find('LUT').text))
        resources["bram"].append(int(p.find('BRAM_18K').text))
        resources["ff"].append(int(p.find('FF').text))

    # Get available resources
    for p in root.findall('.//AvailableResources'):
        available_resources["dsp"] = int(p.find('DSP48E').text)
        available_resources["lut"] = int(p.find('LUT').text)
        available_resources["bram"] = int(p.find('BRAM_18K').text)
        available_resources["ff"] = int(p.find('FF').text)


def write_reports(accels):
    files = {}
    # Create files
    for i in accels:
        f = open('measurements/processed/{}-report.data'.format(i), 'w')
        files[i] = f
        # First row
        row = ["dims", "bw", "min_lat", "avg_lat", "max_lat",
               "dsp", "lut", "bram", "ff"]
        writer = csv.writer(f, delimiter=' ')
        writer.writerow(row)

    count = 0
    for label in labels:
        accel = label[0]
        writer = csv.writer(files[accel], delimiter=' ')

        row = []
        row.append(label[1])  # dims
        row.append(label[2])  # bw
        # Latency
        row.append(latency["min"][count])
        row.append(latency["avg"][count])
        row.append(latency["max"][count])
        # Resources
        row.append(float(resources["dsp"][count]) /
                   float(available_resources["dsp"]))
        row.append(float(resources["lut"][count]) /
                   float(available_resources["lut"]))
        row.append(float(resources["bram"][count]) /
                   float(available_resources["bram"]))
        row.append(float(resources["ff"][count]) /
                   float(available_resources["ff"]))

        writer.writerow(row)

        count += 1

    # Close files
    for i in accels:
        files[i].close()


if __name__ == "__main__":
    # Get data
    files = []
    accels = []
    for file in glob.glob("measurements/*.xml"):
        files.append(file)

    for i in files:
        name = i.split('_')[0].split('/')[1]
        dims = i.split('_')[1]
        bw = i.split('_')[3].split('.')[0]
        if name not in accels:
            accels.append(name)

        fill_data(i, (name, dims, bw))
    write_reports(accels)
    print("Finished")
