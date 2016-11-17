#!/bin/sh

if sudo [ -w /etc/udev/rules.d ]; then
    echo "Copying Explore M3-specific udev rules..."
    sudo cp -v 90-explore-m3.rules /etc/udev/rules.d/90-explore-m3.rules
    sudo chown root:root /etc/udev/rules.d/90-explore-m3.rules
    sudo chmod 644 /etc/udev/rules.d/90-explore-m3.rules
    sudo chmod 777 exploreM3_upload
    sudo chmod 777 upload_reset
    sudo chmod 777 dfu	
    echo "Reloading udev rules"
    sudo udevadm control --reload-rules
    echo "Adding current user to dialout group"
    sudo adduser $USER dialout
else
    echo "Couldn't copy to /etc/udev/rules.d/; you probably have to run this script as root? Or your distribution of Linux doesn't include udev; try running the IDE itself as root."
fi

