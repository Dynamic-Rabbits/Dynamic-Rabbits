# Dynamic Rabbits

This is the version used to conduct our experiments for the paper titled "The Taint Rabbit: Optimizing Generic Taint Analysis with Dynamic Fast Path Generation" and presented at AsiaCCS 2020.

We use a machine installed with 32-bit Ubuntu 14.04.6 We also tested on 16.04 LTS.

Dependencies:

```
sudo apt-get install build-essential git wget python cmake g++ g++-multilib libboost-dev \
                     libpython-dev zlib1g-dev libnuma-dev lsof \
                     libxml2-dev libtool imagemagick php
```

To build:

```
source set_paths.sh
./build_all.sh x86_32 Release
```

To test:

```
./run_tests.sh
```
