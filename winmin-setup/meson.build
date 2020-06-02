project('winmin-setup', 'c')

deps = [
  dependency('gio-2.0', version: '>= 2.50'),
  dependency('gtk+-3.0', version: '>= 3.22'),
  dependency('spice-client-gtk-3.0'),
  dependency('python3-embed'),
]

gnome = import('gnome')

sources = gnome.compile_resources('setup-resources',
  'winmin-setup.gresource.xml',
  c_name: 'resources'
)


executable('winmin-setup', 'winmin-setup.c', sources,
  dependencies: deps,
  install: true, #install_dir : '/usr/bin',
  link_args : '-rdynamic',
)

