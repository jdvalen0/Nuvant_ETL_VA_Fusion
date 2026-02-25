This software depends on the following third party software packages:

Package                 License                         Description        Internet
-----------------------------------------------------------------------===================================---------------
GenICam GenApi v3       GenICam license                 ./GenICam/         http://www.emva.org/standards-technology/genicam/
libusb-1.0.23           LGPL v2.1                       ./libusb/          http://libusb.info
libpng-*                libpng license                  ./libpng/          http://www.libpng.org/
libjpeg-turbo-*         BSD-style open source licenses  ./libjpeg-turbo/   http://www.libjpeg-turbo.org/
Qt-*                    LGPL v3                         ./lgpl-3.0.txt     https://www.qt.io/

Notes:
- libpng-*, libjpeg-turbo-*, Qt-* are the default packages from the Linux OS distribution.
  If not found, these packages will be installed by installation script.
- In case of Ubuntu 16.04 (NVidia Tegra Aarch64 TX Nano):
    libpng16-0:arm64 1.6.34-1ubuntu0.18.04.2
    libturbojpeg:arm64 1.5.2-0ubuntu5.18.04.1
    qt5-default:arm64 and libraries 5.9.5+dfsg-0ubuntu2
