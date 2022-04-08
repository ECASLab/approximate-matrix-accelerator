# Approximate Matrix Accelerator

## Software version

### Compiling

For compiling the code, no dependencies are needed so far. You may only need the `meson` building system. Please, follow these steps to get it into your system:

```bash
sudo apt update
sudo apt install python3 python3-pip ninja-build
sudo pip3 install meson
sudo apt install openmpi-common libopenmpi2 or libopenmpi-dev
sudo apt-get install openmpi-bin
pip3 install matplotlib numpy
```
#### Note for Ubuntu 16.04

We have found some difficulties while installing Python, Meson and Ninja on Ubuntu 16.04. Please, follow these steps to deal with the versioning issues.

1. For Python3 and Pip3

Installing miniconda:

```bash
wget https://repo.anaconda.com/miniconda/Miniconda3-py38_4.10.3-Linux-x86_64.sh
bash Miniconda3-py38_4.10.3-Linux-x86_64.sh
```

During the installation, it will ask for installation details. Just accept the defaults. At the end, your console will reload with a conda environment. You should be able to install meson without any issues by using `pip3`.

2. For Ninja

The `apt` repos are really out-dated. Install ninja by doing:

```bash
wget https://github.com/ninja-build/ninja/releases/download/v1.8.2/ninja-linux.zip
sudo unzip ninja-linux.zip -d /usr/local/bin/
```

From now on, `ninja` has been installed.

After installing the building system, compile the code:

```bash
meson builddir
ninja -C builddir
```

### Testing

You can test the code by using:

```bash
cd builddir/test/sw-ops
./matadd # For addition
./matmul # For multiplication
./matmac # For multiply-add
./matfma # For fused multiply-add
```

or

```bash
ninja -C builddir test
```

> Deprecation warning. In next releases, the SW version will be deprecated.

## Hardware version

For the hardware version, you will need Vivado HLS 2018.2.

You can run the tests in the following way:

```bash
# Run a synthesis + simulation
cd test/hw-ops/
TEST=matadd make test

# Run everything
make measure-all

# Extracts data
make extract-data

# Clean all
make clean
```

where the possible targets are:

* test: performs the tests on a given testbench
* measure: synthesises, runs and extracts the logs for measurement
* measure-all: runs all the synthesis and simulations
* extract-data: cleans the logs, recompiling just the useful information

and where the environment variables are:

* TEST: name of the tests. Please, inspect `test/hw-ops/tops/*.cpp` for the possible tests. You can also use `make help`.
* Q_ROWS: Number of rows. Default: 8
* Q_COLS: Number of columns. Default: 8
* Q_SEED: Seed for generating random numbers. Default: 10
* Q_DATATYPE: datatype of hardware matrices. Default: ap_fixed
* Q_WL: word length of datatype. Default: 8
* Q_USE_HLS_MATH: enables the hls math library. Default: 1
* Q_USE_REG_UNROLLING: selects which scenario use in matfma operation. Default: 0, for scenario 1.
* SYN_TOOL: name of the synthesis tool. By default, it is `vivado_hls`

> If something fails and it is related to `vivado_hls not found`, please, make sure of having it in the environment. Usually, it requires:
> `source /opt/Xilinx/Vivado/2018.2/settings64.sh`

## Important data

After the extraction, the relevant files are in [report](./report/)

Documentation: available [here](https://msee2.gitlab.io/approximate-flexible-acceleration-ml/approximate-gemm-accelerator).


## How to cite

Please, feel free to cite any of the following sources:

### Plain Text

* Salazar-Villalobos, Eduardo, Leon-Vega Luis G., Castro-Godinez Jorge. 2022. Automatic Generation of Matrix Multiply-Add Architectures using High-Level Synthesis [Under review]. *IEEE Embedded Systems Letters (ESL)* (2022)
* Leon-Vega Luis G., Salazar-Villalobos, Eduardo, Rodriguez-Figueroa, Alejandro, Castro-Godinez Jorge, Salazar-Villalobos, Eduardo. 2022. Automatic Generation of Resource and Accuracy Configurable Processing Elements for Deep CNNs [Under review]. *ACM Transactions on Embedded Computing Systems* (2022)

### BibTeX

```bibtex
% GEMMA Paper: For the v1.0.0 of the project
@article{gemma_v1.0.0,
  author = {Salazar-Villalobos, Eduardo,
            Leon-Vega, Luis G.
            Castro-Godinez, Jorge},
  journal = {IEEE Embedded Systems Letters (ESL)},
  publisher = {IEEE},
  title = {{Automatic Generation of Matrix Multiply-Add Architectures using High-Level Synthesis [Under review]}},
  year = {2022}
}

% Automating the PE generation for GEMMA and Convolutions
@article{gemma_v1.0.0,
  author = {Leon-Vega, Luis G.,
            Salazar-Villalobos, Eduardo,
            Rodriguez-Figueroa, Alejandro,
            Castro-Godinez, Jorge},
  journal = {ACM Transactions on Embedded Computing Systems},
  publisher = {ACM},
  title = {{Automatic Generation of Resource and Accuracy Configurable Processing Elements for Deep CNNs}},
  year = {2022}
}

% Software-only
```bibtex
@software{salazar_villalobos_eduardo_v1_1_0,
author  = {Salazar-Villalobos, Eduardo,
           Leon-Vega, Luis G.
           Castro-Godinez, Jorge},
  title = {{Flexible Accelerator Library: Approximate Matrix Accelerator}},
  month = March,
  year = 2022,
  publisher = {Zenodo},
  version = {v1.1.0},
  doi = {10.5281/zenodo.6413238},
  url = {https://doi.org/10.5281/zenodo.6413238}
}
```

Author:

Eduardo Salazar Villalobos <eduarsalazar@estudiantec.cr>

Supervisor:

Luis G. Leon Vega <lleon95@estudiantec.cr>, <luis.leon@ieee.org>

This project has been

Aknowledgements:

This work was possible thanks to the Programmi Operativi Nazionali (PON) from Ministero dell'Università e della Ricerca, eXact Lab S.R.L, the postgraduate research scholarship from Instituto Tecnológico de Costa Rica, and the Master's scholarship programme from RidgeRun Embedded Solutions LLC.
