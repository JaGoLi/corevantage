# Corevantage
A graphical interface to set options on devices with coreboot firmware.<br/>
![alt text](https://github.com/JaGoLi/corevantage/raw/main/screenshots/corevantage-1.0.png)
## Introduction
This is a utility that allows users to view and modify coreboot settings usually accessed with `nvramtool` or `nvramcui`. Usage of the application is pretty straight-forward: once the settings have been modified, hit _Save_ and the user will be prompted to reboot the computer. The bios settings will then take effect on reboot. The code for the application has been designed with modularity in mind, in order to port it to many more devices supported by coreboot in the future. As of now, however, it has only been tested to work with the ThinkPad X200 running the latest version of libreboot that can be found at this git repository: https://github.com/JaGoLi/Libreboot-X200-Updated<br/><br/>
To get more information about the effects of any individual setting in the application, the user can access the _Information_ window under the _Help_ dropdown menu.
## Installation
IMPORTANT: To be able to run this application, the kernel parameter `iomem=relaxed` must be included in the bootloader configuration.<br/>
For grub, it must be in the `GRUB_CMDLINE_LINUX` parameter of the file `/etc/default/grub`. 
### Distribution-Specific Packages (Arch Linux, Ubuntu 20.04 and 20.10)
On Arch-based systems: the user can install the application using an aur helper such as `yay`:<br/>
`yay -S corevantage-x200`<br/><br/>
On Ubuntu-based systems: the user can add a ppa and install the application using `apt`:<br/>
`sudo add-apt-repository ppa:mordec13/corevantage`<br/>
`sudo apt update && sudo apt install corevantage-x200`
### Compilation from source
To compile and run this application, the user needs `cmake`, the basic qt5 development libraries, and `nvramtool`<br/>
First, the user needs to compile `nvramtool`:<br/>
`git clone http://review.coreboot.org/coreboot.git`<br/>
`cd coreboot/util/nvramtool`<br/>
`make -j$(nproc)`<br/>
`sudo make PREFIX=/usr install`<br/><br/>
Then compile Corevantage by doing as such:<br/>
`git clone https://github.com/JaGoLi/corevantage.git && cd corevantage`<br/>
`mkdir build && cd build`<br/>
`make -j$(nproc) x200`<br/>
`sudo make install`<br/>
## Donations
If you appreciate this work, and would like to see this application ported to more devices as well as the continued support of libreboot, feel free to donate at this link: [PayPal](https://www.paypal.com/donate/?hosted_button_id=2W3JGPJ5RKAAA)
