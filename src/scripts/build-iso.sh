set -e

echo making dirs

mkdir iso

mkdir iso/boot

mkdir iso/boot/grub

echo done

echo building kernel...

bash scripts/build.sh

echo done

echo copying files...

cp kernel iso/boot

cp ~/Echo-kernel/grub-config/grub.cfg iso/boot/grub 

echo done

echo creating ISO...

grub-mkrescue -o Echo-kernel-1.0.0.iso

grub-mkrescue -o Echo-kernel-1.0.0.iso iso

echo done

echo removing temporary iso folder...

rm -rf iso

echo done

echo ISO created successfully!

sleep 1