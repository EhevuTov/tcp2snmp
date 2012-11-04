{
  "targets": [
{
  'target_name': 'async',
  'type': 'executable',
  'cflags_cc!': [ '-fno-rtti' ],
  'defines': [
    'NDEBUG',
    'USE_THREADS',
    'EXPERIMENT=1',
  ],
  'sources': [
    'async_tcp_server.cc',
  ],
  'include_dirs': [
    '/usr/local/include',
  ],
  'link_settings': {
    'libraries': [
      '-lm',
      '-lboost_system',
    ],
    'library_dirs': [
      '/usr/local/lib',
    ],
  },
  'test': 0,
}
]
}
