Nano _ex3.txt
chmod +x _ex3.txt >>ex3.txt
ls -l _ex3.txt
chmod -x _ex3.txt >>ex3.txt
ls -l _ex3.txt >> ex3.txt
chmod u+rwx _ex3.txt >>ex3.txt
chmod o+rwx _ex3.txt >>ex3.txt
ls -l _ex3.txt >> ex3.txt
chmod g+rwx _ex3.txt >>ex3.txt
ls -l _ex3.txt >> ex3.txt
echo "User and group can read and write" >> ex3.txt
echo "User and group have all permissions, others can read and execute" >> ex3.txt
echo "Anyone have all permissions" >> ex3.txt
echo "Everyone has all permissions" >> ex3.txt
