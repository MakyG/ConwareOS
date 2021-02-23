
GCCPARAMS = -m32 -Iinclude -fno-use-cxa-atexit -nostdlib -fno-builtin -fno-rtti -fno-exceptions -fno-leading-underscore -Wno-write-strings -fno-stack-protector
# přídavné parametry
# 3. správa paměti
# 8. názvy sekcí .o souboru, loader.s by nemohl zavolat kernelMain (muselo by být _kernelMain)
ASPARAMS = --32
LDPARAMS = -melf_i386

objects = obj/loader.o \
	obj/gdt.o \
	obj/drivers/driver.o \
	obj/HWcommunication/port.o \
	obj/HWcommunication/interruptstubs.o \
	obj/HWcommunication/interrupts.o \
	obj/HWcommunication/pci.o \
	obj/drivers/keyboard.o \
	obj/drivers/mouse.o \
	obj/kernel.o \

run: mykernel.iso
	(killall VirtualBox && sleep 1) || true
	VirtualBox --startvm "Conware OS" &

obj/%.o: src/%.cpp
	mkdir -p $(@D)
	g++ $(GCCPARAMS) -c -o $@ $<

obj/%.o: src/%.s
	mkdir -p $(@D)
	as $(ASPARAMS) -o $@ $<

mykernel.bin: linker.ld $(objects)
	ld $(LDPARAMS) -T $< -o $@ $(objects)

mykernel.iso: mykernel.bin
	mkdir iso
	mkdir iso/boot
	mkdir iso/boot/grub
	cp $< iso/boot/
	echo 'set timeout=0' >> iso/boot/grub/grub.cfg
	echo 'set default=0' >> iso/boot/grub/grub.cfg
	echo '' >> iso/boot/grub/grub.cfg
	echo 'menuentry "Conware Operating System" {' >> iso/boot/grub/grub.cfg
	echo '	multiboot /boot/mykernel.bin' >> iso/boot/grub/grub.cfg
	echo '	boot' >> iso/boot/grub/grub.cfg
	echo '}' >> iso/boot/grub/grub.cfg
	grub-mkrescue --output=$@ iso
	rm -rf iso

install: mykernel.bin
	sudo cp $< /boot/mykernel.bin

.PHONY: clean
clean:
	rm -rf obj mykernel.bin mykernel.iso
