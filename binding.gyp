{
  "targets": [
{
  'target_name': 'async',
  'type': 'executable',
  'variables' : {
   'target_arch' : 'x64',
   'host_arch' : 'x86_64',
   'arch' : 'x64',
   'ARCHS' : ['x86_64'],
  },
  'sources': [
    'async_tcp_server.cc',
  ],
  'include_dirs': [
    '/usr/local/include',
  ],
  'link_settings': {
    'libraries': [
      '-lm',
      '-lboost_system-mt',
    ],
    'library_dirs': [
      '/usr/local/lib',
    ],
  },
  'test': 0,
}
]
}
