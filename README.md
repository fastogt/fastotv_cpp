# fastotv_protocol
Protocol for fastotv based players.

Build
========

Windows
-------
`cmake .. -GNinja -DCMAKE_BUILD_TYPE=RELEASE -DCMAKE_INSTALL_PREFIX=/mingw64`<br>
`cmake .. -GNinja -DCMAKE_BUILD_TYPE=RELEASE -DCMAKE_INSTALL_PREFIX=/mingw32`

Linux, FreeBSD, MacOS X
-------
`cmake .. -GNinja -DCMAKE_BUILD_TYPE=RELEASE -DCMAKE_INSTALL_PREFIX=/usr/local`

License
=======

Copyright (c) 2014-2022 FastoGT (https://fastogt.com)

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License version 3 as 
published by the Free Software Foundation.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program. If not, see <http://www.gnu.org/licenses/>.

Style
=======
.clang_format
mkdir build_cmake_style
cd build_cmake_style
cmake .. -DDEVELOPER_CHECK_STYLE=ON
make check_style

**Note: need clang-tidy and clang-format**
