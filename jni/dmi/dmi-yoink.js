const base = Process.enumerateModules()[0].base;

const yoinkModule = Module.load("/tmp/libyoink.so");
const yoinkOpen = new NativeFunction(
  yoinkModule.getExportByName("yoink_open"),
  "void",
  []
);
const yoinkClose = new NativeFunction(
  yoinkModule.getExportByName("yoink_close"),
  "void",
  []
);
const yoinkDo = new NativeFunction(
  yoinkModule.getExportByName("yoink_do"),
  "void",
  ["int", "pointer"]
);
const yoinkFrame = new NativeFunction(
  yoinkModule.getExportByName("yoink_frame"),
  "void",
  ["pointer", "size_t", "uint8", "uint8", "uint32"]
);

// Silence logs.
// const libduml_util = Process.getModuleByName("libduml_util.so");
// const duss_log_gen_head = libduml_util.getExportByName("duss_log_gen_head");
// Interceptor.attach(duss_log_gen_head, {
//   onLeave(retval) {
//     retval.replace(0);
//   },
// });

const gs_player_open = new NativePointer(base.add(0x2fa68 + 1));
Interceptor.attach(gs_player_open, {
  onEnter(args) {
    console.log("gs_player_open");
    yoinkClose();
    yoinkOpen();
  },
});

const cp_vdec_queue_frame = new NativePointer(base.add(0x00009268 + 1));
Interceptor.attach(cp_vdec_queue_frame, {
  onEnter(args) {
    const buf = args[1];
    const len = args[2].toInt32();
    const key = args[3].toInt32();
    const eos = args[4].toInt32();
    const pts1 = args[5].toInt32();
    const pts2 = args[6].toInt32();

    yoinkFrame(buf, len, key, eos, pts2);
  },
});

const ioctl = Module.findExportByName(null, "ioctl");
Interceptor.attach(ioctl, {
  onEnter(args) {
    const fd = args[0].toInt32();
    const request = args[1].toInt32();
    const pkt = args[2];

    if (request == 0x400c4206) {
      // yoinkDo(fd, pkt);
    }
  },
});
