#ifdef NVME_H
#define NVME_H


/*
 * -- Submission Queue (SQ):
 * A Submission Queue (SQ) is a circular buffer with a fixed slot size that the host software uses 
 * to submit commands for execution by the controller. 
 * The controller fetches SQ entries in order from the Submission Queue, 
 * however, it may then execute those commands in any order.
 *
 * 1.Each Submission Queue entry is a command. Commands are 64 bytes in size. 
 * 2.The physical memory locations in memory to use for data transfers are specified using 
 *   Physical Region Page (PRP) entries or Scatter Gather Lists. 
 */

/*
 * -- Completion Queue (CQ):
 * A Completion Queue (CQ) is a circular buffer with a fixed slot size used to post status 
 * for completed commands.
 * A completed command is uniquely identified by a combination of the associated SQ identifier 
 * and command identifier that is assigned by host software.
 */

/* -- Admin Queue:
 * An Admin Submission and associated Completion Queue exist for the purpose of 
 * controller management and control 
 * (e.g., creation and deletion of I/O Submission and Completion Queues, aborting commands, etc.) 
 * Only commands that are part of the Admin Command Set may be submitted to the Admin Submission Queue.
 * The Admin Queue is the Submission Queue and Completion Queue with identifier 0. 
*/

/*****************************************/
/* System Bus (PCI Express) Registers    */
/*****************************************/
/* PCI Header                            */
typedef struct tag_SysBusReg_PCI_Header_t{
        /* (00h - 03h): Identifiers                                              */
        /* (04h - 05h): Command Register                                         */
        /* (06h - 07h): Device Status                                            */
        /* (08h - 08h): Revision ID                                              */
        /* (09h - 0Bh): Class Codes                                              */
        /* (0Ch - 0Ch): Cache Line Size                                          */
        /* (0Dh - 0Dh): Master Latency Timer                                     */
        /* (0Eh - 0Eh): Header Type                                              */
        /* (0Fh - 0Fh): Build In Self Test (Optional)                            */
        /* (10h - 13h): Memory Register Base Address, lower 32-bits <BAR 0>      */
        /* (14h - 17h): Memory Register Base Address, upper 32-bits <BAR 1>      */
        /* (18h - 1Bh): Index/Data Pair Register Base Address <BAR 2> (Optional) */
        /* (1Ch - 1Fh): Reserved <BAR 3>                                         */
        /* (20h - 23h): Vendor Specific                                          */
        /* (24h - 27h): Vendor Specific                                          */
        /* (28h - 2Bh): CardBus CIS Pointer                                      */
        /* (2Ch - 2Fh): Subsystem Identifier                                     */
        /* (30h - 33h): Expansion ROM Base Address (Optional)                    */
        /* (34h - 34h): Capabilities Pointer                                     */
        /* (35h - 3Bh): Reserved                                                 */
        /* (3Ch - 3Dh): Interrupt Information                                    */
        /* (3Eh - 3Eh): Minimum Grant (Optional)                                 */
        /* (3Fh - 3Fh): Maximum Latency (Optional)                               */
}SysBusReg_PCI_Header_t;
/* PCI Power Management Capability       */
/* Message Signaled Interrupt Capability */
/* MSI-X Capability                      */
/* PCI Express Capability                */
/* Advanced Error Reporting Capability   */


/*************************************/
/* Admin Command Set                 */
/*************************************/
/* Delete I/O Submission Queue       */
/* Create I/O Submission Queue       */
/* Get Log Page                      */
/* Delete I/O Completion Queue       */
/* Create I/O Completion Queue       */
/* Identify                          */
/* Abort                             */
/* Set Feature                       */
/* Get Feature                       */
/* Asynchronous Event Request        */
/* NameSpace Management              */
/* Fireware Commit                   */
/* Fireware Image Download           */
/* NameSpace Attachment              */
/* I/O Command Set specific          */
/* Vendor specific                   */
/* Format NVM                        */
/* Security Send                     */
/* Security Receive                  */


/*************************************/
/* NVM Command Set                   */
/*************************************/
/* Namespace                         */
/* Fused Operations                  */
/* Command Ordering Requirement      */
/* Atomic Operations                 */
/* End-to-end Protection Information */
/* Compare command                   */
/* Data Management command           */
/* Flush command                     */
/* Read command                      */

/* Reservatio Acquire command        */
/* Reservatio Register command       */
/* Reservatio Release command        */
/* Reservatio Report command         */
/* Write command                     */
/* Write Uncorrectable command       */
/* Write Zeros command               */


#endif /* NVME_H */
