/**
 * OPEN SDD FrameWork
 *
 * @author L.Yang
 **/

#ifndef HW_PARA_H
#define HW_PARA_H

/* CPU */
#define CPU_NUM            8

/* DRAM */

/* SRAM */

/* NAND */
#define BANK_NUM           8
#define CHANCEL_NUM        8
#define PLANE_NUM          2
#define PER_BLOCK_WL_NUM   128
#define PER_PAGE_SIZE      (16*1024*8)

#define PER_SLC_BLOCK_SIZE PER_PAGE_SIZE*(PER_BLOCK_WL_NUM*1)
#define PER_MLC_BLOCK_SIZE PER_PAGE_SIZE*(PER_BLOCK_WL_NUM*2)
#define PER_TLC_BLOCK_SIZE PER_PAGE_SIZE*(PER_BLOCK_WL_NUM*3)

#endif /* HW_PARA_H */
