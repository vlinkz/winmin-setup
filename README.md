# Winmin Setup

Winmin Setup is an GTK application that uses the [SPICE protocol](https://www.spice-space.org/) and Python to guide a user through installing a [libvirt](https://libvirt.org/) virtual machine as a base for Winmin.

# Build Dependencies
## winmin-setup
- libspice-client-gtk-3.0-dev
- libspice-client-glib-2.0-dev
- libgtk-3-dev
- libvirt-dev
- meson
## pywinminsetup
- python3

# Building
## winmin-setup
Build and install with:

```
$ meson build
$ ninja -C build install
```
## pywinminsetup
Build and install with:
```
$ sudo python3 setup.py install
```

# Runtime Dependencies

- spice-client-gtk
- libvirt-clients

# Running

In order for this program to access the spice socket of the guest VM, the user must be part of the `kvm` group. This can be added using the following command.
```
$ sudo usermod -aG $USER kvm
```
In order to properly setup Winmin for useage and application installation, the user must be part of the group `tty`. This can be added using the following command.
```
$ sudo usermod -aG $USER tty
```

You may need to logout or reboot in order for group changes to take effect.

### Usage
```
winmin-setup
```
# TODO
- Fix loading screen using threads. Currently the window freezes when downloading the virtio guest iso 
- Add spice window resizing (see [winmin-viewer](https://github.com/vlinkz/winmin-viewer) for reference)
- Use libvirt API for managing virtual machines instead of high-level python commands
- Add image references in the instructions
- Add audio input support