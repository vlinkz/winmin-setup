project('winmin-setup', 'c')

deps = [
  dependency('gio-2.0', version: '>= 2.50'),
  dependency('gtk+-3.0', version: '>= 3.22'),
  dependency('spice-client-gtk-3.0'),
  dependency('python3-embed'),
]

executable('winmin-setup', 'winmin-setup.c',
  dependencies: deps,
  install: true, install_dir : '/usr/bin',
)
