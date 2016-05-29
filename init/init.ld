OUTPUT_FORMAT(elf64-x86-64)
OUTPUT_ARCH(i386:x86-64)
ENTRY(main)

SECTIONS
{
	.text : { *(.text) }
}
