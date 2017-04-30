{
  "targets": [
    {
      "target_name": "addon",
      "sources": [
        "middleware/addon.cc",
        "middleware/wrapper.cc",
        "../os/yoroutine.cc",
        "../os/scheduler.cc"
      ],
      "cflags!": ["-fexceptions"],
      "cflags_cc!": ["-fexceptions"],
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