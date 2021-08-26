sudo add-apt-repository "deb http://security.ubuntu.com/ubuntu xenial-security main"
sudo apt update
sudo apt upgrade
sudo apt install ubuntu-restricted-extras
sudo apt install build-essential cmake git pkg-config
sudo apt install libjpeg-dev libtiff5-dev libjasper-dev libpng-dev
sudo apt install libavcodec-dev libavformat-dev libswscale-dev
sudo apt install libdc1394-22-dev libxvidcore-dev libx264-dev x264
sudo apt install libxine2-dev libv4l-dev v4l-utils
sudo apt install libgstreamer1.0-dev libgstreamer-plugins-base1.0-dev
sudo apt install libgtk-3-dev
sudo apt install libatlas-base-dev libeigen3-dev gfortran
sudo apt install python3-dev python3-numpy libtbb2 libtbb-dev
cd ~
mkdir opencv
cd opencv
wget -O opencv-3.4.0.zip https://github.com/opencv/opencv/archive/3.4.0.zip
wget -O opencv_contrib-3.4.0.zip https://github.com/opencv/opencv_contrib/archive/3.4.0.zip
unzip opencv-3.4.0.zip
unzip opencv_contrib-3.4.0.zip
mkdir build && cd build
cmake \
-D CMAKE_BUILD_TYPE=Release \
-D CMAKE_INSTALL_PREFIX=/usr/local \
-D BUILD_WITH_DEBUG_INFO=OFF \
-D BUILD_EXAMPLES=ON \
-D BUILD_opencv_python2=OFF \
-D BUILD_opencv_python3=ON \
-D INSTALL_PYTHON_EXAMPLES=ON \
-D OPENCV_EXTRA_MODULES_PATH=../opencv_contrib-3.4.0/modules \
-D WITH_TBB=ON \
-D WITH_V4L=ON \
../opencv-3.4.0/ 2>&1 | tee cmake_messages.txt
nproc
make -j2 2>&1 | tee build_messages.txt
sudo make install
sudo ldconfig
pkg-config --modversion opencv
