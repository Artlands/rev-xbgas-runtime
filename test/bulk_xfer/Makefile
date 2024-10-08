CC=${RVCC}
ARCH=rv64imafdc
RV_OBJDUMP=riscv64-unknown-elf-objdump

# Source file
SRC = bulk_get
# bulk_get_nb
# bulk_put
# bulk_put_nb

# Number of elements and test names
ELEMS = 1 4 16 64 128 256 512 1024 1280 4096 8192 12800 16384 32768 65536 131072 
TESTS = 8B 32B 128B 512B 1KB 2KB 4KB 8KB 10KB 32KB 64KB 100KB 128KB 256KB 512KB 1MB 

# Compiler flags
RISCV_GCC_OPTS ?= -DPREALLOCATE=1 -mcmodel=medany -static -std=gnu17 -O0 -ffast-math -fno-common -fno-builtin-printf -march=$(ARCH) -mabi=lp64d
CINCLUDE = -I$(XBGAS_RUNTIME)/include  -I$(REV)/common/syscalls -I$(REV)/test/include

ifeq "$(RVCC)" "riscv64-unknown-elf-gcc"
	RISCV_GCC_OPTS += -fno-tree-loop-distribute-patterns
endif

# Rule to compile each executable by iterating over ELEMS and TESTS together
all:
	@set -e; \
	i=0; \
	for test in $(TESTS); do \
		elem=$$(echo $(ELEMS) | cut -d ' ' -f $$((i + 1))); \
		echo "Compiling $(SRC)_$$test.exe with ELEMS=$$elem"; \
		$(CC) $(RISCV_GCC_OPTS) $(CINCLUDE) -DELEMS=$$elem -o $(SRC)_$$test.exe $(SRC).c -L$(XBGAS_RUNTIME)/lib -lxbrtime -lm; \
		i=$$((i + 1)); \
	done

dump: 
	@set -e; \
	i=0; \
	for test in $(TESTS); do \
		elem=$$(echo $(ELEMS) | cut -d ' ' -f $$((i + 1))); \
		echo "Dumping $(SRC)_$$test.exe with ELEMS=$$elem"; \
		$(RV_OBJDUMP) -d $(SRC)_$$test.exe > $(SRC)_$$test.dump; \
		i=$$((i + 1)); \
	done

# Clean target
clean:
	rm -f *.exe *.dump

.PHONY: all clean