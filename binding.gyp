{
  "targets": [
{
  'target_name': 'async',
  'type': 'executable',
  'cflags_cc!': [ '-fno-rtti','-fexceptions' ],
  'cflags_cc+': ['-frtti', '-fexceptions'],
  'defines': [
    'NDEBUG',
    'USE_THREADS',
    'EXPERIMENT=1',
  ],
  'sources': [
    'async_tcp_server.cc',
    'snmptrap.cc',
    'tlv.cc',
  ],
  'conditions': [
    ['OS=="mac"', {
      'include_dirs': [
        '/usr/local/include',
        './',
      ],
      'libraries': [
        '-lboost_system-mt',
        '-lnetsnmp',
        '-lnetsnmpagent',
        '-lnetsnmphelpers',
        '-lnetsnmpmibs',
        '-lnetsnmptrapd',
      ],
      'library_dirs': [
        '/usr/local/lib',
      ],
      'xcode_settings': {
        'GCC_ENABLE_CPP_RTTI': 'YES',
        'GCC_ENABLE_CPP_EXCEPTIONS': 'YES'
      }
    }
    ],
    ['OS=="linux" or OS=="freebsd"', {
      'include_dirs': [
        '/usr/local/include',
      ],
      'libraries': [
        '-lboost_system',
        '-lnetsnmp',
        '-lnetsnmpagent',
        '-lnetsnmphelpers',
        '-lnetsnmpmibs',
        '-lnetsnmptrapd',
      ],
      'library_dirs': [
        '/usr/local/lib',
      ],
    }
    ],
    ['OS=="win"', {
      'include_dirs': [
        '/usr/local/include',
      ],
      'libraries': [
        '-lboost_system',
        '-lnetsnmp',
        '-lnetsnmpagent',
        '-lnetsnmphelpers',
        '-lnetsnmpmibs',
        '-lnetsnmptrapd',
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
    ['OS=="linux" or OS=="freebsd"', {
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
  'target_name': 'snmptrap_simple',
  'type': 'executable',
  'sources': [
    'test/snmptrap_simple.c',
  ],
  'conditions': [
    ['OS=="mac"', {
      'include_dirs': [
        '/usr/local/include',
      ],
      'libraries': [
        '-lboost_system-mt',
        '-lnetsnmp',
        '-lnetsnmpagent',
        '-lnetsnmphelpers',
        '-lnetsnmpmibs',
        '-lnetsnmptrapd',
      ],
      'library_dirs': [
        '/usr/local/lib',
      ],
      'xcode_settings': {
        'GCC_ENABLE_CPP_RTTI': 'YES'
      }
    }
    ],
    ['OS=="linux" or OS=="freebsd"', {
      'include_dirs': [
        '/usr/local/include',
      ],
      'libraries': [
        '-lboost_system',
        '-lnetsnmp',
        '-lnetsnmpagent',
        '-lnetsnmphelpers',
        '-lnetsnmpmibs',
        '-lnetsnmptrapd',
      ],
      'library_dirs': [
        '/usr/local/lib',
      ],
    }
    ]
  ],
  'test': 0,
},
]
}
