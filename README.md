# Approximate Vector Accelerator

## Software version

### Compiling

For compiling the code, no-dependencies are needed so far. You may only need the `meson` building system. Please, follow these steps to get it into your system:

```bash
sudo apt update
sudo apt install python3 python3-pip ninja-build
sudo pip3 install meson
sudo apt install openmpi-common libopenmpi2 or libopenmpi-dev
pip3 install matplotlib numpy
```

After installing the building system, compile the code:

```bash
meson builddir
ninja -C builddir
```

### Testing

You can test the code by using:

```bash
cd builddir/tests/sw-ops
./matadd # For addition
./matmul # For multiplication
./matmac # For multiply-add
./matfma # For fused multiply-add
```

## Hardware version

For the hardware version, you will need Vivado HLS 2018.2.

You can run the tests in the following way:

```bash
# Run a synthesis + simulation
cd tests/hw-ops/
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

* TEST: name of the tests. Please, inspect `tests/hw-ops/tops/*.cpp` for the possible tests. You can also use `make help`.
* Q_kRows: Number of rows. Default: 12
* Q_kCols: Number of columns. Default: 12
* Q_kSeed: Seed for generating random numbers. Default: 10
* Q_USE_HLS_MATH: enables the hls math library. Default: 1
* SYN_TOOL: name of the synthesis tool. By default, it is `vivado_hls`

> If something fails and it is related to `vivado_hls not found`, please, make sure of having it in the environment. Usually, it requires:
> `source /opt/Xilinx/Vivado/2018.2/settings64.sh`

## Important data

After the extraction, the relevant files are:

```
test/hw-ops/measurements/
  |_ *-report.data      -> Report about latency and resources
  |_ *-maxerrs_*.data   -> Report about the maximum error reported
```

Author:

Eduardo Salazar Villalobos <eduarsalazar@estudiantec.cr>

Supervisor:

Luis G. Leon Vega <lleon95@estudiantec.cr>
