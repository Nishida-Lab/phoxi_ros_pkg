#!/bin/sh
echo "***************************************"
echo "*****      for PhoXi Control      *****"
echo "***************************************"
apt install wget
wget https://photoneo.com/files/installer/PhoXi/1.2.14/PhotoneoPhoXiControlInstaller-1.2.14-Ubuntu16-STABLE.tar
mount -o remount,rw /
tar xf PhotoneoPhoXiControlInstaller-1.2.14-Ubuntu16-STABLE.tar
./PhotoneoPhoXiControlInstaller-1.2.14-Ubuntu16-STABLE.run