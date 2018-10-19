```
sudo apt-get update
sudo apt-get install build-essential git
mkdir rpi
cd rpi
git clone git://github.com/raspberrypi/tools.git
cd ~/rpi/tools/arm-bcm2708
```
In the arm-bcm2708 folder you'll see four other folders, each containing a separate toolchain:
 arm-bcm2708-linux-gnueabi
 arm-bcm2708hardfp-linux-gnueabi
 gcc-linaro-arm-linux-gnueabihf-raspbian
 gcc-linaro-arm-linux-gnueabihf-raspbian-x64
If you are running a 32-bit Linux operating system, you'll want to use the third toolchain 'gcc-linaro-arm-linux-gnueabihf-raspbian'. If however you are running a 64-bit Linux operating system, you'll want to use the fourth toolchain 'gcc-linaro-arm-linux-gnueabihf-raspbian-x64. If you don't know whether you are running  32-bit or a 64-bit version of Linux type in the command line :
```
uname -a
```

If you see something like 'i386'/'386' in the output string, then you're running a 32-bit version of Linux. If however you see 'x86_64' / 'amd64' in the output string, then you're running a 64-bit version of Linux.

The next step is to add the directory containing the binary files of the  toolchain  to the PATH environment variable in Linux. This way we can access the toolchain's binary files/tools from the command line. This step is not necessary if you want to using the toolchain strictly from Eclipse. I still do highly recommend that you do it, in case you decide to compile/debug  arm applications directly from the command line later on. We will do this by adding an "export PATH"  command to the bottom of the .bashrc  files in the home directory.

In a terminal window (on your Desktop Linux OS) type:
```
cd ~/
```
to point to the home directory, then type:
```
vi .bashrc
```
This will open the .bashrc file in a command line based editor called nano. Go to the bottom of the .bashrc file using the down arrow key. Then if you're running 32-bit Linux,  type the following command:
```
export PATH=$PATH:$HOME/rpi/tools/arm-bcm2708/gcc-linaro-arm-linux-gnueabihf-raspbian/bin
```
Alternatively if you're running 64-bit Linux, type the following command instead:
```
export PATH=$PATH:$HOME/rpi/tools/arm-bcm2708/gcc-linaro-arm-linux-gnueabihf-raspbian-x64/bin
```
Then hit Ctrl+x to exit. You will be prompted to save changes. Say yes and hit "Enter".
Then type in the command line:
```
source .bashrc
```
This allows the current open terminal to see the updated PATH variable. Alternatively one can  close the terminal and open a new one.

To test if you can access the cross compiling toolchain from the command line type:
arm-linux-gnueabihf-gcc -v
