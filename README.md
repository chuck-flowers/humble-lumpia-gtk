# humble-lumpia-gtk

This is meant to be a simple GUI front-end to my project
[humple-lumpia](https://github.com/chuck-flowers/humble-lumpia).

### Installation

Currently I support the following installation methods:
- [Install From Source](#install-from-source)

#### Install From Source

##### Dependencies

To install from source, ensure that the following software packages are
installed on your system:

- gcc
- gtk4
- make

##### Commands

Clone the repository and enter the root directory of the repository. Then, run
the following command to install `humble-lumpia-gtk` globally on your system:

```bash
make install
```

If instead you only want to install humble-lumpia for your current user, run
the following command:

```bash
PREFIX="$HOME/.local" make install
```

