#!/usr/bin/env python3
import os,subprocess,sys
import urllib.request

def createvm(path):
    subprocess.call("virt-install --virt-type=kvm --name=winmin-base --ram 4096 --vcpus 4 --hvm --network network=default,model=virtio --graphics spice,listen=socket --disk /var/lib/libvirt/images/winmin-base.img,size=50,bus=virtio,cache=none,io=native,format=raw --cdrom {} --disk /tmp/virtio-win.iso,device=cdrom --video qxl --noautoconsole --os-variant win10 ".format(path),shell=True)
    dump = subprocess.check_output("virsh dumpxml winmin-base",shell=True).decode("utf-8").split("'")
    print("Finding SPICE socket")
    for i in range(len(dump)):
        if "spice.sock" in dump[i]:
            sock="spice+unix://{}".format(dump[i])
            print(sock)
            break
    return sock

def call(input):
    if not os.path.isfile ("/tmp/virtio-win.iso"):
        urllib.request.urlretrieve('https://fedorapeople.org/groups/virt/virtio-win/direct-downloads/latest-virtio/virtio-win.iso', '/tmp/virtio-win.iso')
    sock = createvm(input)
    return sock

def boot():
    subprocess.call("virsh start winmin-base",shell=True)
    dump = subprocess.check_output("virsh dumpxml winmin-base",shell=True).decode("utf-8").split("'")
    print("Finding SPICE socket")
    for i in range(len(dump)):
        if "spice.sock" in dump[i]:
            sock="spice+unix://{}".format(dump[i])
            print(sock)
            break
    return sock

def done():
    subprocess.call("virsh shutdown winmin-base",shell=True);
