#include "lfs_port.h"

static lfs_t lfs;
static struct lfs_config cfg;
static volatile uint8_t unmap;

void littlefs_init(void) {

    cfg.read  = lfs_nor_read;
    cfg.prog  = lfs_nor_write;
    cfg.erase = lfs_nor_erase;
    cfg.sync  = lfs_nor_sync;

    cfg.read_size      = LFS_READ_SIZE;
    cfg.prog_size      = LFS_PROG_SIZE;
    cfg.block_size     = LFS_BLOCK_SIZE;
    cfg.block_count    = LFS_SIZE_BYTES / LFS_BLOCK_SIZE;
    cfg.cache_size     = LFS_CACHE_SIZE;    /* 工作缓存 */
    cfg.lookahead_size = LFS_LOOK_AHEAD;    /* 位图大小 */
    cfg.block_cycles   = LFS_BLOCK_CYCS;    /* 磨损均衡 */
    cfg.compact_thresh = LFS_COMPACT_TH;    /* 压缩回收 */

    int unmount = lfs_mount(&lfs, &cfg);
    if (unmount) {lfs_format(&lfs, &cfg);lfs_mount(&lfs, &cfg);}
}

static inline uint32_t lfs_nor_addr(const struct lfs_config *c,
                                    lfs_block_t block, lfs_off_t off) {
    (void)c;
    return LFS_BASE_OFFSET + (uint32_t)block * LFS_BLOCK_SIZE + (uint32_t)off;
}

static int lfs_nor_read(const struct lfs_config *c, lfs_block_t block,
                        lfs_off_t off, void *buffer, lfs_size_t size) {

    uint32_t nor_adr = lfs_nor_addr(c, block, off);
    nor_read(nor_adr + LFS_MEMAP_BASE, (uint8_t *)buffer, (uint32_t)size);
    return 0;            
}

static int lfs_nor_write(const struct lfs_config *c, lfs_block_t block,
                         lfs_off_t off, const void *buffer, lfs_size_t size) {

    if (!unmap) {spi_indirect();unmap = 1;}
    uint32_t nor_adr = lfs_nor_addr(c, block, off);
    nor_page_write(nor_adr, (uint8_t *)buffer, (uint32_t)size);
    return 0;
}

static int lfs_nor_erase(const struct lfs_config *c, lfs_block_t block) {

    if (!unmap) {spi_indirect();unmap = 1;}
    uint32_t nor_adr = lfs_nor_addr(c, block, 0);
    nor_erase(nor_adr);
    return 0;
}

static int lfs_nor_sync(const struct lfs_config *c) {

    (void)c;
    spi_memory_map(FastReadQuad);unmap = 0;
    return 0;
}