# Big Finish Audiobook Download

This project is a program to download audiobooks from [Big Finish Productions](https://www.bigfinish.com/).

The program is made in GTK, and is licenced under the MIT Licence

## Building
This project uses conan for packages, so you need to run the following to build

```bash
mkdir build
cd build
conan install .. --build missing
cmake .. -GNinja
ninja
```
