TODO: Add the instructions to the setup tutorial.

This is a notes file, do not bother reading it! 


1. Give executable permissions for the install.sh file.
2. Run install.sh from the tools directory.
3. hit ./install.sh from the terimal to execute the command. This will copy the dev rules to enable USB access for Explore M3

//Linux 64 bit error resolution:

https://hackaday.io/project/9064/instructions

If you receive this error on Linux, ".../Arduino/hardware/Arduino_STM32-master/tools/linux/stm32flash/stm32flash: No such file or directory" while trying to upload it is likely due to missing 32-bit libraries.

To fix on Ubuntu, i386 support needs to be installed for several libraries:

sudo dpkg --add-architecture i386
sudo apt-get update
sudo apt-get install libc6:i386 libncurses5:i386 libstdc++6:i386
