/*
 * Definitions for the NVM Express interface
 * Copyright (c) 2011-2014, Intel Corporation.
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms and conditions of the GNU General Public License,
 * version 2, as published by the Free Software Foundation.
 *
 * This program is distributed in the hope it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 * more details.
 */

#ifndef _LINUX_NVME_H
#define _LINUX_NVME_H

#if 0
#include <linux/types.h>
#include <linux/uuid.h>
#endif

#include <stdbool.h>

/* NQN names in commands fields specified one size */
#define NVMF_NQN_FIELD_LEN	256

/* However the max length of a qualified name is another size */
#define NVMF_NQN_SIZE		223

#define NVMF_TRSVCID_SIZE	32
#define NVMF_TRADDR_SIZE	256
#define NVMF_TSAS_SIZE		256

#define NVME_DISC_SUBSYS_NAME	"nqn.2014-08.org.nvmexpress.discovery"

#define NVME_RDMA_IP_PORT	4420

#define NVME_NSID_ALL		0xffffffff

enum nvme_subsys_type {
	NVME_NQN_DISC	= 1,		/* Discovery type target subsystem */
	NVME_NQN_NVME	= 2,		/* NVME type target subsystem */
};

/* Address Family codes for Discovery Log Page entry ADRFAM field */
enum {
	NVMF_ADDR_FAMILY_PCI	= 0,	/* PCIe */
	NVMF_ADDR_FAMILY_IP4	= 1,	/* IP4 */
	NVMF_ADDR_FAMILY_IP6	= 2,	/* IP6 */
	NVMF_ADDR_FAMILY_IB	= 3,	/* InfiniBand */
	NVMF_ADDR_FAMILY_FC	= 4,	/* Fibre Channel */
};

/* Transport Type codes for Discovery Log Page entry TRTYPE field */
enum {
	NVMF_TRTYPE_RDMA	= 1,	/* RDMA */
	NVMF_TRTYPE_FC		= 2,	/* Fibre Channel */
	NVMF_TRTYPE_LOOP	= 254,	/* Reserved for host usage */
	NVMF_TRTYPE_MAX,
};

/* Transport Requirements codes for Discovery Log Page entry TREQ field */
enum {
	NVMF_TREQ_NOT_SPECIFIED	= 0,	/* Not specified */
	NVMF_TREQ_REQUIRED	= 1,	/* Required */
	NVMF_TREQ_NOT_REQUIRED	= 2,	/* Not Required */
};

/* RDMA QP Service Type codes for Discovery Log Page entry TSAS
 * RDMA_QPTYPE field
 */
enum {
	NVMF_RDMA_QPTYPE_CONNECTED	= 1, /* Reliable Connected */
	NVMF_RDMA_QPTYPE_DATAGRAM	= 2, /* Reliable Datagram */
};

/* RDMA QP Service Type codes for Discovery Log Page entry TSAS
 * RDMA_QPTYPE field
 */
enum {
	NVMF_RDMA_PRTYPE_NOT_SPECIFIED	= 1, /* No Provider Specified */
	NVMF_RDMA_PRTYPE_IB		= 2, /* InfiniBand */
	NVMF_RDMA_PRTYPE_ROCE		= 3, /* InfiniBand RoCE */
	NVMF_RDMA_PRTYPE_ROCEV2		= 4, /* InfiniBand RoCEV2 */
	NVMF_RDMA_PRTYPE_IWARP		= 5, /* IWARP */
};

/* RDMA Connection Management Service Type codes for Discovery Log Page
 * entry TSAS RDMA_CMS field
 */
enum {
	NVMF_RDMA_CMS_RDMA_CM	= 1, /* Sockets based endpoint addressing */
};

#define NVME_AQ_DEPTH		32
#define NVME_NR_AEN_COMMANDS	1
#define NVME_AQ_BLK_MQ_DEPTH	(NVME_AQ_DEPTH - NVME_NR_AEN_COMMANDS)

/*
 * Subtract one to leave an empty queue entry for 'Full Queue' condition. See
 * NVM-Express 1.2 specification, section 4.1.2.
 */
#define NVME_AQ_MQ_TAG_DEPTH	(NVME_AQ_BLK_MQ_DEPTH - 1)

enum {
	NVME_REG_CAP	= 0x0000,	/* Controller Capabilities */
	NVME_REG_VS	= 0x0008,	/* Version */
	NVME_REG_INTMS	= 0x000c,	/* Interrupt Mask Set */
	NVME_REG_INTMC	= 0x0010,	/* Interrupt Mask Clear */
	NVME_REG_CC	= 0x0014,	/* Controller Configuration */
	NVME_REG_CSTS	= 0x001c,	/* Controller Status */
	NVME_REG_NSSR	= 0x0020,	/* NVM Subsystem Reset */
	NVME_REG_AQA	= 0x0024,	/* Admin Queue Attributes */
	NVME_REG_ASQ	= 0x0028,	/* Admin SQ Base Address */
	NVME_REG_ACQ	= 0x0030,	/* Admin CQ Base Address */
	NVME_REG_CMBLOC = 0x0038,	/* Controller Memory Buffer Location */
	NVME_REG_CMBSZ	= 0x003c,	/* Controller Memory Buffer Size */
	NVME_REG_DBS	= 0x1000,	/* SQ 0 Tail Doorbell */
};

#define NVME_CAP_MQES(cap)	((cap) & 0xffff)
#define NVME_CAP_TIMEOUT(cap)	(((cap) >> 24) & 0xff)
#define NVME_CAP_STRIDE(cap)	(((cap) >> 32) & 0xf)
#define NVME_CAP_NSSRC(cap)	(((cap) >> 36) & 0x1)
#define NVME_CAP_MPSMIN(cap)	(((cap) >> 48) & 0xf)
#define NVME_CAP_MPSMAX(cap)	(((cap) >> 52) & 0xf)

#define NVME_CMB_BIR(cmbloc)	((cmbloc) & 0x7)
#define NVME_CMB_OFST(cmbloc)	(((cmbloc) >> 12) & 0xfffff)
#define NVME_CMB_SZ(cmbsz)	(((cmbsz) >> 12) & 0xfffff)
#define NVME_CMB_SZU(cmbsz)	(((cmbsz) >> 8) & 0xf)

#define NVME_CMB_WDS(cmbsz)	((cmbsz) & 0x10)
#define NVME_CMB_RDS(cmbsz)	((cmbsz) & 0x8)
#define NVME_CMB_LISTS(cmbsz)	((cmbsz) & 0x4)
#define NVME_CMB_CQS(cmbsz)	((cmbsz) & 0x2)
#define NVME_CMB_SQS(cmbsz)	((cmbsz) & 0x1)

/*
 * Submission and Completion Queue Entry Sizes for the NVM command set.
 * (In bytes and specified as a power of two (2^n)).
 */
#define NVME_NVM_IOSQES		6
#define NVME_NVM_IOCQES		4

enum {
	NVME_CC_ENABLE		= 1 << 0,
	NVME_CC_CSS_NVM		= 0 << 4,
	NVME_CC_EN_SHIFT	= 0,
	NVME_CC_CSS_SHIFT	= 4,
	NVME_CC_MPS_SHIFT	= 7,
	NVME_CC_AMS_SHIFT	= 11,
	NVME_CC_SHN_SHIFT	= 14,
	NVME_CC_IOSQES_SHIFT	= 16,
	NVME_CC_IOCQES_SHIFT	= 20,
	NVME_CC_AMS_RR		= 0 << NVME_CC_AMS_SHIFT,
	NVME_CC_AMS_WRRU	= 1 << NVME_CC_AMS_SHIFT,
	NVME_CC_AMS_VS		= 7 << NVME_CC_AMS_SHIFT,
	NVME_CC_SHN_NONE	= 0 << NVME_CC_SHN_SHIFT,
	NVME_CC_SHN_NORMAL	= 1 << NVME_CC_SHN_SHIFT,
	NVME_CC_SHN_ABRUPT	= 2 << NVME_CC_SHN_SHIFT,
	NVME_CC_SHN_MASK	= 3 << NVME_CC_SHN_SHIFT,
	NVME_CC_IOSQES		= NVME_NVM_IOSQES << NVME_CC_IOSQES_SHIFT,
	NVME_CC_IOCQES		= NVME_NVM_IOCQES << NVME_CC_IOCQES_SHIFT,
	NVME_CSTS_RDY		= 1 << 0,
	NVME_CSTS_CFS		= 1 << 1,
	NVME_CSTS_NSSRO		= 1 << 4,
	NVME_CSTS_PP		= 1 << 5,
	NVME_CSTS_SHST_NORMAL	= 0 << 2,
	NVME_CSTS_SHST_OCCUR	= 1 << 2,
	NVME_CSTS_SHST_CMPLT	= 2 << 2,
	NVME_CSTS_SHST_MASK	= 3 << 2,
};

struct nvme_id_power_state {
	uint16_t			max_power;	/* centiwatts */
	uint8_t			rsvd2;
	uint8_t			flags;
	uint32_t			entry_lat;	/* microseconds */
	uint32_t			exit_lat;	/* microseconds */
	uint8_t			read_tput;
	uint8_t			read_lat;
	uint8_t			write_tput;
	uint8_t			write_lat;
	uint16_t			idle_power;
	uint8_t			idle_scale;
	uint8_t			rsvd19;
	uint16_t			active_power;
	uint8_t			active_work_scale;
	uint8_t			rsvd23[9];
};

enum {
	NVME_PS_FLAGS_MAX_POWER_SCALE	= 1 << 0,
	NVME_PS_FLAGS_NON_OP_STATE	= 1 << 1,
};

struct nvme_id_ctrl {
	uint16_t			vid;
	uint16_t			ssvid;
	char			sn[20];
	char			mn[40];
	char			fr[8];
	uint8_t			rab;
	uint8_t			ieee[3];
	uint8_t			cmic;
	uint8_t			mdts;
	uint16_t			cntlid;
	uint32_t			ver;
	uint32_t			rtd3r;
	uint32_t			rtd3e;
	uint32_t			oaes;
	uint32_t			ctratt;
	uint8_t			rsvd100[156];
	uint16_t			oacs;
	uint8_t			acl;
	uint8_t			aerl;
	uint8_t			frmw;
	uint8_t			lpa;
	uint8_t			elpe;
	uint8_t			npss;
	uint8_t			avscc;
	uint8_t			apsta;
	uint16_t			wctemp;
	uint16_t			cctemp;
	uint16_t			mtfa;
	uint32_t			hmpre;
	uint32_t			hmmin;
	uint8_t			tnvmcap[16];
	uint8_t			unvmcap[16];
	uint32_t			rpmbs;
	uint16_t			edstt;
	uint8_t			dsto;
	uint8_t			fwug;
	uint16_t			kas;
	uint16_t			hctma;
	uint16_t			mntmt;
	uint16_t			mxtmt;
	uint32_t			sanicap;
	uint32_t			hmminds;
	uint16_t			hmmaxd;
	uint8_t			rsvd338[174];
	uint8_t			sqes;
	uint8_t			cqes;
	uint16_t			maxcmd;
	uint32_t			nn;
	uint16_t			oncs;
	uint16_t			fuses;
	uint8_t			fna;
	uint8_t			vwc;
	uint16_t			awun;
	uint16_t			awupf;
	uint8_t			nvscc;
	uint8_t			rsvd531;
	uint16_t			acwu;
	uint8_t			rsvd534[2];
	uint32_t			sgls;
	uint8_t			rsvd540[228];
	char			subnqn[256];
	uint8_t			rsvd1024[768];
	uint32_t			ioccsz;
	uint32_t			iorcsz;
	uint16_t			icdoff;
	uint8_t			ctrattr;
	uint8_t			msdbd;
	uint8_t			rsvd1804[244];
	struct nvme_id_power_state	psd[32];
	uint8_t			vs[1024];
};

enum {
	NVME_CTRL_ONCS_COMPARE			= 1 << 0,
	NVME_CTRL_ONCS_WRITE_UNCORRECTABLE	= 1 << 1,
	NVME_CTRL_ONCS_DSM			= 1 << 2,
	NVME_CTRL_ONCS_WRITE_ZEROES		= 1 << 3,
	NVME_CTRL_ONCS_TIMESTAMP		= 1 << 6,
	NVME_CTRL_VWC_PRESENT			= 1 << 0,
	NVME_CTRL_OACS_SEC_SUPP                 = 1 << 0,
	NVME_CTRL_OACS_DIRECTIVES		= 1 << 5,
	NVME_CTRL_OACS_DBBUF_SUPP		= 1 << 8,
	NVME_CTRL_LPA_CMD_EFFECTS_LOG		= 1 << 1,
};

struct nvme_lbaf {
	uint16_t			ms;
	uint8_t			ds;
	uint8_t			rp;
};

struct nvme_id_ns {
	uint64_t			nsze;
	uint64_t			ncap;
	uint64_t			nuse;
	uint8_t			nsfeat;
	uint8_t			nlbaf;
	uint8_t			flbas;
	uint8_t			mc;
	uint8_t			dpc;
	uint8_t			dps;
	uint8_t			nmic;
	uint8_t			rescap;
	uint8_t			fpi;
	uint8_t			rsvd33;
	uint16_t			nawun;
	uint16_t			nawupf;
	uint16_t			nacwu;
	uint16_t			nabsn;
	uint16_t			nabo;
	uint16_t			nabspf;
	uint16_t			noiob;
	uint8_t			nvmcap[16];
	uint8_t			rsvd64[40];
	uint8_t			nguid[16];
	uint8_t			eui64[8];
	struct nvme_lbaf	lbaf[16];
	uint8_t			rsvd192[192];
	uint8_t			vs[3712];
};

enum {
	NVME_ID_CNS_NS			= 0x00,
	NVME_ID_CNS_CTRL		= 0x01,
	NVME_ID_CNS_NS_ACTIVE_LIST	= 0x02,
	NVME_ID_CNS_NS_DESC_LIST	= 0x03,
	NVME_ID_CNS_NS_PRESENT_LIST	= 0x10,
	NVME_ID_CNS_NS_PRESENT		= 0x11,
	NVME_ID_CNS_CTRL_NS_LIST	= 0x12,
	NVME_ID_CNS_CTRL_LIST		= 0x13,
};

enum {
	NVME_DIR_IDENTIFY		= 0x00,
	NVME_DIR_STREAMS		= 0x01,
	NVME_DIR_SND_ID_OP_ENABLE	= 0x01,
	NVME_DIR_SND_ST_OP_REL_ID	= 0x01,
	NVME_DIR_SND_ST_OP_REL_RSC	= 0x02,
	NVME_DIR_RCV_ID_OP_PARAM	= 0x01,
	NVME_DIR_RCV_ST_OP_PARAM	= 0x01,
	NVME_DIR_RCV_ST_OP_STATUS	= 0x02,
	NVME_DIR_RCV_ST_OP_RESOURCE	= 0x03,
	NVME_DIR_ENDIR			= 0x01,
};

enum {
	NVME_NS_FEAT_THIN	= 1 << 0,
	NVME_NS_FLBAS_LBA_MASK	= 0xf,
	NVME_NS_FLBAS_META_EXT	= 0x10,
	NVME_LBAF_RP_BEST	= 0,
	NVME_LBAF_RP_BETTER	= 1,
	NVME_LBAF_RP_GOOD	= 2,
	NVME_LBAF_RP_DEGRADED	= 3,
	NVME_NS_DPC_PI_LAST	= 1 << 4,
	NVME_NS_DPC_PI_FIRST	= 1 << 3,
	NVME_NS_DPC_PI_TYPE3	= 1 << 2,
	NVME_NS_DPC_PI_TYPE2	= 1 << 1,
	NVME_NS_DPC_PI_TYPE1	= 1 << 0,
	NVME_NS_DPS_PI_FIRST	= 1 << 3,
	NVME_NS_DPS_PI_MASK	= 0x7,
	NVME_NS_DPS_PI_TYPE1	= 1,
	NVME_NS_DPS_PI_TYPE2	= 2,
	NVME_NS_DPS_PI_TYPE3	= 3,
};

struct nvme_ns_id_desc {
	uint8_t nidt;
	uint8_t nidl;
	uint16_t reserved;
};

#define NVME_NIDT_EUI64_LEN	8
#define NVME_NIDT_NGUID_LEN	16
#define NVME_NIDT_UUID_LEN	16

enum {
	NVME_NIDT_EUI64		= 0x01,
	NVME_NIDT_NGUID		= 0x02,
	NVME_NIDT_UUID		= 0x03,
};

struct nvme_smart_log {
	uint8_t			critical_warning;
	uint8_t			temperature[2];
	uint8_t			avail_spare;
	uint8_t			spare_thresh;
	uint8_t			percent_used;
	uint8_t			rsvd6[26];
	uint8_t			data_units_read[16];
	uint8_t			data_units_written[16];
	uint8_t			host_reads[16];
	uint8_t			host_writes[16];
	uint8_t			ctrl_busy_time[16];
	uint8_t			power_cycles[16];
	uint8_t			power_on_hours[16];
	uint8_t			unsafe_shutdowns[16];
	uint8_t			media_errors[16];
	uint8_t			num_err_log_entries[16];
	uint32_t			warning_temp_time;
	uint32_t			critical_comp_time;
	uint16_t			temp_sensor[8];
	uint8_t			rsvd216[296];
};

struct nvme_fw_slot_info_log {
	uint8_t			afi;
	uint8_t			rsvd1[7];
	uint64_t			frs[7];
	uint8_t			rsvd64[448];
};

enum {
	NVME_CMD_EFFECTS_CSUPP		= 1 << 0,
	NVME_CMD_EFFECTS_LBCC		= 1 << 1,
	NVME_CMD_EFFECTS_NCC		= 1 << 2,
	NVME_CMD_EFFECTS_NIC		= 1 << 3,
	NVME_CMD_EFFECTS_CCC		= 1 << 4,
	NVME_CMD_EFFECTS_CSE_MASK	= 3 << 16,
};

struct nvme_effects_log {
	uint32_t acs[256];
	uint32_t iocs[256];
	uint8_t   resv[2048];
};

enum {
	NVME_SMART_CRIT_SPARE		= 1 << 0,
	NVME_SMART_CRIT_TEMPERATURE	= 1 << 1,
	NVME_SMART_CRIT_RELIABILITY	= 1 << 2,
	NVME_SMART_CRIT_MEDIA		= 1 << 3,
	NVME_SMART_CRIT_VOLATILE_MEMORY	= 1 << 4,
};

enum {
	NVME_AER_ERROR			= 0,
	NVME_AER_SMART			= 1,
	NVME_AER_CSS			= 6,
	NVME_AER_VS			= 7,
	NVME_AER_NOTICE_NS_CHANGED	= 0x0002,
	NVME_AER_NOTICE_FW_ACT_STARTING = 0x0102,
};

struct nvme_lba_range_type {
	uint8_t			type;
	uint8_t			attributes;
	uint8_t			rsvd2[14];
	uint64_t			slba;
	uint64_t			nlb;
	uint8_t			guid[16];
	uint8_t			rsvd48[16];
};

enum {
	NVME_LBART_TYPE_FS	= 0x01,
	NVME_LBART_TYPE_RAID	= 0x02,
	NVME_LBART_TYPE_CACHE	= 0x03,
	NVME_LBART_TYPE_SWAP	= 0x04,

	NVME_LBART_ATTRIB_TEMP	= 1 << 0,
	NVME_LBART_ATTRIB_HIDE	= 1 << 1,
};

struct nvme_reservation_status {
	uint32_t	gen;
	uint8_t	rtype;
	uint8_t	regctl[2];
	uint8_t	resv5[2];
	uint8_t	ptpls;
	uint8_t	resv10[13];
	struct {
		uint16_t	cntlid;
		uint8_t	rcsts;
		uint8_t	resv3[5];
		uint64_t	hostid;
		uint64_t	rkey;
	} regctl_ds[];
};

enum nvme_async_event_type {
	NVME_AER_TYPE_ERROR	= 0,
	NVME_AER_TYPE_SMART	= 1,
	NVME_AER_TYPE_NOTICE	= 2,
};

/* I/O commands */

enum nvme_opcode {
	nvme_cmd_flush         = 0x00,
	nvme_cmd_write         = 0x01,
	nvme_cmd_read          = 0x02,
	nvme_cmd_write_uncor   = 0x04,
	nvme_cmd_compare       = 0x05,
	nvme_cmd_write_zeroes  = 0x08,
	nvme_cmd_dsm           = 0x09,
	nvme_cmd_resv_register = 0x0d,
	nvme_cmd_resv_report   = 0x0e,
	nvme_cmd_resv_acquire  = 0x11,
	nvme_cmd_resv_release  = 0x15,
};

/*
 * Descriptor subtype - lower 4 bits of nvme_(keyed_)sgl_desc identifier
 *
 * @NVME_SGL_FMT_ADDRESS:     absolute address of the data block
 * @NVME_SGL_FMT_OFFSET:      relative offset of the in-capsule data block
 * @NVME_SGL_FMT_TRANSPORT_A: transport defined format, value 0xA
 * @NVME_SGL_FMT_INVALIDATE:  RDMA transport specific remote invalidation
 *                            request subtype
 */
enum {
	NVME_SGL_FMT_ADDRESS		= 0x00,
	NVME_SGL_FMT_OFFSET		= 0x01,
	NVME_SGL_FMT_TRANSPORT_A	= 0x0A,
	NVME_SGL_FMT_INVALIDATE		= 0x0f,
};

/*
 * Descriptor type - upper 4 bits of nvme_(keyed_)sgl_desc identifier
 *
 * For struct nvme_sgl_desc:
 *   @NVME_SGL_FMT_DATA_DESC:		data block descriptor
 *   @NVME_SGL_FMT_SEG_DESC:		sgl segment descriptor
 *   @NVME_SGL_FMT_LAST_SEG_DESC:	last sgl segment descriptor
 *
 * For struct nvme_keyed_sgl_desc:
 *   @NVME_KEY_SGL_FMT_DATA_DESC:	keyed data block descriptor
 *
 * Transport-specific SGL types:
 *   @NVME_TRANSPORT_SGL_DATA_DESC:	Transport SGL data dlock descriptor
 */
enum {
	NVME_SGL_FMT_DATA_DESC		= 0x00,
	NVME_SGL_FMT_SEG_DESC		= 0x02,
	NVME_SGL_FMT_LAST_SEG_DESC	= 0x03,
	NVME_KEY_SGL_FMT_DATA_DESC	= 0x04,
	NVME_TRANSPORT_SGL_DATA_DESC	= 0x05,
};

struct nvme_sgl_desc {
	uint64_t	addr;
	uint32_t	length;
	uint8_t	rsvd[3];
	uint8_t	type;
};

struct nvme_keyed_sgl_desc {
	uint64_t	addr;
	uint8_t	length[3];
	uint8_t	key[4];
	uint8_t	type;
};

union nvme_data_ptr {
	struct {
		uint64_t	prp1;
		uint64_t	prp2;
	};
	struct nvme_sgl_desc	sgl;
	struct nvme_keyed_sgl_desc ksgl;
};

/*
 * Lowest two bits of our flags field (FUSE field in the spec):
 *
 * @NVME_CMD_FUSE_FIRST:   Fused Operation, first command
 * @NVME_CMD_FUSE_SECOND:  Fused Operation, second command
 *
 * Highest two bits in our flags field (PSDT field in the spec):
 *
 * @NVME_CMD_PSDT_SGL_METABUF:	Use SGLS for this transfer,
 *	If used, MPTR contains addr of single physical buffer (byte aligned).
 * @NVME_CMD_PSDT_SGL_METASEG:	Use SGLS for this transfer,
 *	If used, MPTR contains an address of an SGL segment containing
 *	exactly 1 SGL descriptor (qword aligned).
 */
enum {
	NVME_CMD_FUSE_FIRST	= (1 << 0),
	NVME_CMD_FUSE_SECOND	= (1 << 1),

	NVME_CMD_SGL_METABUF	= (1 << 6),
	NVME_CMD_SGL_METASEG	= (1 << 7),
	NVME_CMD_SGL_ALL	= NVME_CMD_SGL_METABUF | NVME_CMD_SGL_METASEG,
};

struct nvme_common_command {
	uint8_t			opcode;
	uint8_t			flags;
	uint16_t			command_id;
	uint32_t			nsid;
	uint32_t			cdw2[2];
	uint64_t			metadata;
	union nvme_data_ptr	dptr;
	uint32_t			cdw10[6];
};

struct nvme_rw_command {
	uint8_t             opcode;
	uint8_t             flags;
	uint16_t			command_id;
	uint32_t			nsid;
	uint64_t			rsvd2;
	uint64_t			metadata;
	union nvme_data_ptr	dptr;
	uint64_t			slba;
	uint16_t			length;
	uint16_t			control;
	uint32_t			dsmgmt;
	uint32_t			reftag;
	uint16_t			apptag;
	uint16_t			appmask;
};

enum {
	NVME_RW_LR			= 1 << 15,
	NVME_RW_FUA			= 1 << 14,
	NVME_RW_DSM_FREQ_UNSPEC		= 0,
	NVME_RW_DSM_FREQ_TYPICAL	= 1,
	NVME_RW_DSM_FREQ_RARE		= 2,
	NVME_RW_DSM_FREQ_READS		= 3,
	NVME_RW_DSM_FREQ_WRITES		= 4,
	NVME_RW_DSM_FREQ_RW		= 5,
	NVME_RW_DSM_FREQ_ONCE		= 6,
	NVME_RW_DSM_FREQ_PREFETCH	= 7,
	NVME_RW_DSM_FREQ_TEMP		= 8,
	NVME_RW_DSM_LATENCY_NONE	= 0 << 4,
	NVME_RW_DSM_LATENCY_IDLE	= 1 << 4,
	NVME_RW_DSM_LATENCY_NORM	= 2 << 4,
	NVME_RW_DSM_LATENCY_LOW		= 3 << 4,
	NVME_RW_DSM_SEQ_REQ		= 1 << 6,
	NVME_RW_DSM_COMPRESSED		= 1 << 7,
	NVME_RW_PRINFO_PRCHK_REF	= 1 << 10,
	NVME_RW_PRINFO_PRCHK_APP	= 1 << 11,
	NVME_RW_PRINFO_PRCHK_GUARD	= 1 << 12,
	NVME_RW_PRINFO_PRACT		= 1 << 13,
	NVME_RW_DTYPE_STREAMS		= 1 << 4,
};

struct nvme_dsm_cmd {
	uint8_t			opcode;
	uint8_t			flags;
	uint16_t			command_id;
	uint32_t			nsid;
	uint64_t			rsvd2[2];
	union nvme_data_ptr	dptr;
	uint32_t			nr;
	uint32_t			attributes;
	uint32_t			rsvd12[4];
};

enum {
	NVME_DSMGMT_IDR		= 1 << 0,
	NVME_DSMGMT_IDW		= 1 << 1,
	NVME_DSMGMT_AD		= 1 << 2,
};

#define NVME_DSM_MAX_RANGES	256

struct nvme_dsm_range {
	uint32_t			cattr;
	uint32_t			nlb;
	uint64_t			slba;
};

struct nvme_write_zeroes_cmd {
	uint8_t			opcode;
	uint8_t			flags;
	uint16_t			command_id;
	uint32_t			nsid;
	uint64_t			rsvd2;
	uint64_t			metadata;
	union nvme_data_ptr	dptr;
	uint64_t			slba;
	uint16_t			length;
	uint16_t			control;
	uint32_t			dsmgmt;
	uint32_t			reftag;
	uint16_t			apptag;
	uint16_t			appmask;
};

/* Features */

struct nvme_feat_auto_pst {
	uint64_t entries[32];
};

enum {
	NVME_HOST_MEM_ENABLE	= (1 << 0),
	NVME_HOST_MEM_RETURN	= (1 << 1),
};

/* Admin commands */

enum nvme_admin_opcode {
	nvme_admin_delete_sq	  = 0x00,
	nvme_admin_create_sq	  = 0x01,
	nvme_admin_get_log_page	  = 0x02,
	nvme_admin_delete_cq	  = 0x04,
	nvme_admin_create_cq	  = 0x05,
	nvme_admin_identify       = 0x06,
	nvme_admin_abort_cmd	  = 0x08,
	nvme_admin_set_features	  = 0x09,
	nvme_admin_get_features	  = 0x0a,
	nvme_admin_async_event	  = 0x0c,
	nvme_admin_ns_mgmt        = 0x0d,
	nvme_admin_activate_fw	  = 0x10,
	nvme_admin_download_fw	  = 0x11,
	nvme_admin_ns_attach	  = 0x15,
	nvme_admin_keep_alive	  = 0x18,
	nvme_admin_directive_send = 0x19,
	nvme_admin_directive_recv = 0x1a,
	nvme_admin_dbbuf          = 0x7C,
	nvme_admin_format_nvm	  = 0x80,
	nvme_admin_security_send  = 0x81,
	nvme_admin_security_recv  = 0x82,
	nvme_admin_sanitize_nvm	  = 0x84,
};

enum {
	NVME_QUEUE_PHYS_CONTIG	= (1 << 0),
	NVME_CQ_IRQ_ENABLED	= (1 << 1),
	NVME_SQ_PRIO_URGENT	= (0 << 1),
	NVME_SQ_PRIO_HIGH	= (1 << 1),
	NVME_SQ_PRIO_MEDIUM	= (2 << 1),
	NVME_SQ_PRIO_LOW	= (3 << 1),
	NVME_FEAT_ARBITRATION	= 0x01,
	NVME_FEAT_POWER_MGMT	= 0x02,
	NVME_FEAT_LBA_RANGE	= 0x03,
	NVME_FEAT_TEMP_THRESH	= 0x04,
	NVME_FEAT_ERR_RECOVERY	= 0x05,
	NVME_FEAT_VOLATILE_WC	= 0x06,
	NVME_FEAT_NUM_QUEUES	= 0x07,
	NVME_FEAT_IRQ_COALESCE	= 0x08,
	NVME_FEAT_IRQ_CONFIG	= 0x09,
	NVME_FEAT_WRITE_ATOMIC	= 0x0a,
	NVME_FEAT_ASYNC_EVENT	= 0x0b,
	NVME_FEAT_AUTO_PST	= 0x0c,
	NVME_FEAT_HOST_MEM_BUF	= 0x0d,
	NVME_FEAT_TIMESTAMP	= 0x0e,
	NVME_FEAT_KATO		= 0x0f,
	NVME_FEAT_SW_PROGRESS	= 0x80,
	NVME_FEAT_HOST_ID	= 0x81,
	NVME_FEAT_RESV_MASK	= 0x82,
	NVME_FEAT_RESV_PERSIST	= 0x83,
	NVME_LOG_ERROR		= 0x01,
	NVME_LOG_SMART		= 0x02,
	NVME_LOG_FW_SLOT	= 0x03,
	NVME_LOG_CMD_EFFECTS	= 0x05,
	NVME_LOG_DISC		= 0x70,
	NVME_LOG_RESERVATION	= 0x80,
	NVME_FWACT_REPL		= (0 << 3),
	NVME_FWACT_REPL_ACTV	= (1 << 3),
	NVME_FWACT_ACTV		= (2 << 3),
};

struct nvme_identify {
	uint8_t			opcode;
	uint8_t			flags;
	uint16_t			command_id;
	uint32_t			nsid;
	uint64_t			rsvd2[2];
	union nvme_data_ptr	dptr;
	uint8_t			cns;
	uint8_t			rsvd3;
	uint16_t			ctrlid;
	uint32_t			rsvd11[5];
};

#define NVME_IDENTIFY_DATA_SIZE 4096

struct nvme_features {
	uint8_t			opcode;
	uint8_t			flags;
	uint16_t			command_id;
	uint32_t			nsid;
	uint64_t			rsvd2[2];
	union nvme_data_ptr	dptr;
	uint32_t			fid;
	uint32_t			dword11;
	uint32_t                  dword12;
	uint32_t                  dword13;
	uint32_t                  dword14;
	uint32_t                  dword15;
};

struct nvme_host_mem_buf_desc {
	uint64_t			addr;
	uint32_t			size;
	uint32_t			rsvd;
};

struct nvme_create_cq {
	uint8_t			opcode;
	uint8_t			flags;
	uint16_t			command_id;
	uint32_t			rsvd1[5];
	uint64_t			prp1;
	uint64_t			rsvd8;
	uint16_t			cqid;
	uint16_t			qsize;
	uint16_t			cq_flags;
	uint16_t			irq_vector;
	uint32_t			rsvd12[4];
};

struct nvme_create_sq {
	uint8_t			opcode;
	uint8_t			flags;
	uint16_t			command_id;
	uint32_t			rsvd1[5];
	uint64_t			prp1;
	uint64_t			rsvd8;
	uint16_t			sqid;
	uint16_t			qsize;
	uint16_t			sq_flags;
	uint16_t			cqid;
	uint32_t			rsvd12[4];
};

struct nvme_delete_queue {
	uint8_t			opcode;
	uint8_t			flags;
	uint16_t			command_id;
	uint32_t			rsvd1[9];
	uint16_t			qid;
	uint16_t			rsvd10;
	uint32_t			rsvd11[5];
};

struct nvme_abort_cmd {
	uint8_t			opcode;
	uint8_t			flags;
	uint16_t			command_id;
	uint32_t			rsvd1[9];
	uint16_t			sqid;
	uint16_t			cid;
	uint32_t			rsvd11[5];
};

struct nvme_download_firmware {
	uint8_t			opcode;
	uint8_t			flags;
	uint16_t			command_id;
	uint32_t			rsvd1[5];
	union nvme_data_ptr	dptr;
	uint32_t			numd;
	uint32_t			offset;
	uint32_t			rsvd12[4];
};

struct nvme_format_cmd {
	uint8_t			opcode;
	uint8_t			flags;
	uint16_t			command_id;
	uint32_t			nsid;
	uint64_t			rsvd2[4];
	uint32_t			cdw10;
	uint32_t			rsvd11[5];
};

struct nvme_get_log_page_command {
	uint8_t			opcode;
	uint8_t			flags;
	uint16_t			command_id;
	uint32_t			nsid;
	uint64_t			rsvd2[2];
	union nvme_data_ptr	dptr;
	uint8_t			lid;
	uint8_t			rsvd10;
	uint16_t			numdl;
	uint16_t			numdu;
	uint16_t			rsvd11;
	uint32_t			lpol;
	uint32_t			lpou;
	uint32_t			rsvd14[2];
};

struct nvme_directive_cmd {
	uint8_t			opcode;
	uint8_t			flags;
	uint16_t			command_id;
	uint32_t			nsid;
	uint64_t			rsvd2[2];
	union nvme_data_ptr	dptr;
	uint32_t			numd;
	uint8_t			doper;
	uint8_t			dtype;
	uint16_t			dspec;
	uint8_t			endir;
	uint8_t			tdtype;
	uint16_t			rsvd15;

	uint32_t			rsvd16[3];
};

/*
 * Fabrics subcommands.
 */
enum nvmf_fabrics_opcode {
	nvme_fabrics_command		= 0x7f,
};

enum nvmf_capsule_command {
	nvme_fabrics_type_property_set	= 0x00,
	nvme_fabrics_type_connect	= 0x01,
	nvme_fabrics_type_property_get	= 0x04,
};

struct nvmf_common_command {
	uint8_t	opcode;
	uint8_t	resv1;
	uint16_t	command_id;
	uint8_t	fctype;
	uint8_t	resv2[35];
	uint8_t	ts[24];
};

/*
 * The legal cntlid range a NVMe Target will provide.
 * Note that cntlid of value 0 is considered illegal in the fabrics world.
 * Devices based on earlier specs did not have the subsystem concept;
 * therefore, those devices had their cntlid value set to 0 as a result.
 */
#define NVME_CNTLID_MIN		1
#define NVME_CNTLID_MAX		0xffef
#define NVME_CNTLID_DYNAMIC	0xffff

#define MAX_DISC_LOGS	255

/* Discovery log page entry */
struct nvmf_disc_rsp_page_entry {
	uint8_t		trtype;
	uint8_t		adrfam;
	uint8_t		subtype;
	uint8_t		treq;
	uint16_t		portid;
	uint16_t		cntlid;
	uint16_t		asqsz;
	uint8_t		resv8[22];
	char		trsvcid[NVMF_TRSVCID_SIZE];
	uint8_t		resv64[192];
	char		subnqn[NVMF_NQN_FIELD_LEN];
	char		traddr[NVMF_TRADDR_SIZE];
	union tsas {
		char		common[NVMF_TSAS_SIZE];
		struct rdma {
			uint8_t	qptype;
			uint8_t	prtype;
			uint8_t	cms;
			uint8_t	resv3[5];
			uint16_t	pkey;
			uint8_t	resv10[246];
		} rdma;
	} tsas;
};

/* Discovery log page header */
struct nvmf_disc_rsp_page_hdr {
	uint64_t		genctr;
	uint64_t		numrec;
	uint16_t		recfmt;
	uint8_t		resv14[1006];
	struct nvmf_disc_rsp_page_entry entries[0];
};

struct nvmf_connect_command {
	uint8_t		opcode;
	uint8_t		resv1;
	uint16_t		command_id;
	uint8_t		fctype;
	uint8_t		resv2[19];
	union nvme_data_ptr dptr;
	uint16_t		recfmt;
	uint16_t		qid;
	uint16_t		sqsize;
	uint8_t		cattr;
	uint8_t		resv3;
	uint32_t		kato;
	uint8_t		resv4[12];
};

struct nvmf_connect_data {
	unsigned char hostid[16];
	uint16_t	  cntlid;
	char          resv4[238];
	char          subsysnqn[NVMF_NQN_FIELD_LEN];
	char          hostnqn[NVMF_NQN_FIELD_LEN];
	char          resv5[256];
};

struct nvmf_property_set_command {
	uint8_t		opcode;
	uint8_t		resv1;
	uint16_t		command_id;
	uint8_t		fctype;
	uint8_t		resv2[35];
	uint8_t		attrib;
	uint8_t		resv3[3];
	uint32_t		offset;
	uint64_t		value;
	uint8_t		resv4[8];
};

struct nvmf_property_get_command {
	uint8_t		opcode;
	uint8_t		resv1;
	uint16_t		command_id;
	uint8_t		fctype;
	uint8_t		resv2[35];
	uint8_t		attrib;
	uint8_t		resv3[3];
	uint32_t		offset;
	uint8_t		resv4[16];
};

struct nvme_dbbuf {
	uint8_t			opcode;
	uint8_t			flags;
	uint16_t			command_id;
	uint32_t			rsvd1[5];
	uint64_t			prp1;
	uint64_t			prp2;
	uint32_t			rsvd12[6];
};

struct streams_directive_params {
	uint16_t	msl;
	uint16_t	nssa;
	uint16_t	nsso;
	uint8_t	rsvd[10];
	uint32_t	sws;
	uint16_t	sgs;
	uint16_t	nsa;
	uint16_t	nso;
	uint8_t	rsvd2[6];
};

struct nvme_command {
	union {
		struct nvme_common_command common;
		struct nvme_rw_command rw;
		struct nvme_identify identify;
		struct nvme_features features;
		struct nvme_create_cq create_cq;
		struct nvme_create_sq create_sq;
		struct nvme_delete_queue delete_queue;
		struct nvme_download_firmware dlfw;
		struct nvme_format_cmd format;
		struct nvme_dsm_cmd dsm;
		struct nvme_write_zeroes_cmd write_zeroes;
		struct nvme_abort_cmd abort;
		struct nvme_get_log_page_command get_log_page;
		struct nvmf_common_command fabrics;
		struct nvmf_connect_command connect;
		struct nvmf_property_set_command prop_set;
		struct nvmf_property_get_command prop_get;
		struct nvme_dbbuf dbbuf;
		struct nvme_directive_cmd directive;
	};
};

static inline bool nvme_is_write(struct nvme_command *cmd)
{
	/*
	 * What a mess...
	 *
	 * Why can't we simply have a Fabrics In and Fabrics out command?
	 */
	if (cmd->common.opcode == nvme_fabrics_command)
		return cmd->fabrics.fctype & 1;
	return cmd->common.opcode & 1;
}

enum {
	/*
	 * Generic Command Status:
	 */
	NVME_SC_SUCCESS			= 0x0,
	NVME_SC_INVALID_OPCODE		= 0x1,
	NVME_SC_INVALID_FIELD		= 0x2,
	NVME_SC_CMDID_CONFLICT		= 0x3,
	NVME_SC_DATA_XFER_ERROR		= 0x4,
	NVME_SC_POWER_LOSS		= 0x5,
	NVME_SC_INTERNAL		= 0x6,
	NVME_SC_ABORT_REQ		= 0x7,
	NVME_SC_ABORT_QUEUE		= 0x8,
	NVME_SC_FUSED_FAIL		= 0x9,
	NVME_SC_FUSED_MISSING		= 0xa,
	NVME_SC_INVALID_NS		= 0xb,
	NVME_SC_CMD_SEQ_ERROR		= 0xc,
	NVME_SC_SGL_INVALID_LAST	= 0xd,
	NVME_SC_SGL_INVALID_COUNT	= 0xe,
	NVME_SC_SGL_INVALID_DATA	= 0xf,
	NVME_SC_SGL_INVALID_METADATA	= 0x10,
	NVME_SC_SGL_INVALID_TYPE	= 0x11,

	NVME_SC_SGL_INVALID_OFFSET	= 0x16,
	NVME_SC_SGL_INVALID_SUBTYPE	= 0x17,

	NVME_SC_LBA_RANGE		= 0x80,
	NVME_SC_CAP_EXCEEDED		= 0x81,
	NVME_SC_NS_NOT_READY		= 0x82,
	NVME_SC_RESERVATION_CONFLICT	= 0x83,

	/*
	 * Command Specific Status:
	 */
	NVME_SC_CQ_INVALID		= 0x100,
	NVME_SC_QID_INVALID		= 0x101,
	NVME_SC_QUEUE_SIZE		= 0x102,
	NVME_SC_ABORT_LIMIT		= 0x103,
	NVME_SC_ABORT_MISSING		= 0x104,
	NVME_SC_ASYNC_LIMIT		= 0x105,
	NVME_SC_FIRMWARE_SLOT		= 0x106,
	NVME_SC_FIRMWARE_IMAGE		= 0x107,
	NVME_SC_INVALID_VECTOR		= 0x108,
	NVME_SC_INVALID_LOG_PAGE	= 0x109,
	NVME_SC_INVALID_FORMAT		= 0x10a,
	NVME_SC_FW_NEEDS_CONV_RESET	= 0x10b,
	NVME_SC_INVALID_QUEUE		= 0x10c,
	NVME_SC_FEATURE_NOT_SAVEABLE	= 0x10d,
	NVME_SC_FEATURE_NOT_CHANGEABLE	= 0x10e,
	NVME_SC_FEATURE_NOT_PER_NS	= 0x10f,
	NVME_SC_FW_NEEDS_SUBSYS_RESET	= 0x110,
	NVME_SC_FW_NEEDS_RESET		= 0x111,
	NVME_SC_FW_NEEDS_MAX_TIME	= 0x112,
	NVME_SC_FW_ACIVATE_PROHIBITED	= 0x113,
	NVME_SC_OVERLAPPING_RANGE	= 0x114,
	NVME_SC_NS_INSUFFICENT_CAP	= 0x115,
	NVME_SC_NS_ID_UNAVAILABLE	= 0x116,
	NVME_SC_NS_ALREADY_ATTACHED	= 0x118,
	NVME_SC_NS_IS_PRIVATE		= 0x119,
	NVME_SC_NS_NOT_ATTACHED		= 0x11a,
	NVME_SC_THIN_PROV_NOT_SUPP	= 0x11b,
	NVME_SC_CTRL_LIST_INVALID	= 0x11c,

	/*
	 * I/O Command Set Specific - NVM commands:
	 */
	NVME_SC_BAD_ATTRIBUTES		= 0x180,
	NVME_SC_INVALID_PI		= 0x181,
	NVME_SC_READ_ONLY		= 0x182,
	NVME_SC_ONCS_NOT_SUPPORTED	= 0x183,

	/*
	 * I/O Command Set Specific - Fabrics commands:
	 */
	NVME_SC_CONNECT_FORMAT		= 0x180,
	NVME_SC_CONNECT_CTRL_BUSY	= 0x181,
	NVME_SC_CONNECT_INVALID_PARAM	= 0x182,
	NVME_SC_CONNECT_RESTART_DISC	= 0x183,
	NVME_SC_CONNECT_INVALID_HOST	= 0x184,

	NVME_SC_DISCOVERY_RESTART	= 0x190,
	NVME_SC_AUTH_REQUIRED		= 0x191,

	/*
	 * Media and Data Integrity Errors:
	 */
	NVME_SC_WRITE_FAULT		= 0x280,
	NVME_SC_READ_ERROR		= 0x281,
	NVME_SC_GUARD_CHECK		= 0x282,
	NVME_SC_APPTAG_CHECK		= 0x283,
	NVME_SC_REFTAG_CHECK		= 0x284,
	NVME_SC_COMPARE_FAILED		= 0x285,
	NVME_SC_ACCESS_DENIED		= 0x286,
	NVME_SC_UNWRITTEN_BLOCK		= 0x287,

	NVME_SC_DNR			= 0x4000,
};

struct nvme_completion {
	/*
	 * Used by Admin and Fabrics commands to return data:
	 */
	union nvme_result {
		uint16_t	u16;
		uint32_t	u32;
		uint64_t	u64;
	} result;
	uint16_t	sq_head;	/* how much of this queue may be reclaimed */
	uint16_t	sq_id;		/* submission queue that generated this entry */
	uint16_t	command_id;	/* of the command which completed */
	uint16_t	status;		/* did the command fail, and if so, why? */
};

#define NVME_VS(major, minor, tertiary) \
	(((major) << 16) | ((minor) << 8) | (tertiary))

#define NVME_MAJOR(ver)		((ver) >> 16)
#define NVME_MINOR(ver)		(((ver) >> 8) & 0xff)
#define NVME_TERTIARY(ver)	((ver) & 0xff)

#endif /* _LINUX_NVME_H */
