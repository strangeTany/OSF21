fallocate -l 50M lofs.img
losetup -f lofs.img
mkfs.ext4 $(losetup -a | grep 'lofs.img' | awk '{print $1}' | cut -d ':' -f 1)
mkdir endpoint
mount $(losetup -a | grep 'lofs.img' | awk '{print $1}' | cut -d ':' -f 1) ./endpoint
cd endpoint