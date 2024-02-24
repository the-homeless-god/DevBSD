DevBSD
======

DevBSD (`Developer BSD` or `Devil BSD` or `Digitable EVil BSD`) is a free, fast, secure, and highly portable Unix-like Open
Source operating system.  It is available for a [wide range of
platforms](https://wiki.NetBSD.org/ports/), from large-scale servers
and powerful desktop systems to handheld and embedded devices.

Shortly, it's just extender of NetBSD to provide a good desktop platform for daily development.

Building
--------

You can cross-build DevBSD from most UNIX-like operating systems.
To build for amd64 (x86_64), in the src directory:

    ./build.sh -U -u -j4 -m amd64 -O ~/obj release

Additional build information available in the [BUILDING](BUILDING) file.

Testing
-------

On a running NetBSD system:

    cd /usr/tests; atf-run | atf-report
