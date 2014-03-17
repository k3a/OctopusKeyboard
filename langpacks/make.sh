sudo vim layout/DEBIAN/control
sudo cp -R layout layout_out
sudo find layout_out -name "._*" -exec rm -rf {} \;
sudo find layout_out -name ".DS_Store" -exec rm -rf {} \;
sudo find layout_out -name ".svn" -exec rm -rf {} \;
sudo chown -R 501 layout_out
dpkg-deb -b layout_out $1.deb
sudo rm -rf layout_out
