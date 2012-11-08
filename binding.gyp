{
  "targets": [
{
  'target_name': 'async',
  'type': 'executable',
  'sources': [
    'async_tcp_server.cc',
  ],
  'conditions': [
    ['OS=="mac"', {
      'include_dirs': [
        '/usr/local/include',
      ],
      'libraries': [
        '-lboost_system-mt',
      ],
      'library_dirs': [
        '/usr/local/lib',
      ],
      'xcode_settings': {
        'GCC_ENABLE_CPP_RTTI': 'YES'
      }
    }
    ],
    ['OS=="freebsd"', {
      'include_dirs': [
        '/usr/local/include',
      ],
      'libraries': [
        '-lboost_system',
      ],
      'library_dirs': [
        '/usr/local/lib',
      ],
    }
    ]
  ],
  'test': 0,
},
{
  'target_name': 'client',
  'type': 'executable',
  'sources': [
    'test/async_tcp_blocking_client.cc',
  ],
  'conditions': [
    ['OS=="mac"', {
      'include_dirs': [
        '/usr/local/include',
      ],
      'libraries': [
        '-lboost_system-mt',
      ],
      'library_dirs': [
        '/usr/local/lib',
      ],
      'xcode_settings': {
        'GCC_ENABLE_CPP_RTTI': 'YES'
      }
    }
    ],
    ['OS=="freebsd"', {
      'include_dirs': [
        '/usr/local/include',
      ],
      'libraries': [
        '-lboost_system',
      ],
      'library_dirs': [
        '/usr/local/lib',
      ],
    }
    ]
  ],
  'test': 0,
}
]
}
