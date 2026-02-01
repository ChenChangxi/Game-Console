#pragma once

#include "lfs.h"
#include "nor.h"

/* 文件参数 */
#define LFS_READ_SIZE   (PAGE)
#define LFS_PROG_SIZE   (PAGE)
#define LFS_BLOCK_SIZE  (SECTOR)
#define LFS_MEMAP_BASE  (QSPI_BASE)
#define LFS_CACHE_SIZE  (512u)
#define LFS_LOOK_AHEAD  (64u)
#define LFS_BLOCK_CYCS  (500u)
#define LFS_COMPACT_TH  (80u)
#define LFS_SIZE_BYTES  (24u * 1024u * 1024u)
#define LFS_BASE_OFFSET  (8u * 1024u * 1024u)

/* 格式化并挂载 */
void littlefs_init(void);