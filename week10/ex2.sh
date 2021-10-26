mkdir week01
cd ~/week01
nano file.txt
cd ..
mkdir week10
cd ~/week10
link ../week01/file.txt _ex2.txt
INODENUMBER=$(ls -i _ex2.txt | cut -d' ' -f1)
{echo "$INODENUMBER" & find ~ -inum $INODENUMBER} >> ex2.txt
{echo -n "$INODENUMBER " & find ~ -inum $INODENUMBER} >> ex2.txt
