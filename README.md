# flase (Sheep 'n' Dogs)
Agent based simulation of a collector and item model with diffusive items in 2D. 
Features normal Brownian motion and random movement with constant velocity.

It creates a GNUplot script for visualization. Output using open GL is
in beta stage.

## Installation (Linux / Mac)

Download source code.

Create build directory in Project folder and move into.

Extract to {YOUR_PATH}

`cd {YOUR_PATH}/flase`

`mkdir -p build`

`cd build`

`cmake ..`

`make`


## Usage

Run `sheepndogs` executable.

The data will be written to `flase/build/temp` and the gnuplot script to `flase/build/havefun.gp`.
 
Run the script using the terminal via `gnuplot havefun.gp`. (needs wxt support)

Use `sheepndogs --help` for a list of adjustable parameters.

Check the physics document if the meaning of parameters is unclear and for general background information.

## Physics

[See this part of my master thesis](https://gitlab.gwdg.de/MSc/flase/uploads/88b35ae75e67d10dbd5a0e76ca3cf737/physics.pdf)


## Credits

This program was built during my masters at Humboldt University Berlin.
Special thanks to Prof. Schimansky-Geier and Jörg Bachmann.

The kdtree used is by Martin F. Krafft and also hosted at https://anonscm.debian.org/cgit/libkdtree/libkdtree.git/

## License

see LICENSE.md
