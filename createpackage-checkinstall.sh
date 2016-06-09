#!/bin/bash
cd ./libgenerator && sudo make clean
sudo checkinstall --requires "libc6" --pkgversion "20160609.1" --pkgrelease "1" --pkglicense "Proprietary" --nodoc -y
cd ../generator && sudo make clean
sudo checkinstall --requires "libgenerator" --pkgversion "20160609.1" --pkgrelease "1" --pkglicense "Proprietary" --nodoc -y
cd ../
mv ./libgenerator/*.deb ./
mv ./generator/*.deb ./
