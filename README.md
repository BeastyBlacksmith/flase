# Sheep 'n' Dogs
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

`cd {YOUR_PATH}/flase/tex`

`latex physics`

`biber physics`

`latex physics`

View physics.pdf.

## Contributing

1. Fork it!
2. Create your feature branch: `git checkout -b my-new-feature`
3. Commit your changes: `git commit -am 'Add some feature'`
4. Push to the branch: `git push origin my-new-feature`
5. Submit a pull request :D

## History

TODO: Write history

## Credits

This program was built during my masters at Humboldt University Berlin.
Special thanks to Prof. Schimansky-Geier and Jörg Bachmann.

## License

see LICENSE.md