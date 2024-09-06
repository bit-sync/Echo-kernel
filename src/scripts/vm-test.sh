set -e

cd ~/Echo-kernel/src

echo starting vm

qemu-system-i386 -kernel ec-kernel

echo end