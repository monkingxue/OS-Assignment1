{
  "targets": [
    {
      "target_name": "addon",
      "sources": [
        "p_to_c.cc",
        "../os/scheduler.cc",
        "../os/yoroutine.cc",
      ],
      "cflags!": ["-fno-exceptions"],
      "cflags_cc!": ["-fno-exceptions"],
      "conditions": [
        ["OS=='mac'", {
          "xcode_settings": {
            "GCC_ENABLE_CPP_EXCEPTIONS": "YES"
          }
        }]
      ]
    }
  ]
}