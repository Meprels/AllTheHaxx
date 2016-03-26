#AllTheHaxx ~ [0x539]
CI Status: [![Circle CI](https://circleci.com/gh/AllTheHaxx/AllTheHaxx.svg?style=svg)](https://circleci.com/gh/AllTheHaxx/AllTheHaxx)
###AllTheHaxx. Guaranteed to be 420% verkeckt!
================================
Our own flavor of the popular [DDNet](https://github.com/ddnet/ddnet) client modification for the 2d shooter [teeworlds](http://teeworlds.com). Take a look at our [homepage](https:/AllTheHaxx.github.io/) for more information.

Development discussions happen on #AllTheHaxx on Quakenet ([»Webchat](http://webchat.quakenet.org/?channels=AllTheHaxx&uio=d4)).

You can get binary releases from [our website](https://AllTheHaxx.github.io/).

Building
--------

To compile AllTheHaxx yourself, you can follow the [instructions for compiling Teeworlds](https://www.teeworlds.com/?page=docs&wiki=compiling_everything).
Make sure you have all the requirements that are needed by DDNet Client (listed below)
*WINDOWS USERS:* if you should encounter any compiling problems, __please__ compile with MinGW!!

--------------------------
AllTheHaxx requires additional libraries, that are bundled for the most common platforms (Windows, Mac, Linux, all x86 and x86_64). Instead you can install these libraries on your system, remove the `config.lua` and `bam` should use the system-wide libraries by default. You can install all required dependencies on Debian and Ubuntu like this:

    apt-get install libsdl1.2-dev libfreetype6-dev libcurl4-openssl-dev libogg-dev libopus-dev libopusfile-dev

If you have the libraries installed, but still want to use the bundled ones instead, you can specify so by running `bam config curl.use_pkgconfig=false opus.use_pkgconfig=false opusfile.use_pkgconfig=false ogg.use_pkgconfig=false`.

The MySQL server is not included in the binary releases and can be built with `bam server_sql_release`. It requires `libmariadbclient-dev`, `libmysqlcppconn-dev` and `libboost-dev`, which are also bundled for the common platforms.

Note that the bundled MySQL libraries might not work properly on your system. If you run into connection problems with the MySQL server, for example that it connects as root while you chose another user, make sure to install your system libraries for the MySQL client and C++ connector. Make sure that `mysql.use_mysqlconfig` is set to `true` in your config.lua.

--------------------------

