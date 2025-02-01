#pragma once

// 1. 复制一份 errnum，避免副作用
// 2. (void)errnum; 防止编译器警告
// 3. Release 模式可被优化，零开销

#define ZCHECK(ret)                 \
  ({                                \
    __typeof__(ret) errnum = (ret); \
    assert(errnum == 0);            \
    (void)errnum;                   \
  })