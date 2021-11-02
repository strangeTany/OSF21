sudo chmod 777 lofsdisk/ 
cd lofsdisk/

sudo touch file1
sudo touch file2
sudo chmod 777 file1
sudo chmod 777 file2  
sudo echo "Tatiana" > file1
sudo echo "Ivshina" > file2

gcc ex2.c -o ex2.out
cp -v ex2.out $chr/ex2.out

cp -v ex2.out $chr/ex2.out

mkdir $chr/usr
mkdir $chr/usr/lib
mkdir $chr/usr/lib64
cp -v /usr/lib/libreadline.so.8 $chr/usr/lib
cp -v /usr/lib/libdl.so.2 $chr/usr/lib
cp -v /usr/lib/libc.so.6 $chr/usr/lib
cp -v /usr/lib/libncursesw.so.6 $chr/usr/lib
cp -v /usr/lib64/ld-linux-x86-64.so.2 $chr/usr/lib64
cp -v /usr/lib/libcap.so.2 $chr/usr/lib

chroot . ./ex2.out > ../ex2.txt