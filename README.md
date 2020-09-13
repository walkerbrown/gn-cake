# gn-cake
Trying out Google's GN build system for Fuchsia

## Build GN from source
Prerequisites
```
brew install ninja
```
Clone GN and build
```
git clone https://gn.googlesource.com/gn
python build/gen.py
ninja -C out
```
Run tests (optional)
```
out/gn_unittests
```
Finally, add the `gn` executable to your path
```
~/gn/out/gn
```

## Setup the `BUILDCONFIG.gn` and `BUILD.gn` directory structure
A single `.gn` file is required at the project root. Each `BUILD.gn` specifies source files and targets. 
```
.
├── .gn
├── BUILD.gn
├── LICENSE
├── build
│   ├── BUILD.gn
│   ├── BUILDCONFIG.gn
│   └── toolchain
│       └── BUILD.gn
└── src
    └── hello_world
        ├── BUILD.gn
        └── hello_world.cc
```

## Generate build directory
```
gn gen out
ninja -C out
```

Run the executable
```
out/<exe>
```

To clean out the build
```
gn clean out
```

Other useful tools
```
gn desc <out_dir> <//fully_qualified/path/to:target> [<property to display>]
gn desc out //src/hello_world:hello_world cflags --blame
gn help labels
gn help configs
```
