# SplitWebP

A command line tool that helps in splitting webp animation into images

<br/>
<div align="center">
    <img src="./assets/splitwebp_logo.png" alt="splitwebp">
</div>
<hr>

![Build Status](https://github.com/Razdeep/splitwebp/workflows/CMake/badge.svg)
![Issues](https://img.shields.io/github/license/Razdeep/splitwebp?style=plastic)
![Build Status](https://img.shields.io/github/stars/Razdeep/splitwebp?style=plastic)
![Issues](https://img.shields.io/github/issues/Razdeep/splitwebp?style=plastic)

## Dependencies
 - g++
 - cmake
 - OpenCV 3
 - libwebp

## Building & Installing from source
 - Open terminal and navigate to your working directory.
 - Run the following commands
 ```bash
 $ git clone https://github.com/Razdeep/splitwebp.git
 $ cd splitwebp
 $ mkdir build && cd build
 $ cmake .. && cmake --build .
 $ sudo make install
 ```

## License

MIT License

Copyright (c) 2020 Rajdeep Roy Chowdhury

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
