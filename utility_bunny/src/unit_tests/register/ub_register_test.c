/**
 *  @file ub_register_test.c
 *  @brief 
 *  @author John F.X. Galea
 */

#include "dr_api.h"
#include "drmgr.h"
#include "../../utility_bunny.h"

static void test1() {

	DR_ASSERT_MSG(ub_get_reg_size(DR_REG_DH) == 1,
			"ub_register_test - test1 -0 failed...");

	DR_ASSERT_MSG(ub_get_reg_size(DR_REG_CH) == 1,
			"ub_register_test - test1 - 1 failed...");

	DR_ASSERT_MSG(ub_get_reg_size(DR_REG_BH) == 1,
			"ub_register_test - test1 - 2 failed...");

	DR_ASSERT_MSG(ub_get_reg_size(DR_REG_AH) == 1,
			"ub_register_test - test1 - 3 failed...");

#ifdef X86_64

	DR_ASSERT_MSG(ub_get_reg_size(DR_REG_R15) == 8,
			"ub_register_test - test1 - 4 failed...");

	DR_ASSERT_MSG(ub_get_reg_size(DR_REG_R14) == 8,
			"ub_register_test - test1 - 5 failed...");

	DR_ASSERT_MSG(ub_get_reg_size(DR_REG_R13) == 8,
			"ub_register_test - test1 - 6 failed...");

	DR_ASSERT_MSG(ub_get_reg_size(DR_REG_R12) == 8,
			"ub_register_test - test1 - 7 failed...");

	DR_ASSERT_MSG(ub_get_reg_size(DR_REG_R11) == 8,
			"ub_register_test - test1 - 8 failed...");

	DR_ASSERT_MSG(ub_get_reg_size(DR_REG_R10) == 8,
			"ub_register_test - test1 - 9 failed...");

	DR_ASSERT_MSG(ub_get_reg_size(DR_REG_R9) == 8,
			"ub_register_test - test1 - 10 failed...");

	DR_ASSERT_MSG(ub_get_reg_size(DR_REG_R8) == 8,
			"ub_register_test - test1 - 11 failed...");

	DR_ASSERT_MSG(ub_get_reg_size(DR_REG_R15L) == 1,
			"ub_register_test - tes1 - t12 failed...");

	DR_ASSERT_MSG(ub_get_reg_size(DR_REG_R14L) == 1,
			"ub_register_test - test1 - 13 failed...");

	DR_ASSERT_MSG(ub_get_reg_size(DR_REG_R13L) == 1,
			"ub_register_test - test1 - 14 failed...");

	DR_ASSERT_MSG(ub_get_reg_size(DR_REG_R12L) == 1,
			"ub_register_test - test1 - 15 failed...");

	DR_ASSERT_MSG(ub_get_reg_size(DR_REG_R11L) == 1,
			"ub_register_test - test1 - 16 failed...");

	DR_ASSERT_MSG(ub_get_reg_size(DR_REG_R10L) == 1,
			"ub_register_test - test1 - 17 failed...");

	DR_ASSERT_MSG(ub_get_reg_size(DR_REG_R9L) == 1,
			"ub_register_test - test1 - 18 failed...");

	DR_ASSERT_MSG(ub_get_reg_size(DR_REG_R8L) == 1,
			"ub_register_test - test1 - 19 failed...");

	DR_ASSERT_MSG(ub_get_reg_size(DR_REG_R15D) == 4,
			"ub_register_test - test1 - 20 failed...");

	DR_ASSERT_MSG(ub_get_reg_size(DR_REG_R14D) == 4,
			"ub_register_test - test1 - 21 failed...");

	DR_ASSERT_MSG(ub_get_reg_size(DR_REG_R13D) == 4,
			"ub_register_test - test1 - 22 failed...");

	DR_ASSERT_MSG(ub_get_reg_size(DR_REG_R12D) == 4,
			"ub_register_test - test1 - 23 failed...");

	DR_ASSERT_MSG(ub_get_reg_size(DR_REG_R11D) == 4,
			"ub_register_test - test1 - 24 failed...");

	DR_ASSERT_MSG(ub_get_reg_size(DR_REG_R10D) == 4,
			"ub_register_test - test1 - 25 failed...");

	DR_ASSERT_MSG(ub_get_reg_size(DR_REG_R9D) == 4,
			"ub_register_test - test1 - 26 failed...");

	DR_ASSERT_MSG(ub_get_reg_size(DR_REG_R8D) == 4,
			"ub_register_test - test1 - 27 failed...");

	DR_ASSERT_MSG(ub_get_reg_size(DR_REG_R15W) == 2,
			"ub_register_test - test1 - 28 failed...");

	DR_ASSERT_MSG(ub_get_reg_size(DR_REG_R14W) == 2,
			"ub_register_test - test1 - 29 failed...");

	DR_ASSERT_MSG(ub_get_reg_size(DR_REG_R13W) == 2,
			"ub_register_test - test1 - 30 failed...");

	DR_ASSERT_MSG(ub_get_reg_size(DR_REG_R12W) == 2,
			"ub_register_test - test1 - 31 failed...");

	DR_ASSERT_MSG(ub_get_reg_size(DR_REG_R11W) == 2,
			"ub_register_test - test1 - 32 failed...");

	DR_ASSERT_MSG(ub_get_reg_size(DR_REG_R10W) == 2,
			"ub_register_test - test1 - 33 failed...");

	DR_ASSERT_MSG(ub_get_reg_size(DR_REG_R9W) == 2,
			"ub_register_test - test1 - 34 failed...");

	DR_ASSERT_MSG(ub_get_reg_size(DR_REG_R8W) == 2,
			"ub_register_test - test1 - 35 failed...");

	DR_ASSERT_MSG(ub_get_reg_size(DR_REG_RDI) == 8,
			"ub_register_test - test1 - 36 failed...");

	DR_ASSERT_MSG(ub_get_reg_size(DR_REG_RAX) == 8,
			"ub_register_test - test1 - 37 failed...");

	DR_ASSERT_MSG(ub_get_reg_size(DR_REG_RSI) == 8,
			"ub_register_test - test1 - 38 failed...");

	DR_ASSERT_MSG(ub_get_reg_size(DR_REG_RBP) == 8,
			"ub_register_test - test1 - 39 failed...");

	DR_ASSERT_MSG(ub_get_reg_size(DR_REG_RBX) == 8,
			"ub_register_test - test1 - 40 failed...");

	DR_ASSERT_MSG(ub_get_reg_size(DR_REG_RCX) == 8,
			"ub_register_test - test1 - 41 failed...");

	DR_ASSERT_MSG(ub_get_reg_size(DR_REG_RDX) == 8,
			"ub_register_test - test1 - 42 failed...");

	DR_ASSERT_MSG(ub_get_reg_size(DR_REG_RSP) == 8,
			"ub_register_test - test1 - 42 failed...");

#endif

	DR_ASSERT_MSG(ub_get_reg_size(DR_REG_EDI) == 4,
			"ub_register_test - test1 - 43 failed...");

	DR_ASSERT_MSG(ub_get_reg_size(DR_REG_EAX) == 4,
			"ub_register_test - test1 - 44 failed...");

	DR_ASSERT_MSG(ub_get_reg_size(DR_REG_ESI) == 4,
			"ub_register_test - test1 - 45 failed...");

	DR_ASSERT_MSG(ub_get_reg_size(DR_REG_EBP) == 4,
			"ub_register_test - test1 - 46 failed...");

	DR_ASSERT_MSG(ub_get_reg_size(DR_REG_EBX) == 4,
			"ub_register_test - test1 - 47 failed...");

	DR_ASSERT_MSG(ub_get_reg_size(DR_REG_ECX) == 4,
			"ub_register_test - test1 - 48 failed...");

	DR_ASSERT_MSG(ub_get_reg_size(DR_REG_EDX) == 4,
			"ub_register_test - test1 - 49 failed...");

	DR_ASSERT_MSG(ub_get_reg_size(DR_REG_ESP) == 4,
			"ub_register_test - test1 - 50 failed...");

	DR_ASSERT_MSG(ub_get_reg_size(DR_REG_DI) == 2,
			"ub_register_test - test1 - 51 failed...");

	DR_ASSERT_MSG(ub_get_reg_size(DR_REG_AX) == 2,
			"ub_register_test - test1 - 52 failed...");

	DR_ASSERT_MSG(ub_get_reg_size(DR_REG_SI) == 2,
			"ub_register_test - test1 - 53 failed...");

	DR_ASSERT_MSG(ub_get_reg_size(DR_REG_BP) == 2,
			"ub_register_test - test1 - 54 failed...");

	DR_ASSERT_MSG(ub_get_reg_size(DR_REG_BX) == 2,
			"ub_register_test - test1 - 55 failed...");

	DR_ASSERT_MSG(ub_get_reg_size(DR_REG_CX) == 2,
			"ub_register_test - test1 - 56 failed...");

	DR_ASSERT_MSG(ub_get_reg_size(DR_REG_DX) == 2,
			"ub_register_test - test1 - 57 failed...");

	DR_ASSERT_MSG(ub_get_reg_size(DR_REG_SP) == 2,
			"ub_register_test - test1 - 58 failed...");

	DR_ASSERT_MSG(ub_get_reg_size(DR_REG_DL) == 1,
			"ub_register_test - test1 - 59 failed...");

	DR_ASSERT_MSG(ub_get_reg_size(DR_REG_CL) == 1,
			"ub_register_test - test1 - 60 failed...");

	DR_ASSERT_MSG(ub_get_reg_size(DR_REG_BL) == 1,
			"ub_register_test - test1 - 61 failed...");

	DR_ASSERT_MSG(ub_get_reg_size(DR_REG_AL) == 1,
			"ub_register_test - test1 - 62 failed...");

	DR_ASSERT_MSG(ub_get_reg_size(DR_REG_XMM0) == 16,
			"ub_register_test - test1 - 63 failed...");

	DR_ASSERT_MSG(ub_get_reg_size(DR_REG_XMM1) == 16,
			"ub_register_test - test1 - 64 failed...");

	DR_ASSERT_MSG(ub_get_reg_size(DR_REG_XMM2) == 16,
			"ub_register_test - test1 - 65 failed...");

	DR_ASSERT_MSG(ub_get_reg_size(DR_REG_XMM3) == 16,
			"ub_register_test - test1 - 66 failed...");

	DR_ASSERT_MSG(ub_get_reg_size(DR_REG_XMM4) == 16,
			"ub_register_test - test1 - 67 failed...");

	DR_ASSERT_MSG(ub_get_reg_size(DR_REG_XMM5) == 16,
			"ub_register_test - test1 - 68 failed...");

	DR_ASSERT_MSG(ub_get_reg_size(DR_REG_XMM6) == 16,
			"ub_register_test - test1 - 69 failed...");

	DR_ASSERT_MSG(ub_get_reg_size(DR_REG_XMM7) == 16,
			"ub_register_test - test1 - 70 failed...");

	DR_ASSERT_MSG(ub_get_reg_size(DR_REG_XMM8) == 16,
			"ub_register_test - test1 - 71 failed...");

	DR_ASSERT_MSG(ub_get_reg_size(DR_REG_XMM9) == 16,
			"ub_register_test - test1 - 72 failed...");

	DR_ASSERT_MSG(ub_get_reg_size(DR_REG_XMM10) == 16,
			"ub_register_test - test1 - 73 failed...");

	DR_ASSERT_MSG(ub_get_reg_size(DR_REG_XMM11) == 16,
			"ub_register_test - test1 - 74 failed...");

	DR_ASSERT_MSG(ub_get_reg_size(DR_REG_XMM12) == 16,
			"ub_register_test - test1 - 75 failed...");

	DR_ASSERT_MSG(ub_get_reg_size(DR_REG_XMM13) == 16,
			"ub_register_test - test1 - 76 failed...");

	DR_ASSERT_MSG(ub_get_reg_size(DR_REG_XMM14) == 16,
			"ub_register_test - test1 - 77 failed...");

	DR_ASSERT_MSG(ub_get_reg_size(DR_REG_XMM15) == 16,
			"ub_register_test - test1 - 78 failed...");
}

void check_byte_ids_of_reg(reg_id_t id, void *hashset) {

	size_t size = ub_get_reg_size(id);

	for (int i = 0; i < size; i++) {

		bool not_already_included = ub_intptr_hashset_insert(hashset,
				ub_get_byte_id(id, i));

		DR_ASSERT_MSG(not_already_included == true,
				"ub_register_test - test1 - 79 failed...");
	}
}

static void test2() {

	void *hashset = ub_intptr_hashset_create();

	check_byte_ids_of_reg(DR_REG_XAX, hashset);
	check_byte_ids_of_reg(DR_REG_XSP, hashset);
	check_byte_ids_of_reg(DR_REG_XBP, hashset);
	check_byte_ids_of_reg(DR_REG_XSI, hashset);
	check_byte_ids_of_reg(DR_REG_XDI, hashset);
	check_byte_ids_of_reg(DR_REG_XDX, hashset);
	check_byte_ids_of_reg(DR_REG_XCX, hashset);
	check_byte_ids_of_reg(DR_REG_XBX, hashset);

#ifdef X86_64
	check_byte_ids_of_reg(DR_REG_R8, hashset);
	check_byte_ids_of_reg(DR_REG_R9, hashset);
	check_byte_ids_of_reg(DR_REG_R10, hashset);
	check_byte_ids_of_reg(DR_REG_R11, hashset);
	check_byte_ids_of_reg(DR_REG_R12, hashset);
	check_byte_ids_of_reg(DR_REG_R13, hashset);
	check_byte_ids_of_reg(DR_REG_R14, hashset);
	check_byte_ids_of_reg(DR_REG_R15, hashset);
#endif

	check_byte_ids_of_reg(DR_REG_XMM0, hashset);
	check_byte_ids_of_reg(DR_REG_XMM1, hashset);
	check_byte_ids_of_reg(DR_REG_XMM2, hashset);
	check_byte_ids_of_reg(DR_REG_XMM3, hashset);
	check_byte_ids_of_reg(DR_REG_XMM4, hashset);
	check_byte_ids_of_reg(DR_REG_XMM5, hashset);
	check_byte_ids_of_reg(DR_REG_XMM6, hashset);
	check_byte_ids_of_reg(DR_REG_XMM7, hashset);
	check_byte_ids_of_reg(DR_REG_XMM8, hashset);
	check_byte_ids_of_reg(DR_REG_XMM9, hashset);
	check_byte_ids_of_reg(DR_REG_XMM10, hashset);
	check_byte_ids_of_reg(DR_REG_XMM11, hashset);
	check_byte_ids_of_reg(DR_REG_XMM12, hashset);
	check_byte_ids_of_reg(DR_REG_XMM13, hashset);
	check_byte_ids_of_reg(DR_REG_XMM14, hashset);
	check_byte_ids_of_reg(DR_REG_XMM15, hashset);

	ub_intptr_hashset_destroy(hashset);
}

void check_byte_ids_of_max_min_regs(reg_id_t max_id, reg_id_t min_id) {

	size_t size = ub_get_reg_size(min_id);

	for (int i = 0; i < size; i++) {
		DR_ASSERT_MSG(ub_get_byte_id(max_id, i) == ub_get_byte_id(min_id, i),
				"ub_register_test - test80 failed...");
	}
}

static void check_high_byte_id(reg_id_t max_id, unsigned int offset,
		reg_id_t min_id) {

	size_t size = ub_get_reg_size(min_id);

	for (int i = 0; i < size; i++) {

		DR_ASSERT_MSG(
				ub_get_byte_id(max_id, offset + i) == ub_get_byte_id(min_id, i),
				"ub_register_test - test80 failed...");
	}
}

static void test3() {

	check_byte_ids_of_max_min_regs(DR_REG_XAX, DR_REG_XAX);
	check_byte_ids_of_max_min_regs(DR_REG_XAX, DR_REG_EAX);
	check_byte_ids_of_max_min_regs(DR_REG_XAX, DR_REG_AX);
	check_byte_ids_of_max_min_regs(DR_REG_XAX, DR_REG_AL);
	check_high_byte_id(DR_REG_XAX, 1, DR_REG_AH);

	check_byte_ids_of_max_min_regs(DR_REG_XBX, DR_REG_XBX);
	check_byte_ids_of_max_min_regs(DR_REG_XBX, DR_REG_EBX);
	check_byte_ids_of_max_min_regs(DR_REG_XBX, DR_REG_BX);
	check_high_byte_id(DR_REG_XBX, 1, DR_REG_BH);
	check_byte_ids_of_max_min_regs(DR_REG_XBX, DR_REG_BL);

	check_byte_ids_of_max_min_regs(DR_REG_XSI, DR_REG_XSI);
	check_byte_ids_of_max_min_regs(DR_REG_XSI, DR_REG_ESI);
	check_byte_ids_of_max_min_regs(DR_REG_XSI, DR_REG_SI);
	check_byte_ids_of_max_min_regs(DR_REG_XSI, DR_REG_SIL);

	check_byte_ids_of_max_min_regs(DR_REG_XCX, DR_REG_XCX);
	check_byte_ids_of_max_min_regs(DR_REG_XCX, DR_REG_ECX);
	check_byte_ids_of_max_min_regs(DR_REG_XCX, DR_REG_CX);
	check_byte_ids_of_max_min_regs(DR_REG_XCX, DR_REG_CL);
	check_high_byte_id(DR_REG_XCX, 1, DR_REG_CH);

	check_byte_ids_of_max_min_regs(DR_REG_XBP, DR_REG_XBP);
	check_byte_ids_of_max_min_regs(DR_REG_XBP, DR_REG_EBP);
	check_byte_ids_of_max_min_regs(DR_REG_XBP, DR_REG_BP);
	check_byte_ids_of_max_min_regs(DR_REG_XBP, DR_REG_BPL);

	check_byte_ids_of_max_min_regs(DR_REG_XDI, DR_REG_XDI);
	check_byte_ids_of_max_min_regs(DR_REG_XDI, DR_REG_EDI);
	check_byte_ids_of_max_min_regs(DR_REG_XDI, DR_REG_DI);
	check_byte_ids_of_max_min_regs(DR_REG_XDI, DR_REG_DIL);

	check_byte_ids_of_max_min_regs(DR_REG_XDX, DR_REG_XDX);
	check_byte_ids_of_max_min_regs(DR_REG_XDX, DR_REG_EDX);
	check_byte_ids_of_max_min_regs(DR_REG_XDX, DR_REG_DX);
	check_byte_ids_of_max_min_regs(DR_REG_XDX, DR_REG_DL);
	check_high_byte_id(DR_REG_XDX, 1, DR_REG_DH);

	check_byte_ids_of_max_min_regs(DR_REG_XSP, DR_REG_XSP);
	check_byte_ids_of_max_min_regs(DR_REG_XSP, DR_REG_ESP);
	check_byte_ids_of_max_min_regs(DR_REG_XSP, DR_REG_SP);
	check_byte_ids_of_max_min_regs(DR_REG_XSP, DR_REG_SPL);

#ifdef X86_64
	check_byte_ids_of_max_min_regs(DR_REG_R8, DR_REG_R8W);
	check_byte_ids_of_max_min_regs(DR_REG_R8, DR_REG_R8L);
	check_byte_ids_of_max_min_regs(DR_REG_R8, DR_REG_R8D);

	check_byte_ids_of_max_min_regs(DR_REG_R9, DR_REG_R9W);
	check_byte_ids_of_max_min_regs(DR_REG_R9, DR_REG_R9L);
	check_byte_ids_of_max_min_regs(DR_REG_R9, DR_REG_R9D);

	check_byte_ids_of_max_min_regs(DR_REG_R10, DR_REG_R10W);
	check_byte_ids_of_max_min_regs(DR_REG_R10, DR_REG_R10L);
	check_byte_ids_of_max_min_regs(DR_REG_R10, DR_REG_R10D);

	check_byte_ids_of_max_min_regs(DR_REG_R11, DR_REG_R11W);
	check_byte_ids_of_max_min_regs(DR_REG_R11, DR_REG_R11L);
	check_byte_ids_of_max_min_regs(DR_REG_R11, DR_REG_R11D);

	check_byte_ids_of_max_min_regs(DR_REG_R12, DR_REG_R12W);
	check_byte_ids_of_max_min_regs(DR_REG_R12, DR_REG_R12L);
	check_byte_ids_of_max_min_regs(DR_REG_R12, DR_REG_R12D);

	check_byte_ids_of_max_min_regs(DR_REG_R13, DR_REG_R13W);
	check_byte_ids_of_max_min_regs(DR_REG_R13, DR_REG_R13L);
	check_byte_ids_of_max_min_regs(DR_REG_R13, DR_REG_R13D);

	check_byte_ids_of_max_min_regs(DR_REG_R14, DR_REG_R14W);
	check_byte_ids_of_max_min_regs(DR_REG_R14, DR_REG_R14L);
	check_byte_ids_of_max_min_regs(DR_REG_R14, DR_REG_R14D);

	check_byte_ids_of_max_min_regs(DR_REG_R15, DR_REG_R15W);
	check_byte_ids_of_max_min_regs(DR_REG_R15, DR_REG_R15L);
	check_byte_ids_of_max_min_regs(DR_REG_R15, DR_REG_R15D);
#endif

}

void check_byte_indexes(reg_id_t id) {

	size_t size = ub_get_reg_size(id);

	for (int i = 0; i < size; i++) {

		size_t index = ub_get_reg_byte_index(ub_get_byte_id(id, i));

		DR_ASSERT_MSG(index == i, "ub_register_test - test81 failed...");
	}
}

static void test4() {

	check_byte_indexes(DR_REG_XAX);
	check_byte_indexes(DR_REG_XBX);
	check_byte_indexes(DR_REG_XBP);
	check_byte_indexes(DR_REG_XSI);
	check_byte_indexes(DR_REG_XCX);
	check_byte_indexes(DR_REG_XDI);
	check_byte_indexes(DR_REG_XSP);
	check_byte_indexes(DR_REG_XDX);

#ifdef X86_64
	check_byte_indexes(DR_REG_R8);
	check_byte_indexes(DR_REG_R9);
	check_byte_indexes(DR_REG_R10);
	check_byte_indexes(DR_REG_R11);
	check_byte_indexes(DR_REG_R12);
	check_byte_indexes(DR_REG_R13);
	check_byte_indexes(DR_REG_R14);
	check_byte_indexes(DR_REG_R15);
#endif

	check_byte_indexes(DR_REG_XMM0);
	check_byte_indexes(DR_REG_XMM1);
	check_byte_indexes(DR_REG_XMM2);
	check_byte_indexes(DR_REG_XMM3);
	check_byte_indexes(DR_REG_XMM4);
	check_byte_indexes(DR_REG_XMM5);
	check_byte_indexes(DR_REG_XMM6);
	check_byte_indexes(DR_REG_XMM7);
	check_byte_indexes(DR_REG_XMM8);
	check_byte_indexes(DR_REG_XMM9);
	check_byte_indexes(DR_REG_XMM10);
	check_byte_indexes(DR_REG_XMM11);
	check_byte_indexes(DR_REG_XMM12);
	check_byte_indexes(DR_REG_XMM13);
	check_byte_indexes(DR_REG_XMM14);
	check_byte_indexes(DR_REG_XMM15);
}

void check_from_byte_to_reg(reg_id_t id) {

	size_t size = ub_get_reg_size(id);

	for (int i = 0; i < size; i++) {

		reg_id_t reg_id = ub_get_reg_id(ub_get_byte_id(id, i));

		DR_ASSERT_MSG(reg_id == id, "ub_register_test - test82 failed...");
	}
}

static void test5() {

	check_from_byte_to_reg(DR_REG_XAX);
	check_from_byte_to_reg(DR_REG_XBX);
	check_from_byte_to_reg(DR_REG_XBP);
	check_from_byte_to_reg(DR_REG_XSI);
	check_from_byte_to_reg(DR_REG_XCX);
	check_from_byte_to_reg(DR_REG_XDI);
	check_from_byte_to_reg(DR_REG_XSP);
	check_from_byte_to_reg(DR_REG_XDX);

#ifdef X86_64
	check_from_byte_to_reg(DR_REG_R8);
	check_from_byte_to_reg(DR_REG_R9);
	check_from_byte_to_reg(DR_REG_R10);
	check_from_byte_to_reg(DR_REG_R11);
	check_from_byte_to_reg(DR_REG_R12);
	check_from_byte_to_reg(DR_REG_R13);
	check_from_byte_to_reg(DR_REG_R14);
	check_from_byte_to_reg(DR_REG_R15);
#endif

	check_from_byte_to_reg(DR_REG_XMM0);
	check_from_byte_to_reg(DR_REG_XMM1);
	check_from_byte_to_reg(DR_REG_XMM2);
	check_from_byte_to_reg(DR_REG_XMM3);
	check_from_byte_to_reg(DR_REG_XMM4);
	check_from_byte_to_reg(DR_REG_XMM5);
	check_from_byte_to_reg(DR_REG_XMM6);
	check_from_byte_to_reg(DR_REG_XMM7);
	check_from_byte_to_reg(DR_REG_XMM8);
	check_from_byte_to_reg(DR_REG_XMM9);
	check_from_byte_to_reg(DR_REG_XMM10);
	check_from_byte_to_reg(DR_REG_XMM11);
	check_from_byte_to_reg(DR_REG_XMM12);
	check_from_byte_to_reg(DR_REG_XMM13);
	check_from_byte_to_reg(DR_REG_XMM14);
	check_from_byte_to_reg(DR_REG_XMM15);
}

DR_EXPORT void dr_client_main(client_id_t id, int argc, const char *argv[]) {

	test1();
	test2();
	test3();
	test4();
	test5();
}

