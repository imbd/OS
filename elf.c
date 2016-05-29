#include "elf.h"
#include "tmpfs.h"
#include "utils.h"
#include "allocator.h"
#include "process.h"
#include "print.h"

elf_contents * create_elf_contents(){
	elf_contents * ret = malloc(sizeof(elf_contents));
	list_init(&ret->mm_list_head);
	return ret;
}

void destroy_elf_contents(elf_contents * cont) {
	free(cont);
}

elf_contents * parse_elf(const char * path) {
	elf_contents * ret = create_elf_contents();

	int fd = tmpfs_open(path, OP_READ);
	size_t i = 0;
	struct elf_hdr hdr;
	struct elf_phdr phdr;

	tmpfs_read(fd, &hdr, sizeof(struct elf_hdr));
	ret->entry = hdr.e_entry;

	tmpfs_seek(fd, hdr.e_phoff);

	for (i = 0; i < hdr.e_phnum; i++) {
		tmpfs_read(fd, &phdr, sizeof(struct elf_phdr));

		if (phdr.p_type == PT_LOAD) {
			void * buf = malloc_aligned(phdr.p_memsz, PAGE_SIZE_2M);
			int offset = tmpfs_get_reading_offset(fd);
			tmpfs_seek(fd, phdr.p_offset);
			tmpfs_read(fd, buf, phdr.p_memsz);
			tmpfs_seek(fd, offset);

			p_mm_entry * new_entry = create_p_mm_entry(phdr.p_vaddr, pa(buf), phdr.p_memsz, US_CODE);
			list_add(&new_entry->list, &ret->mm_list_head);
		}
	}
	tmpfs_close(fd);
	return ret;
}
